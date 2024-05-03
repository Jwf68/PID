#pragma once

#ifndef __SETPOINTRAMPER_H
#define __SETPOINTRAMPER_H

namespace Lindinvent
{
	namespace MPD
	{

		class SetPointRamper
		{
		public:
			void Init(unsigned int callPeriod);
			void setUpRamp(float finalSetPoint, float timeToFinalSetPointSecond);
			float getRampedSetPoint();

		private:
			float _callPeriodSecond;
			float _finalSetPoint;
			float _increaseSetPointEveryCallSecond;
			int _numberOfCallsTofinalSetPoint;
			float _rampedSetPoint;
			int _calls;
		};
	}
}
#endif // __SETPOINTRAMPER_H

