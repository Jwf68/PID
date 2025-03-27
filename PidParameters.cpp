#include "PidParameters.h"

namespace company
{
	namespace product
	{
		PidParameters::PidParameters() : 
			proportionalGain(0.f),
			integrationTimeSecond(0.f),
			derivateTimeSecond(0.f),
			trackingTimeConstantSecond(0.f),
			filterTimeConstantSecond(0.f),
			derivateFilterTimeConstantSecond(0.f),
			setpointWeightingFactor(0.f),
			sampleTimeSecond(0.f)
		{
		}

		bool PidParameters::equal(const PidParameters* other) const
		{
			return proportionalGain == other->proportionalGain &&
				integrationTimeSecond == other->integrationTimeSecond &&
				derivateTimeSecond == other->derivateTimeSecond &&
				trackingTimeConstantSecond == other->trackingTimeConstantSecond &&
				filterTimeConstantSecond == other->filterTimeConstantSecond &&
				derivateFilterTimeConstantSecond == other->derivateFilterTimeConstantSecond &&
				setpointWeightingFactor == other->setpointWeightingFactor &&
				sampleTimeSecond == other->sampleTimeSecond;
		}
	}
}