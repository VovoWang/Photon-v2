#pragma once

#include "Math/TVector3.h"

namespace ph
{

template<typename T>
class TOrthonormalBasis3 final
{
public:
	TVector3<T> xAxis;
	TVector3<T> yAxis;
	TVector3<T> zAxis;

	inline TOrthonormalBasis3();
	inline TOrthonormalBasis3(const TOrthonormalBasis3& other);
	inline TOrthonormalBasis3(const TVector3<T>& xAxis, 
	                          const TVector3<T>& yAxis, 
	                          const TVector3<T>& zAxis);

	inline TVector3<T> worldToLocal(const TVector3<T>& worldVec) const;

	inline T cosPhi(const TVector3<T>& unitVec) const;
	inline T sinPhi(const TVector3<T>& unitVec) const;
	inline T tanPhi(const TVector3<T>& unitVec) const;
	inline T cos2Phi(const TVector3<T>& unitVec) const;
	inline T sin2Phi(const TVector3<T>& unitVec) const;
	inline T tan2Phi(const TVector3<T>& unitVec) const;
	inline T cosTheta(const TVector3<T>& unitVec) const;
	inline T sinTheta(const TVector3<T>& unitVec) const;
	inline T tanTheta(const TVector3<T>& unitVec) const;
	inline T cos2Theta(const TVector3<T>& unitVec) const;
	inline T sin2Theta(const TVector3<T>& unitVec) const;
	inline T tan2Theta(const TVector3<T>& unitVec) const;
	inline T absCosTheta(const TVector3<T>& unitVec) const;
	inline T absSinTheta(const TVector3<T>& unitVec) const;

	inline TOrthonormalBasis3& renormalize();

	inline void set(const TVector3<T>& xAxis, 
	                const TVector3<T>& yAxis, 
	                const TVector3<T>& zAxis);
	
	inline TOrthonormalBasis3& operator = (const TOrthonormalBasis3& rhs);
};

}// end namespace ph

#include "Math/TOrthonormalBasis3.ipp"