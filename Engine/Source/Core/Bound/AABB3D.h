#pragma once

#include "Math/TVector3.h"

#include <vector>

namespace ph
{

class Ray;

class AABB3D final
{
public:
	static AABB3D makeUnioned(const AABB3D& a, const AABB3D& b);

public:
	AABB3D();
	AABB3D(const Vector3R& point);
	AABB3D(const Vector3R& minVertex, const Vector3R& maxVertex);

	bool isIntersectingVolume(const Ray& ray) const;
	bool isIntersectingVolume(const Ray& ray, real* out_rayNearHitT, real* out_rayFarHitT) const;
	bool isIntersectingVolume(const AABB3D& other) const;
	bool isPoint() const;
	AABB3D& unionWith(const AABB3D& other);
	AABB3D& unionWith(const Vector3R& point);

	std::vector<Vector3R> getVertices() const;

	inline void getMinMaxVertices(Vector3R* out_minVertex, Vector3R* out_maxVertex) const
	{
		out_minVertex->set(m_minVertex);
		out_maxVertex->set(m_maxVertex);
	}

	inline const Vector3R& getMinVertex() const
	{
		return m_minVertex;
	}

	inline const Vector3R& getMaxVertex() const
	{
		return m_maxVertex;
	}

	inline Vector3R calcCentroid() const
	{
		return m_minVertex.add(m_maxVertex).mulLocal(0.5_r);
	}

	inline Vector3R calcExtents() const
	{
		return m_maxVertex.sub(m_minVertex);
	}

	inline real calcSurfaceArea() const
	{
		const Vector3R& extents = calcExtents();
		return 2.0_r * (extents.x * extents.y + extents.y * extents.z + extents.z * extents.x);
	}

	inline void setMinVertex(const Vector3R& minVertex)
	{
		m_minVertex = minVertex;
	}

	inline void setMaxVertex(const Vector3R& maxVertex)
	{
		m_maxVertex = maxVertex;
	}

private:
	Vector3R m_minVertex;
	Vector3R m_maxVertex;
};

}// end namespace ph