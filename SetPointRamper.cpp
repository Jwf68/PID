#include "SetPointRamper.h"

namespace Lindinvent
{
	namespace MPD
	{
		void SetPointRamper::Init(unsigned int callPeriod)
		{
			_callPeriodSecond = callPeriod / 1000.f;
			_finalSetPoint = 0.f;
			_increaseSetPointEveryCallSecond = 0.f;
			_numberOfCallsTofinalSetPoint = 0;
			_rampedSetPoint = 0.f;
			_calls = 0;
		}

		void SetPointRamper::setUpRamp(float finalSetPoint, float timeToFinalSetPointSecond)
		{
			_finalSetPoint = finalSetPoint;
			_numberOfCallsTofinalSetPoint = timeToFinalSetPointSecond / _callPeriodSecond;
			_increaseSetPointEveryCallSecond = _finalSetPoint / float(_numberOfCallsTofinalSetPoint);
			_rampedSetPoint = 0.f;
			_calls = 0;
		}

		float SetPointRamper::getRampedSetPoint()
		{
			if (_calls < _numberOfCallsTofinalSetPoint)
			{
				_rampedSetPoint += _increaseSetPointEveryCallSecond;
				_calls++;
				return _rampedSetPoint;
			}
			else
			{
				return _finalSetPoint;
			}
		}
	}
}