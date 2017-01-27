#pragma once

#include "Actor/Geometry/Geometry.h"
#include "Common/primitive_type.h"

#include <vector>

namespace ph
{

class GWave : public Geometry
{
public:
	GWave(const float32 xLen, const float32 yLen, const float32 zLen);
	virtual ~GWave() override;

	virtual void discretize(std::vector<std::unique_ptr<Primitive>>* const out_primitives, const PrimitiveMetadata& metadata) const override;

private:
	float32 m_xLen;
	float32 m_yLen;
	float32 m_zLen;

	static void genTessellatedRectangleXZ(const float32 xLen, const float32 zLen, const int32 numXdivs, const int32 numZdivs, std::vector<Vector3f>& positions);
};

}// end namespace ph