#pragma once

#ifndef __PID_HANDLER_H
#define __PID_HANDLER_H

#include "TaskScheduler.h"
#include "Defines.h"
#include "LeafsStore.h"
#include "LeafManager.h"
#include "PidParameters.h"
#include "PidController.h"
#include <algorithm> 

#define PID_HANDLER_PERIOD 50

namespace company
{
	using namespace System;

	namespace product
	{
		using namespace System;

		class PidHandler : public ITask
		{
		public:
			PidHandler();
			void Init(LeafsStore* leafStore);

		private:
			void Execute() override;
			void UpdateSettings();
			void Compute();
			LeafsStore* _leafStore;
			SimpleTimer _timerSampling;
			PidParameters _NewPIDparameters;
			PidParameters _OldPIDparameters;
			float _lowerLimitControlSignal;
			float _upperLimitControlSignal;
			PidController _PIDcontroller;
			float _hysteresis;
			float _setPoint;
			float _actualValue;
			float _controlSignal;
		};
	}
}
#endif
