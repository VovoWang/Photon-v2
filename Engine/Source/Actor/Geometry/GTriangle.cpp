#include "Actor/Geometry/GTriangle.h"
#include "Core/Intersectable/PTriangle.h"
#include "Core/Intersectable/PrimitiveMetadata.h"
#include "Actor/StGenerator/StGenerator.h"
#include "Actor/AModel.h"
#include "FileIO/InputPacket.h"
#include "Actor/Geometry/PrimitiveBuildingMaterial.h"

#include <iostream>

namespace ph
{

GTriangle::GTriangle(const Vector3R& vA, const Vector3R& vB, const Vector3R& vC) : 
	Geometry(), 
	m_vA(vA), m_vB(vB), m_vC(vC)
{
	const Vector3R faceN = vB.sub(vA).cross(vC.sub(vA)).normalizeLocal();
	m_nA = faceN;
	m_nB = faceN;
	m_nC = faceN;

	m_uvwA.set(0, 0, 0);
	m_uvwB.set(1, 0, 0);
	m_uvwC.set(0, 1, 0);
}

//GTriangle::GTriangle(const InputPacket& packet) : 
//	Geometry(packet)
//{
//	const DataTreatment requiredDT(EDataImportance::REQUIRED, "GTriangle needs vA, vB, vC, nA, nB, nC, uvwA, uvwB, uvwC specified");
//
//	m_vA   = packet.getVector3r("vA",   Vector3R(0), requiredDT);
//	m_vB   = packet.getVector3r("vB",   Vector3R(0), requiredDT);
//	m_vC   = packet.getVector3r("vC",   Vector3R(0), requiredDT);
//	m_nA   = packet.getVector3r("nA",   Vector3R(0), requiredDT);
//	m_nB   = packet.getVector3r("nB",   Vector3R(0), requiredDT);
//	m_nC   = packet.getVector3r("nC",   Vector3R(0), requiredDT);
//	m_uvwA = packet.getVector3r("uvwA", Vector3R(0), requiredDT);
//	m_uvwB = packet.getVector3r("uvwB", Vector3R(0), requiredDT);
//	m_uvwC = packet.getVector3r("uvwC", Vector3R(0), requiredDT);
//}

GTriangle::~GTriangle() = default;

void GTriangle::genPrimitive(const PrimitiveBuildingMaterial& data,
                             std::vector<std::unique_ptr<Primitive>>& out_primitives) const
{
	if(!data.metadata)
	{
		std::cerr << "warning: at GTriangle::genPrimitive(), " 
		          << "no PrimitiveMetadata" << std::endl;
		return;
	}

	PTriangle triangle(data.metadata, m_vA, m_vB, m_vC);

	triangle.setNa(m_nA);
	triangle.setNb(m_nB);
	triangle.setNc(m_nC);

	Vector3R mappedUVW;

	m_stGenerator->map(m_vA, m_uvwA, &mappedUVW);
	triangle.setUVWa(mappedUVW);

	m_stGenerator->map(m_vB, m_uvwB, &mappedUVW);
	triangle.setUVWb(mappedUVW);

	m_stGenerator->map(m_vC, m_uvwC, &mappedUVW);
	triangle.setUVWc(mappedUVW);

	out_primitives.push_back(std::make_unique<PTriangle>(triangle));
}

std::shared_ptr<Geometry> GTriangle::genTransformApplied(const StaticTransform& transform) const
{
	auto tTriangle = std::make_shared<GTriangle>(*this);
	transform.transformP(m_vA, &tTriangle->m_vA);
	transform.transformP(m_vB, &tTriangle->m_vB);
	transform.transformP(m_vC, &tTriangle->m_vC);
	transform.transformO(m_nA, &tTriangle->m_nA);
	transform.transformO(m_nB, &tTriangle->m_nB);
	transform.transformO(m_nC, &tTriangle->m_nC);

	return tTriangle;
}

}// end namespace ph