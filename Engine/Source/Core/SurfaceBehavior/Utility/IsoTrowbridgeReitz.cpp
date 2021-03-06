#include "Core/SurfaceBehavior/Utility/IsoTrowbridgeReitz.h"

#include <cmath>

namespace ph
{

IsoTrowbridgeReitz::IsoTrowbridgeReitz(const real alpha) :
	Microfacet(),
	m_alpha(alpha)
{

}

IsoTrowbridgeReitz::~IsoTrowbridgeReitz() = default;

// GGX (Trowbridge-Reitz) Normal Distribution Function
real IsoTrowbridgeReitz::distribution(
	const SurfaceHit& X,
	const Vector3R& N, const Vector3R& H) const
{
	const real NoH = N.dot(H);
	if(NoH <= 0.0_r)
	{
		return 0.0_r;
	}

	const real alpha2 = m_alpha * m_alpha;
	const real NoH2   = NoH * NoH;

	const real innerTerm   = NoH2 * (alpha2 - 1.0_r) + 1.0_r;
	const real denominator = PH_PI_REAL * innerTerm * innerTerm;

	return alpha2 / denominator;
}

// Smith's GGX Geometry Shadowing Function (H is expected to be on the hemisphere of N)
real IsoTrowbridgeReitz::shadowing(
	const SurfaceHit& X,
	const Vector3R& N, const Vector3R& H,
	const Vector3R& L, const Vector3R& V) const
{
	const real NoL = N.dot(L);
	const real NoV = N.dot(V);
	const real HoL = H.dot(L);
	const real HoV = H.dot(V);
	if(!isSidednessAgreed(NoL, NoV, HoL, HoV))
	{
		return 0.0_r;
	}

	const real alpha2 = m_alpha * m_alpha;

	// Here the shadowing factor uses a more accurate version than the one used
	// by Walter et al. (2007).
	// Reference: Eric Heitz, Understanding the Masking-Shadowing Function in 
	// Microfacet Based BRDFs, Journal of Computer Graphics Techniques Vol. 3, 
	// No. 2, 2014. Equation 99 is the one used here.

	const real lambdaL = 0.5_r * (-1.0_r + std::sqrt(1.0_r + alpha2 * (NoL * NoL)));
	const real lambdaV = 0.5_r * (-1.0_r + std::sqrt(1.0_r + alpha2 * (NoV * NoV)));

	return 1.0_r / (1.0_r + lambdaL + lambdaV);
}

// for GGX (Trowbridge-Reitz) Normal Distribution Function
void IsoTrowbridgeReitz::genDistributedH(
	const SurfaceHit& X,
	const real seedA_i0e1, const real seedB_i0e1,
	const Vector3R& N, 
	Vector3R* const out_H) const
{
	const real phi   = 2.0f * PH_PI_REAL * seedA_i0e1;
	const real theta = std::atan(m_alpha * std::sqrt(seedB_i0e1 / (1.0_r - seedB_i0e1)));

	const real sinTheta = std::sin(theta);
	const real cosTheta = std::cos(theta);

	Vector3R& H = *out_H;

	H.x = sinTheta * std::sin(phi);
	H.y = cosTheta;
	H.z = sinTheta * std::cos(phi);

	Vector3R xAxis;
	Vector3R yAxis(N);
	Vector3R zAxis;
	Math::formOrthonormalBasis(yAxis, &xAxis, &zAxis);
	H = xAxis.mulLocal(H.x).addLocal(yAxis.mulLocal(H.y)).addLocal(zAxis.mulLocal(H.z));
	H.normalizeLocal();
}

}// end namespace ph