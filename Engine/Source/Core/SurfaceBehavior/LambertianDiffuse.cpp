#include "Core/SurfaceBehavior/LambertianDiffuse.h"
#include "Core/Ray.h"
#include "Math/Vector3f.h"
#include "Math/random_number.h"
#include "Math/constant.h"
#include "Actor/Material/MatteOpaque.h"
#include "Core/Intersection.h"
#include "Core/SurfaceBehavior/random_sample.h"
#include "Core/SurfaceBehavior/SurfaceSample.h"

#include <cmath>

namespace ph
{

LambertianDiffuse::LambertianDiffuse() :
	m_albedo(std::make_shared<ConstantTexture>(Vector3f(0.5f, 0.5f, 0.5f)))
{

}

LambertianDiffuse::~LambertianDiffuse() = default;

void LambertianDiffuse::genImportanceSample(const Intersection& intersection, const Ray& ray, SurfaceSample* const out_sample) const
{
	// Lambertian diffuse model's BRDF is simply albedo/pi.
	// The importance sampling strategy is to use the cosine term in the rendering equation, 
	// generating a cos(theta) weighted L corresponding to N, which PDF is cos(theta)/pi.
	// Thus, BRDF_lambertian*cos(theta)/PDF = albedo = Li's weight.

	Vector3f albedo;
	m_albedo->sample(intersection.getHitUVW(), &albedo);
	out_sample->m_LiWeight.set(albedo);

	// generate and transform L to N's space

	Vector3f& L = out_sample->m_direction;
	genUnitHemisphereCosineThetaWeightedSample(genRandomFloat32_0_1_uniform(), genRandomFloat32_0_1_uniform(), &L);
	Vector3f u;
	Vector3f v(intersection.getHitSmoothNormal());
	Vector3f w;
	v.calcOrthBasisAsYaxis(&u, &w);
	L = u.mulLocal(L.x).addLocal(v.mulLocal(L.y)).addLocal(w.mulLocal(L.z));
	L.normalizeLocal();

	// this model reflects light
	out_sample->m_type = ESurfaceSampleType::REFLECTION;
}

void LambertianDiffuse::setAlbedo(const std::shared_ptr<Texture>& albedo)
{
	m_albedo = albedo;
}

void LambertianDiffuse::evaluate(const Intersection& intersection, const Vector3f& L, const Vector3f& V, Vector3f* const out_value) const
{
	const float32 NoL = intersection.getHitSmoothNormal().dot(L);
	const float32 NoV = intersection.getHitSmoothNormal().dot(V);

	// check if L, V lies on different side of the surface
	if(NoL * NoV <= 0.0f)
	{
		out_value->set(0, 0, 0);
		return;
	}

	// sidedness agreement between real geometry and shading (phong-interpolated) normal
	if(NoL * intersection.getHitGeoNormal().dot(L) <= 0 || NoV * intersection.getHitGeoNormal().dot(V) <= 0.0f)
	{
		out_value->set(0, 0, 0);
		return;
	}

	Vector3f albedo;
	m_albedo->sample(intersection.getHitUVW(), &albedo);
	*out_value = albedo.divLocal(PI_FLOAT32).mulLocal(std::abs(NoL));
}

}// end namespace ph