#pragma once

#ifndef CHANGERATELIMITER_H
#define CHANGERATELIMITER_H

#include <stdlib.h>

/* Limits the rate of change of a float number.
*/
class ChangeRateLimiter
{
public:
	void SetSampleTime(float sampleTimeSecond);
	void SetMaxChangeRatePerSecond(float changeRate);
	float LimitChangeRate(float value);

private:
	float sampleTimeSecond = 0.f;
	float maxChangePerCall = 0.f;
	float oldValue = 0.f;
};
#endif // CHANGERATELIMITER_H

