#include "PidHandler.h"

namespace company
{
	namespace product
	{
		PidHandler::PidHandler() :
			_hysteresis(0.f),
			_controlSignal(0.f)
		{
		}

		void PidHandler::Init(LeafsStore* leafStore)
		{
			_leafStore = leafStore;
			_timerSampling.Start();
		}

		// This is the method the scheduler runs
		void PidHandler::Execute()
		{
			uint8_t functionAut1 = _leafStore->GetLeafValue<uint8_t>(MPX::FAUT1);
			uint8_t functionAut2 = _leafStore->GetLeafValue<uint8_t>(MPX::FAUT2);
			uint8_t functionAut3 = _leafStore->GetLeafValue<uint8_t>(MPX::FAUT3);

			if (functionAut1 != AUTF_PID2_CONTROLLER && functionAut2 != AUTF_PID2_CONTROLLER && functionAut3 != AUTF_PID2_CONTROLLER)
			{
				// bail if controller is not configured
				return;
			}

			if (this->_timerSampling.HasTimedOut(TIMER_SECOND, true))
			{
				UpdateSettings();
				Compute();
			}
		}

		void PidHandler::UpdateSettings()
		{
			_setPoint = _leafStore->GetLeafValue<float>(MPX::TEMP_ROOM_SP_FINAL);
			_actualValue = _leafStore->GetLeafValue<float>(MPX::TEMP_ROOM);
			_hysteresis = this->_leafStore->GetLeafValue<float>(MPX::PID2_HYSTERISIS);

			uint8_t functionAut1 = _leafStore->GetLeafValue<uint8_t>(MPX::FAUT1);
			uint8_t functionAut2 = _leafStore->GetLeafValue<uint8_t>(MPX::FAUT2);
			uint8_t functionAut3 = _leafStore->GetLeafValue<uint8_t>(MPX::FAUT3);

			if (functionAut1 == AUTF_PID2_CONTROLLER)
			{
				_lowerLimitControlSignal = this->_leafStore->GetLeafValue<float>(MPX::P1AUT1);
				_upperLimitControlSignal = this->_leafStore->GetLeafValue<float>(MPX::P2AUT1);
			}
			else if (functionAut2 == AUTF_PID2_CONTROLLER)
			{
				_lowerLimitControlSignal = this->_leafStore->GetLeafValue<float>(MPX::P1AUT2);
				_upperLimitControlSignal = this->_leafStore->GetLeafValue<float>(MPX::P2AUT2);
			}
			else if (functionAut3 == AUTF_PID2_CONTROLLER)
			{
				_lowerLimitControlSignal = this->_leafStore->GetLeafValue<float>(MPX::P1AUT3);
				_upperLimitControlSignal = this->_leafStore->GetLeafValue<float>(MPX::P2AUT3);
			}

			_NewPIDparameters.proportionalGain = this->_leafStore->GetLeafValue<float>(MPX::PID2_P);
			_NewPIDparameters.integrationTimeSecond = this->_leafStore->GetLeafValue<float>(MPX::PID2_I);
			_NewPIDparameters.derivateTimeSecond = 0.f;

			_NewPIDparameters.trackingTimeConstantSecond = 0.5f * _NewPIDparameters.integrationTimeSecond;
			_NewPIDparameters.derivateFilterTimeConstantSecond = _NewPIDparameters.derivateTimeSecond / 10.0f;
			_NewPIDparameters.setpointWeightingFactor = 0.5f;				
			_NewPIDparameters.sampleTimeSecond = 1.0f;
			_NewPIDparameters.filterTimeConstantSecond = 1.f / ((1.f / _NewPIDparameters.sampleTimeSecond) / 2.f);

			if (!_NewPIDparameters.equal(&_OldPIDparameters))
			{
				_PIDcontroller.SetParameters(_NewPIDparameters);
				_OldPIDparameters = _NewPIDparameters;
			}
		}

		void PidHandler::Compute()
		{		
			float controlError  = _setPoint - _actualValue;

			if (std::fabs(controlError) > _hysteresis)
			{
				_controlSignal = _PIDcontroller.Compute(_setPoint, _actualValue, _lowerLimitControlSignal, _upperLimitControlSignal);
			}
			Globals::PIDOutput = (unsigned char)Math::Clamp(_controlSignal * 25.5f, 0, 255);
		}
	}
}
