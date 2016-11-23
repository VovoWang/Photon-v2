#pragma once

#include "Common/primitive_type.h"
#include "Model/Primitive/BoundingVolume/AABB.h"

#include <memory>
#include <vector>

namespace ph
{

class Primitive;
class Intersection;

class KdtreeNode final
{
public:
	KdtreeNode();

	void buildTree(const std::vector<const Primitive*>& primitives);
	bool findClosestIntersection(const Ray& ray, Intersection* const out_intersection) const;

private:
	std::unique_ptr<KdtreeNode> m_positiveChild;
	std::unique_ptr<KdtreeNode> m_negativeChild;

	std::vector<const Primitive*> m_primitives;
	AABB m_aabb;

	int32   m_splitAxis;
	float32 m_splitPos;

	void buildChildrenNodes(const std::vector<const Primitive*>& primitives);
	std::unique_ptr<KdtreeNode> buildChildNode(const AABB& childAABB, const std::vector<const Primitive*>& parentPrimitives);
	bool traverseAndFindClosestIntersection(const Ray& ray, Intersection* const out_intersection, 
	                                        const float32 rayDistMin, const float32 rayDistMax) const;
	bool isLeaf() const;

private:
	static const int32 UNKNOWN_AXIS = -1;
	static const int32 X_AXIS = 0;
	static const int32 Y_AXIS = 1;
	static const int32 Z_AXIS = 2;

	static constexpr float64 COST_TRAVERSAL    = 1.0;
	static constexpr float64 COST_INTERSECTION = 1.0;
};

}// end namespace ph