#pragma once

#include "Math/TVector3.h"
#include "Math/TQuaternion.h"
#include "FileIO/Tokenizer.h"
#include "Math/Math.h"

#include <cmath>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace ph
{

template<typename T>
inline TVector3<T>::TVector3() :
	x(0), y(0), z(0)
{

}

template<typename T>
inline TVector3<T>::TVector3(const T x, const T y, const T z) :
	x(x), y(y), z(z)
{

}

template<typename T>
inline TVector3<T>::TVector3(const T var) :
	x(var), y(var), z(var)
{

}

template<typename T>
inline TVector3<T>::TVector3(const TVector3& other) :
	x(other.x), y(other.y), z(other.z)
{

}

template<typename T>
inline TVector3<T>::~TVector3() = default;

template<typename T>
TVector3<T> TVector3<T>::rotate(const TQuaternion<T>& rotation) const
{
	const TQuaternion<T>& conjugatedRotation = rotation.conjugate();
	const TQuaternion<T>& result = rotation.mul(*this).mulLocal(conjugatedRotation);

	return TVector3(result.x, result.y, result.z);
}

template<typename T>
void TVector3<T>::rotate(const TQuaternion<T>& rotation, TVector3* const out_result) const
{
	const TQuaternion<T>& conjugatedRotation = rotation.conjugate();
	const TQuaternion<T>& result = rotation.mul(*this).mulLocal(conjugatedRotation);

	out_result->x = result.x;
	out_result->y = result.y;
	out_result->z = result.z;
}

template<typename T>
inline T TVector3<T>::length() const
{
	return std::sqrt(squaredLength());
}

template<typename T>
inline T TVector3<T>::squaredLength() const
{
	return x * x + y * y + z * z;
}

template<typename T>
inline T TVector3<T>::max() const
{
	return std::max(x, std::max(y, z));
}

template<typename T>
inline T TVector3<T>::absMax() const
{
	return std::max(std::abs(x), std::max(std::abs(y), std::abs(z)));
}

template<typename T>
inline TVector3<T> TVector3<T>::max(const TVector3& rhs) const
{
	return TVector3(std::max(x, rhs.x), std::max(y, rhs.y), std::max(z, rhs.z));
}

template<typename T>
inline TVector3<T>& TVector3<T>::maxLocal(const TVector3& rhs)
{
	x = std::max(x, rhs.x);
	y = std::max(y, rhs.y);
	z = std::max(z, rhs.z);

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::min(const TVector3& rhs) const
{
	return TVector3(std::min(x, rhs.x), std::min(y, rhs.y), std::min(z, rhs.z));
}

template<typename T>
inline TVector3<T>& TVector3<T>::minLocal(const TVector3& rhs)
{
	x = std::min(x, rhs.x);
	y = std::min(y, rhs.y);
	z = std::min(z, rhs.z);

	return *this;
}

template<typename T>
inline int32 TVector3<T>::maxDimension() const
{
	return x > y ? (x > z ? Math::X_AXIS : Math::Z_AXIS) :
	               (y > z ? Math::Y_AXIS : Math::Z_AXIS);
}

template<typename T>
inline T TVector3<T>::dot(const TVector3& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

template<typename T>
inline T TVector3<T>::absDot(const TVector3& rhs) const
{
	return std::abs(dot(rhs));
}

template<typename T>
inline T TVector3<T>::dot(const T rhs) const
{
	return (x + y + z) * rhs;
}

template<typename T>
inline T TVector3<T>::dot(const T rhsX, const T rhsY, const T rhsZ) const
{
	return x * rhsX + y * rhsY + z * rhsZ;
}

template<typename T>
inline TVector3<T> TVector3<T>::cross(const TVector3& rhs) const
{
	return TVector3(y * rhs.z - z * rhs.y,
	                z * rhs.x - x * rhs.z,
	                x * rhs.y - y * rhs.x);
}

template<typename T>
inline void TVector3<T>::cross(const TVector3& rhs, TVector3* const out_result) const
{
	out_result->x = y * rhs.z - z * rhs.y;
	out_result->y = z * rhs.x - x * rhs.z;
	out_result->z = x * rhs.y - y * rhs.x;
}

template<typename T>
inline TVector3<T> TVector3<T>::normalize() const
{
	const T reciLen = 1 / length();
	return TVector3(x * reciLen, y * reciLen, z * reciLen);
}

template<typename T>
inline TVector3<T>& TVector3<T>::normalizeLocal()
{
	const T reciLen = 1 / length();

	x *= reciLen;
	y *= reciLen;
	z *= reciLen;

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::add(const TVector3& rhs) const
{
	return TVector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

template<typename T>
inline void TVector3<T>::add(const TVector3& rhs, TVector3* const out_result) const
{
	out_result->x = x + rhs.x;
	out_result->y = y + rhs.y;
	out_result->z = z + rhs.z;
}

template<typename T>
inline TVector3<T> TVector3<T>::add(const T rhs) const
{
	return TVector3(x + rhs, y + rhs, z + rhs);
}

template<typename T>
inline TVector3<T>& TVector3<T>::addLocal(const TVector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::addLocal(const T rhs)
{
	x += rhs;
	y += rhs;
	z += rhs;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::addLocal(const T rhsX, const T rhsY, const T rhsZ)
{
	x += rhsX;
	y += rhsY;
	z += rhsZ;

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::sub(const TVector3& rhs) const
{
	return TVector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

template<typename T>
inline TVector3<T> TVector3<T>::sub(const T rhs) const
{
	return TVector3(x - rhs, y - rhs, z - rhs);
}

template<typename T>
inline void TVector3<T>::sub(const TVector3& rhs, TVector3* const out_result) const
{
	out_result->x = x - rhs.x;
	out_result->y = y - rhs.y;
	out_result->z = z - rhs.z;
}

template<typename T>
inline TVector3<T>& TVector3<T>::subLocal(const TVector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::subLocal(const T rhs)
{
	x -= rhs;
	y -= rhs;
	z -= rhs;

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::mul(const TVector3& rhs) const
{
	return TVector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

template<typename T>
inline void TVector3<T>::mul(const TVector3& rhs, TVector3* const out_result) const
{
	out_result->x = x * rhs.x;
	out_result->y = y * rhs.y;
	out_result->z = z * rhs.z;
}

template<typename T>
inline TVector3<T> TVector3<T>::mul(const T rhs) const
{
	return TVector3(x * rhs, y * rhs, z * rhs);
}

template<typename T>
inline void TVector3<T>::mul(const T rhs, TVector3* const out_result) const
{
	out_result->x = x * rhs;
	out_result->y = y * rhs;
	out_result->z = z * rhs;
}

template<typename T>
inline TVector3<T>& TVector3<T>::mulLocal(const T rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::mulLocal(const TVector3& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::maddLocal(const T multiplier, const TVector3& adder)
{
	x = x * multiplier + adder.x;
	y = y * multiplier + adder.y;
	z = x * multiplier + adder.z;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::negateLocal()
{
	x *= -1;
	y *= -1;
	z *= -1;

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::div(const TVector3& rhs) const
{
	return TVector3(x / rhs.x, y / rhs.y, z / rhs.z);
}

template<typename T>
inline TVector3<T>& TVector3<T>::divLocal(const TVector3& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::div(const T rhs) const
{
	return TVector3(x / rhs, y / rhs, z / rhs);
}

template<typename T>
inline TVector3<T>& TVector3<T>::divLocal(const T rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::abs() const
{
	return TVector3(fabs(x), fabs(y), fabs(z));
}

template<typename T>
inline TVector3<T>& TVector3<T>::absLocal()
{
	x = std::abs(x);
	y = std::abs(y);
	z = std::abs(z);

	return *this;
}

// Clamp current vector's components to specific range. If a component is NaN, its value is
// clamped to lower bound. Either lower bound or upper bound shall not be NaN, or the method's 
// behavior is undefined.

template<typename T>
inline TVector3<T> TVector3<T>::clamp(const T lowerBound, const T upperBound) const
{
	return TVector3(fmin(upperBound, fmax(x, lowerBound)),
	                fmin(upperBound, fmax(y, lowerBound)),
	                fmin(upperBound, fmax(z, lowerBound)));
}

template<typename T>
inline TVector3<T>& TVector3<T>::clampLocal(const T lowerBound, const T upperBound)
{
	x = fmin(upperBound, fmax(x, lowerBound));
	y = fmin(upperBound, fmax(y, lowerBound));
	z = fmin(upperBound, fmax(z, lowerBound));

	return *this;
}

template<typename T>
inline TVector3<T> TVector3<T>::complement() const
{
	return TVector3(1 - x, 1 - y, 1 - z);
}

template<typename T>
inline T TVector3<T>::avg() const
{
	return (x + y + z) / 3;
}

template<typename T>
inline TVector3<T> TVector3<T>::reciprocal() const
{
	return TVector3(1 / x, 1 / y, 1 / z);
}

template<typename T>
inline TVector3<T> TVector3<T>::reflect(const TVector3& normal) const
{
	TVector3 result = normal.mul(2 * normal.dot(*this));
	return this->sub(result);
}

template<typename T>
inline TVector3<T>& TVector3<T>::reflectLocal(const TVector3& normal)
{
	const T factor = 2 * normal.dot(*this);

	x = x - factor * normal.x;
	y = y - factor * normal.y;
	z = z - factor * normal.z;

	return *this;
}

// returned (x, y, z) = (min, mid, max)
template<typename T>
inline void TVector3<T>::sort(TVector3* const out_result) const
{
	if(x > y)
	{
		if(x > z)
		{
			out_result->z = x;

			if(y < z)
			{
				out_result->x = y;
				out_result->y = z;
			}
			else
			{
				out_result->x = z;
				out_result->y = y;
			}
		}
		else
		{
			out_result->z = z;
			out_result->y = x;
			out_result->x = y;
		}
	}
	else
	{
		if(x < z)
		{
			out_result->x = x;

			if(y > z)
			{
				out_result->z = y;
				out_result->y = z;
			}
			else
			{
				out_result->z = z;
				out_result->y = y;
			}
		}
		else
		{
			out_result->x = z;
			out_result->y = x;
			out_result->z = y;
		}
	}
}

template<typename T>
inline std::string TVector3<T>::toStringFormal() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

template<typename T>
inline TVector3<T>& TVector3<T>::set(const T rhsX, const T rhsY, const T rhsZ)
{
	x = rhsX;
	y = rhsY;
	z = rhsZ;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::set(const T rhs)
{
	x = rhs;
	y = rhs;
	z = rhs;

	return *this;
}

template<typename T>
inline TVector3<T>& TVector3<T>::set(const TVector3& rhs)
{
	return set(rhs.x, rhs.y, rhs.z);
}

template<typename T>
inline void TVector3<T>::set(TVector3* const out_value) const
{
	out_value->x = x;
	out_value->y = y;
	out_value->z = z;
}

template<typename T>
inline bool TVector3<T>::equals(const TVector3& rhs) const
{
	return x == rhs.x &&
	       y == rhs.y &&
	       z == rhs.z;
}

template<typename T>
inline bool TVector3<T>::equals(const TVector3& rhs, const T margin) const
{
	return (x - rhs.x) < std::abs(margin) &&
	       (y - rhs.y) < std::abs(margin) &&
	       (z - rhs.z) < std::abs(margin);
}

template<typename T>
inline bool TVector3<T>::isZero() const
{
	return x == 0 && y == 0 && z == 0;
}

template<typename T>
inline bool TVector3<T>::hasNegativeComponent() const
{
	return x < 0 || y < 0 || z < 0;
}

template<typename T>
inline T& TVector3<T>::operator [] (const int32 axisIndex)
{
	switch(axisIndex)
	{
	case Math::X_AXIS: return x;
	case Math::Y_AXIS: return y;
	case Math::Z_AXIS: return z;
	}

	std::cerr << "warning: at TVector3<T>::operator [] (), axis index out of range (" << axisIndex << "), x is returned" << std::endl;
	return x;
}

template<typename T>
inline const T& TVector3<T>::operator [] (const int32 axisIndex) const
{
	switch(axisIndex)
	{
	case Math::X_AXIS: return x;
	case Math::Y_AXIS: return y;
	case Math::Z_AXIS: return z;
	}

	std::cerr << "warning: at TVector3<T>::operator [] (), axis index out of range (" << axisIndex << "), x is returned" << std::endl;
	return x;
}

template<typename T>
inline TVector3<T>& TVector3<T>::operator = (const TVector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

}// end namespace ph