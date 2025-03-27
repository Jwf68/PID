#pragma once

#ifndef __PID_PARAMETERS_H
#define __PID_PARAMETERS_H

namespace company
{
	namespace product
	{
		class PidParameters
		{
		public:
			PidParameters();

			/* The gain K is set to a negative value if the measured value goes in the same
			 * direction as the control signal, otherwise positive.
			 * An increase in the gain K means that the gain curve is raised for all frequencies while the
			 * phase curve remains unchanged. The increased gain at low frequencies means that any
			 * stationary errors are reduced. Increasing the gain will increase the cutoff frequency ωc of
			 * the compensated system. The increased cutting frequency means that the speed of the closed
			 * system increases. Because now the phase margin must be read at a higher frequency
			 * the gain increase will also mean that the phase margin decreases and
			 * the robustness becomes worse.
			*/
			float proportionalGain;

			/* The integration time in seconds. A reduction in Ti means an increase in integral action. 
			 * The integration time can be interpreted as the time it takes to double the P step when the control error is constant.
			 * If the process is fast then Ti is chosen short, while a slow process requires a longer Ti time because the control 
			 * signal should change more slowly. The integration time is thus chosen proportionally to the process times.
			 * A reduction in Ti causes the gain to increase
			 * for low frequencies, while the phase decreases. The increased gain at low
			 * frequencies mean that any stationary errors are reduced.
			 * The increased gain causes the speed of the closed system to increase.
			 * Because the phase margin must now be read at a higher frequency, at the same time as the phase
			 * decreased, the robustness of the closed system becomes worse.
			*/
			float integrationTimeSecond;

			/* The derivative time in seconds.
			 * An increase in Td means that the gain increases for high frequencies,
			 * while the phase increases. The increase in gain means that the cutoff frequency
			 * ωc increases.
			 * The increased cutting frequency means that the system becomes faster. The fact that
			 * the phase margin must now be read at a higher frequency gives a poorer robustness, but
			 * since we have simultaneously raised the phase, we cannot draw this conclusion. There actually is
			 * a possibility that one can achieve both an increase in speed and an improved robustness by raising Td.
			 * However, this only applies within certain limits. Then gives an increase in Td impaired robustness.
			*/
			float derivateTimeSecond;

			/* Time constant in seconds that controls how quickly the integral part should
			 * be restored after a limitation of the control signal. Tt is referred to as "tracking time
			 * constant". The time constant Tt should be greater than Td but less than Ti.
			 * A rule of thumb is to choose Tt according to Tt = sqrt(Ti * Td) for a PID controller and
			 * for a PI controller Tt = 0.5 * Ti.
			*/
			float trackingTimeConstantSecond;

			/* The time constant of the analogue measured value filter in e.g. seconds.
			 * To avoid the alias effect, the filter must eliminate any frequencies higher than half the
			 * sampling rate. The time constant Tanalogue f shall be chosen so that the
			 * frequencies above half the sampling frequency are attenuated, e.g. 16 times.
			 * The relationship between a low-pass filter's time constant Tf
			 * and its cutoff frequency is Tf = 1 / cutoff frequency.
			 * cutoff frequency = 1 / sampleTimeSecond / 2
			*/
			float filterTimeConstantSecond;

			/* The time constant of the derivative filter in seconds. This filter filters the measured value
			 * before the D-part. The filter is necessary for the prediction of the D-part to be reliable even if the
			 * measurement signal contains noise.
			 * Rule of thumb for the D filter Tf = Td / 10 is a good rule.
			 * Tf can be chosen according to Tf = Td/N, where typical
			 * values of N are between 2 and 20.
			 * The disadvantage of filtering is that the filter causes a delay
			 * or, more precisely, a phase shift of the signal. A delay negatively affects the D-part
			 * prediction function, which is not desirable. It is important to find a balance between
			 * how hard you want to filter and how much delay you can allow.
			*/
			float derivateFilterTimeConstantSecond;

			/* Setpoint weighting factor, value 0-1. The control signal does not react as strongly 
			 * to a setpoint change if Setpoint weighting factor < 1.
			*/
			float setpointWeightingFactor;

			/*
			* The sampling time is the time in e.g. seconds between each execution of the
			* regulator algorithm. Sampling rate = 1/h. A rule of thumb is to choose the sampling
			* time shorter than one-fifth of the process's time constant T.
			*/
			float sampleTimeSecond;

			bool equal(const PidParameters* other) const;
		};
	}
}
#endif