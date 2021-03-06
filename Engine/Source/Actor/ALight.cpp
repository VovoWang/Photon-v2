#include "Actor/ALight.h"
#include "Math/Math.h"
#include "Core/Intersectable/PrimitiveMetadata.h"
#include "Actor/Geometry/Geometry.h"
#include "Actor/Material/Material.h"
#include "Actor/Material/MatteOpaque.h"
#include "Actor/LightSource/LightSource.h"
#include "Actor/CookedUnit.h"
#include "FileIO/InputPacket.h"
#include "Actor/Geometry/PrimitiveBuildingMaterial.h"
#include "Actor/LightSource/EmitterBuildingMaterial.h"
#include "Core/Intersectable/TransformedIntersectable.h"
#include "Actor/ModelBuilder.h"

#include <algorithm>
#include <iostream>

namespace ph
{

ALight::ALight() : 
	PhysicalActor(), 
	m_geometry(nullptr), m_material(nullptr), m_lightSource(nullptr)
{

}

ALight::ALight(const std::shared_ptr<LightSource>& lightSource) : 
	PhysicalActor(),
	m_geometry(nullptr), m_material(nullptr), m_lightSource(lightSource)
{

}

ALight::ALight(const ALight& other) : 
	PhysicalActor(other),
	m_geometry(other.m_geometry), m_material(other.m_material), m_lightSource(other.m_lightSource)
{

}

ALight::~ALight() = default;


ALight& ALight::operator = (ALight rhs)
{
	swap(*this, rhs);

	return *this;
}

// TODO: simply this method
CookedUnit ALight::cook(CookingContext& context) const
{
	if(!m_lightSource)
	{
		std::cerr << "warning: at ALight::cook(), "
		          << "incomplete data detected" << std::endl;
		return CookedUnit();
	}

	CookedUnit cookedActor;
	if(m_geometry)
	{
		cookedActor = buildGeometricLight(context);
	}
	else
	{
		auto baseLW = std::make_unique<StaticTransform>(StaticTransform::makeForward(m_localToWorld));
		auto baseWL = std::make_unique<StaticTransform>(StaticTransform::makeInverse(m_localToWorld));

		EmitterBuildingMaterial emitterBuildingMaterial;
		cookedActor.emitter = m_lightSource->genEmitter(context, emitterBuildingMaterial);
		cookedActor.emitter->setTransform(baseLW.get(), baseWL.get());
		cookedActor.transforms.push_back(std::move(baseLW));
		cookedActor.transforms.push_back(std::move(baseWL));
	}

	return cookedActor;
}

const Geometry* ALight::getGeometry() const
{
	return m_geometry.get();
}

const Material* ALight::getMaterial() const
{
	return m_material.get();
}

const LightSource* ALight::getLightSource() const
{
	return m_lightSource.get();
}

void ALight::setGeometry(const std::shared_ptr<Geometry>& geometry)
{
	m_geometry = geometry;
}

void ALight::setMaterial(const std::shared_ptr<Material>& material)
{
	m_material = material;
}

void ALight::setLightSource(const std::shared_ptr<LightSource>& lightSource)
{
	m_lightSource = lightSource;
}

CookedUnit ALight::buildGeometricLight(CookingContext& context) const
{
	std::shared_ptr<Material> material = m_material;
	if(!material)
	{
		std::cout << "note: at ALight::buildGeometricLight(), " 
		          << "material is not specified, using default diffusive material" << std::endl;
		material = std::make_shared<MatteOpaque>();
	}

	ModelBuilder modelBuilder(context);

	std::unique_ptr<Transform> baseLW, baseWL;
	auto sanifiedGeometry = getSanifiedEmitterGeometry(context, &baseLW, &baseWL);
	if(!sanifiedGeometry)
	{
		sanifiedGeometry = m_geometry;
		std::cerr << "warning: at ALight::buildGeometricLight(), "
		          << "sanified geometry cannot be made; proceed at your own risk" << std::endl;
	}


	// TODO: transform must be rigid (e.g., motion)
	

	EmitterBuildingMaterial emitterBuildingMaterial;
	PrimitiveBuildingMaterial primitiveBuildingMaterial;
	auto metadata = std::make_unique<PrimitiveMetadata>();
	primitiveBuildingMaterial.metadata = metadata.get();

	material->populateSurfaceBehavior(context, &(metadata->surfaceBehavior));

	std::vector<std::unique_ptr<Primitive>> primitives;
	sanifiedGeometry->genPrimitive(primitiveBuildingMaterial, primitives);
	for(auto& primitive : primitives)
	{
		emitterBuildingMaterial.primitives.push_back(primitive.get());
		modelBuilder.addIntersectable(std::move(primitive));
	}

	auto emitter = m_lightSource->genEmitter(context, emitterBuildingMaterial);
	metadata->surfaceBehavior.setEmitter(emitter.get());

	// TODO: this relies on Emitter having the exact same behavior with 
	// TransformedIntersectable when a transform is applied, which is
	// risky
	emitter->setTransform(baseLW.get(), baseWL.get());

	// TODO: baseLW & baseWL may be identity transform if base transform
	// is applied to the geometry, in such case, wrapping primitives with
	// TransformedIntersectable is a total waste
	modelBuilder.transform(std::move(baseLW), std::move(baseWL));

	modelBuilder.setPrimitiveMetadata(std::move(metadata));

	CookedUnit cookedActor = modelBuilder.claimBuildResult();
	cookedActor.emitter = std::move(emitter);

	return cookedActor;
}

std::shared_ptr<Geometry> ALight::getSanifiedEmitterGeometry(
	CookingContext& context,
	std::unique_ptr<Transform>* const out_baseLW,
	std::unique_ptr<Transform>* const out_baseWL) const
{
	std::shared_ptr<Geometry> sanifiedGeometry = nullptr;
	*out_baseLW = nullptr;
	*out_baseWL = nullptr;

	auto baseLW = std::make_unique<StaticTransform>(StaticTransform::makeForward(m_localToWorld));
	auto baseWL = std::make_unique<StaticTransform>(StaticTransform::makeInverse(m_localToWorld));

	// TODO: test "isRigid()" may be more appropriate
	if(m_localToWorld.hasScaleEffect())
	{
		sanifiedGeometry = m_geometry->genTransformApplied(*baseLW);
		if(sanifiedGeometry != nullptr)
		{
			// TODO: combine identity transforms...
			*out_baseLW = std::make_unique<StaticTransform>(StaticTransform::IDENTITY());
			*out_baseWL = std::make_unique<StaticTransform>(StaticTransform::IDENTITY());
		}
		else
		{
			std::cerr << "warning: at ALight::getSanifiedEmitterGeometry(), "
			          << "scale detected and has failed to apply it to the geometry; "
			          << "scaling on light with attached geometry may have unexpected "
			          << "behaviors such as miscalculated primitive surface area, which "
			          << "can cause severe rendering artifacts" << std::endl;
		}
	}
	else
	{
		sanifiedGeometry = m_geometry;
		*out_baseLW = std::move(baseLW);
		*out_baseWL = std::move(baseWL);
	}

	return sanifiedGeometry;
}

void swap(ALight& first, ALight& second)
{
	// enable ADL
	using std::swap;

	// by swapping the members of two objects, the two objects are effectively swapped
	swap(static_cast<PhysicalActor&>(first), static_cast<PhysicalActor&>(second));
	swap(first.m_geometry,                   second.m_geometry);
	swap(first.m_material,                   second.m_material);
	swap(first.m_lightSource,                second.m_lightSource);
}

SdlTypeInfo ALight::ciTypeInfo()
{
	return SdlTypeInfo(ETypeCategory::REF_ACTOR, "light");
}

void ALight::ciRegister(CommandRegister& cmdRegister)
{
	SdlLoader loader;
	loader.setFunc<ALight>(ciLoad);
	cmdRegister.setLoader(loader);

	SdlExecutor translateSE;
	translateSE.setName("translate");
	translateSE.setFunc<ALight>(ciTranslate);
	cmdRegister.addExecutor(translateSE);

	SdlExecutor rotateSE;
	rotateSE.setName("rotate");
	rotateSE.setFunc<ALight>(ciRotate);
	cmdRegister.addExecutor(rotateSE);

	SdlExecutor scaleSE;
	scaleSE.setName("scale");
	scaleSE.setFunc<ALight>(ciScale);
	cmdRegister.addExecutor(scaleSE);
}

std::unique_ptr<ALight> ALight::ciLoad(const InputPacket& packet)
{
	const DataTreatment requiredData(EDataImportance::REQUIRED, 
	                                 "ALight requires at least a LightSource");
	const auto lightSource = packet.get<LightSource>("light-source", requiredData);
	const auto geometry    = packet.get<Geometry>("geometry");
	const auto material    = packet.get<Material>("material");

	std::unique_ptr<ALight> light = std::make_unique<ALight>(lightSource);
	light->setGeometry(geometry);
	light->setMaterial(material);
	return light;
}

}// end namespace ph