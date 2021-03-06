#pragma once

#include "Common/primitive_type.h"
#include "Math/math_fwd.h"
#include "Core/Camera/RadianceSensor.h"
#include "FileIO/SDL/TCommandInterface.h"
#include "Core/Bound/TAABB2D.h"
#include "Math/TVector2.h"
#include "Core/Quantity/SpectralStrength.h"
#include "Frame/frame_fwd.h"

#include <vector>
#include <functional>
#include <memory>

namespace ph
{

class InputPacket;
class SampleFilter;

class Film : public TCommandInterface<Film>
{
public:
	Film(int64 actualWidthPx, int64 actualHeightPx,
	     const std::shared_ptr<SampleFilter>& filter);
	Film(int64 actualWidthPx, int64 actualHeightPx,
	     const TAABB2D<int64>& effectiveWindowPx,
	     const std::shared_ptr<SampleFilter>& filter);
	virtual ~Film() = 0;

	virtual void addSample(float64 xPx, float64 yPx, const SpectralStrength& radiance) = 0;
	void develop(HdrRgbFrame& out_frame) const;
	void develop(HdrRgbFrame& out_frame, const TAABB2D<int64>& regionPx) const;
	virtual void clear() = 0;

	// Generates a child film with the same actual dimensions and filter as parent's, 
	// but potentially has a different effective window.
	// A child film can be merged into its parent by calling mergeToParent().
	virtual std::unique_ptr<Film> genChild(const TAABB2D<int64>& effectiveWindowPx) = 0;

	inline void mergeToParent() const
	{
		m_merger();
	}

	inline const TVector2<int64>& getActualResPx() const
	{
		return m_actualResPx;
	}

	inline const TVector2<int64>& getEffectiveResPx() const
	{
		return m_effectiveResPx;
	}

	inline const TVector2<float64>& getSampleResPx() const
	{
		return m_sampleResPx;
	}

	inline const TAABB2D<int64>& getEffectiveWindowPx() const
	{
		return m_effectiveWindowPx;
	}

	inline const TAABB2D<float64>& getSampleWindowPx() const
	{
		return m_sampleWindowPx;
	}

protected:
	TVector2<int64>   m_actualResPx;
	TVector2<int64>   m_effectiveResPx;
	TVector2<float64> m_sampleResPx;
	TAABB2D<int64>    m_effectiveWindowPx;
	TAABB2D<float64>  m_sampleWindowPx;

	std::shared_ptr<SampleFilter> m_filter;
	std::function<void()>         m_merger;

private:
	virtual void developRegion(HdrRgbFrame& out_frame, const TAABB2D<int64>& regionPx) const = 0;

// command interface
public:
	static SdlTypeInfo ciTypeInfo();
	static void ciRegister(CommandRegister& cmdRegister);
};

}// end namespace ph