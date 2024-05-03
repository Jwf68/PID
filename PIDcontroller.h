#pragma once

#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include "PIDparameters.h"

/*
Implementation of a PID controller, according to pseudocode from the book:
Karl J Åström and Tore Hägglund, Advanced PID control, ISA, 2006, page 428, F13.18.
*/
class PIDcontroller
{
public:
	void SetParameters(PIDparameters p);

	float Compute(float setPoint, float actualValue, float lowerLimitControlSignal, float upperLimitControlSignal);

private:
	float previousControldeviation = 0.f;
	float integralPart = 0.f;
	float p1, p2, p3, p4, p5, p6;
	float x = 0.f;
	float oldProportionalGain = 0.f;
	float oldSetpointWeightingFactor = 0.f;
	float setPoint = 0.f;
	float actualValue = 0.f;

	float SaturateControlSignal(float controlSignal, float lowerLimitControlSignal, float upperLimitControlSignal);
};
#endif // PIDCONTROLLER_H

