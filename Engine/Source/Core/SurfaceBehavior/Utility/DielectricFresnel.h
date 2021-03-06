#pragma once

#include "Core/SurfaceBehavior/Utility/FresnelEffect.h"

namespace ph
{

class DielectricFresnel : public FresnelEffect
{
public:
	DielectricFresnel(real iorOuter, real iorInner);
	virtual ~DielectricFresnel() override;

	// TODO: add a dielectric specific form (not spectral)
	virtual void calcReflectance(real cosThetaIncident, SpectralStrength* out_reflectance) const = 0;

	bool calcRefractDir(const Vector3R& I, const Vector3R& N, Vector3R* out_refractDir) const;

	inline real getIorOuter() const
	{
		return m_iorOuter;
	}

	inline real getIorInner() const
	{
		return m_iorInner;
	}

protected:
	real m_iorOuter;
	real m_iorInner;
};

}// end namespace ph