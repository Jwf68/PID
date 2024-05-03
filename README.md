# Text book implementation of a PID controller in C++
Implementation of a PID controller, according to pseudocode from the book: Karl J Åström and Tore Hägglund, Advanced PID control, ISA, 2006, page 428, F13.18.
The file PIDJonasWahlfrid2007_02_19_EN.pdf contains report "Realization and tuning of PID controllers", which explains in detail the PID implementation.

Classes:
ChangeRateLimiter is used to limit set point changes.
PIDcontroller the PID controller.
PIDparameters parameters for the PID controller.
Scaler is used to scale raw values to engineering units.

Typical usage:
// one time initiation 
			_PIDparameters.proportionalGain = 0.2f;
			_PIDparameters.integrationTimeSecond = 0.2f;
			_PIDparameters.derivateTimeSecond = 0.0f;
			_PIDparameters.trackingTimeConstantSecond = 0.1f;
			_PIDparameters.filterTimeConstantSecond = 1.0f;
			_PIDparameters.derivateFilterTimeConstantSecond = 1.0f;
			_PIDparameters.setpointWeightingFactor = 0.5f;
			_PIDparameters.sampleTimeSecond = 0.1f;
			_PIDcontroller.SetParameters(_PIDparameters);
			_changeRateLimiter.SetSampleTime(0.1f);

// continus call
			_speedSetPointHz = 40;
			_changeRateLimiter.SetMaxChangeRatePerSecond(4.0f);
			float limitedSetPoint = _changeRateLimiter.LimitChangeRate(_speedSetPointHz);
			float limitedSpeedActualValueHz = LimitSignal(_speedActualValueHz, 0, 80);
			float controlSignal = _PIDcontroller.Compute(limitedSetPoint, limitedSpeedActualValueHz, 0.f, _settings.MaxPowerLimitControlSignal);
