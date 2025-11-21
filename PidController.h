#pragma once

#ifndef __PID_CONTROLLER_H
#define __PID_CONTROLLER_H

#include "PidParameters.h"

namespace company
{
	namespace product
	{
		/*
		Implementation of a PID controller, according to pseudocode from the book:
		Karl J Åström and Tore Hägglund, Advanced PID control, ISA, 2006, page 428, F13.18.
		*/
		class PidController
		{
		public:
			void SetParameters(PidParameters p);
			float Compute(float setPoint, float actualValue, float lowerLimitControlSignal, float upperLimitControlSignal);

		private:
			float integralPart = 0.f;
			float p1, p2, p3, p4, p5, p6;
			float x = 0.f;

			float SaturateControlSignal(float controlSignal, float lowerLimitControlSignal, float upperLimitControlSignal);
		};
	}
}
#endif

