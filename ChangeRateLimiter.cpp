#include "ChangeRateLimiter.h"

void ChangeRateLimiter::SetSampleTime(float sampleTimeSecond)
{
	this->sampleTimeSecond = sampleTimeSecond;
}

void ChangeRateLimiter::SetMaxChangeRatePerSecond(float changeRatePerSecond)
{
	// Calculate the maximum allowed change
	this->maxChangePerCall = changeRatePerSecond * this->sampleTimeSecond;
}

float ChangeRateLimiter::LimitChangeRate(float value)
{
	float returnValue = value;
	// Calculate the actual change
	float change = value - this->oldValue;

	// Check if the change exceeds the maximum allowed change
	if (std::abs(change) > this->maxChangePerCall)
	{
		// Limit the change to the maximum allowed
		if (change > 0)
		{
			returnValue = this->oldValue + this->maxChangePerCall;
		}
		else
		{
			returnValue = this->oldValue - this->maxChangePerCall;
		}
	}
	this->oldValue = returnValue;
	return returnValue;
}