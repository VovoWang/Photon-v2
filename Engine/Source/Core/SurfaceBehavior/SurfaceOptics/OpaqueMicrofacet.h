#pragma once

#include "Core/SurfaceBehavior/SurfaceOptics.h"
#include "Math/TVector3.h"
#include "Core/Texture/TTexture.h"
#include "Core/SurfaceBehavior/Utility/Microfacet.h"
#include "Core/SurfaceBehavior/Utility/FresnelEffect.h"
#include "Core/Quantity/SpectralStrength.h"

#include <memory>

namespace ph
{

class OpaqueMicrofacet final : public SurfaceOptics
{
public:
	OpaqueMicrofacet();
	virtual ~OpaqueMicrofacet() override;

	inline void setAlbedo(const std::shared_ptr<TTexture<SpectralStrength>>& albedo)
	{
		m_albedo = albedo;
	}

	inline void setMicrofacet(const std::shared_ptr<Microfacet>& microfacet)
	{
		m_microfacet = microfacet;
	}

	inline void setFresnelEffect(const std::shared_ptr<FresnelEffect>& fresnel)
	{
		m_fresnel = fresnel;
	}

private:
	virtual void evalBsdf(
		const SurfaceHit& X, const Vector3R& L, const Vector3R& V,
		SpectralStrength* out_bsdf,
		ESurfacePhenomenon* out_type) const override;

	virtual void genBsdfSample(
		const SurfaceHit& X, const Vector3R& V,
		Vector3R* out_L,
		SpectralStrength* out_pdfAppliedBsdf,
		ESurfacePhenomenon* out_type) const override;

	virtual void calcBsdfSamplePdf(
		const SurfaceHit& X, const Vector3R& L, const Vector3R& V,
		const ESurfacePhenomenon& type,
		real* out_pdfW) const override;

private:
	std::shared_ptr<TTexture<SpectralStrength>> m_albedo;
	std::shared_ptr<Microfacet>                 m_microfacet;
	std::shared_ptr<FresnelEffect>              m_fresnel;
};

}// end namespace ph