#include "World/BruteForceIntersector.h"
#include "Model/Primitive/Primitive.h"
#include "Common/primitive_type.h"
#include "Core/Intersection.h"
#include "Core/Ray.h"

#include <limits>

namespace ph
{

BruteForceIntersector::~BruteForceIntersector() = default;

void BruteForceIntersector::construct(const std::vector<std::unique_ptr<Primitive>>& primitives)
{
	m_primitives.clear();
	m_primitives.shrink_to_fit();

	for(const auto& primitive : primitives)
	{
		m_primitives.push_back(primitive.get());
	}
}

bool BruteForceIntersector::isIntersecting(const Ray& ray, Intersection* out_intersection) const
{
	Intersection intersection;
	float32 closestSquaredHitDist = std::numeric_limits<float32>::infinity();

	for(const auto& primitive : m_primitives)
	{
		if(primitive->isIntersecting(ray, &intersection))
		{
			float32 squaredHitDist = intersection.getHitPosition().sub(ray.getOrigin()).squaredLength();
			if(closestSquaredHitDist > squaredHitDist)
			{
				closestSquaredHitDist = squaredHitDist;
				*out_intersection = intersection;
			}
		}
	}

	return closestSquaredHitDist != std::numeric_limits<float32>::infinity();
}

}// end namespace ph