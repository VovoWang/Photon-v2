#include "Math/Transform/StaticTransform.h"
#include "Core/Ray.h"
#include "Math/TVector3.h"

#include <iostream>

namespace ph
{

const StaticTransform& StaticTransform::IDENTITY()
{
	static const StaticTransform identity(Matrix4R::IDENTITY(), Matrix4R::IDENTITY());
	return identity;
}

StaticTransform::StaticTransform() : 
	StaticTransform(Matrix4R::IDENTITY(), Matrix4R::IDENTITY())
{

}

StaticTransform::StaticTransform(const Matrix4R& transform, const Matrix4R& inverseTransform) : 
	m_transformMatrix(transform), m_inverseTransformMatrix(inverseTransform)
{

}

StaticTransform::~StaticTransform() = default;

std::unique_ptr<Transform> StaticTransform::genInversed() const
{
	auto inversed = std::make_unique<StaticTransform>();
	inversed->m_transformMatrix        = m_inverseTransformMatrix;
	inversed->m_inverseTransformMatrix = m_transformMatrix;

	return std::move(inversed);
}

void StaticTransform::transformVector(const Vector3R& vector, const Time& time,
                                      Vector3R* const out_vector) const
{
	// TODO: use quaternion
	m_transformMatrix.mul(vector, 0.0_r, out_vector);
}

void StaticTransform::transformOrientation(const Vector3R& orientation, const Time& time,
                                           Vector3R* const out_orientation) const
{
	// TODO: correctly transform orientation
	m_transformMatrix.mul(orientation, 0.0_r, out_orientation);
}

void StaticTransform::transformPoint(const Vector3R& point, const Time& time,
                                     Vector3R* const out_point) const
{
	m_transformMatrix.mul(point, 1.0_r, out_point);
}

void StaticTransform::transformLineSegment(const Vector3R& lineStartPos, const Vector3R& lineDir,
                                           const real lineMinT, const real lineMaxT, 
                                           const Time& time,
                                           Vector3R* const out_lineStartPos,
                                           Vector3R* const out_lineDir,
                                           real* const out_lineMinT, 
                                           real* const out_lineMaxT) const
{
	StaticTransform::transformPoint (lineStartPos, time, out_lineStartPos);
	StaticTransform::transformVector(lineDir,      time, out_lineDir);
	*out_lineMinT = lineMinT;
	*out_lineMaxT = lineMaxT;
}

}// end namespace ph