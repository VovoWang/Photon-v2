#pragma once

#include "Model/Material/SurfaceIntegrand.h"

namespace ph
{

class MatteOpaque;

class LambertianDiffuseSurfaceIntegrand : public SurfaceIntegrand
{
public:
	LambertianDiffuseSurfaceIntegrand(const MatteOpaque* const matteOpaque);
	virtual ~LambertianDiffuseSurfaceIntegrand() override;

	virtual void genUniformRandomV(const Intersection& intersection, const Vector3f& L, Vector3f* out_V) const override;
	virtual void genImportanceRandomV(const Intersection& intersection, const Vector3f& L, Vector3f* out_V) const override;
	virtual void evaluateUniformRandomVPDF(const Intersection& intersection, const Vector3f& L, const Vector3f& V, Vector3f* const out_PDF) const override;
	virtual void evaluateImportanceRandomVPDF(const Intersection& intersection, const Vector3f& L, const Vector3f& V, Vector3f* const out_PDF) const override;
	virtual void evaluateLiWeight(const Intersection& intersection, const Vector3f& L, const Vector3f& V, Vector3f* const out_LiWeight) const override;

private:
	const MatteOpaque* m_matteOpaque;
};

}// end namespace ph