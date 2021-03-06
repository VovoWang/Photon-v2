#include "Core/Intersectable/Bvh/BvhIntersectableInfo.h"
#include "Core/Intersectable/Intersectable.h"

#include <iostream>

namespace ph
{

BvhIntersectableInfo::BvhIntersectableInfo(
	const Intersectable* const intersectable, 
	const std::size_t          index) :
	index(index), aabb(), aabbCentroid(), intersectable(intersectable)
{
	intersectable->calcAABB(&aabb);
	aabbCentroid = aabb.calcCentroid();
}

}// end namespace ph