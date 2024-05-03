#include "PIDController.h"

void PIDcontroller::SetParameters(PIDparameters p)
{
	// calculate parameters only when settings are changed
	p1 = p.proportionalGain * p.setpointWeightingFactor; // set-point gain
	p2 = p.proportionalGain + p.proportionalGain * p.derivateTimeSecond / (p.derivateFilterTimeConstantSecond + p.sampleTimeSecond); // PD gain
	p3 = p.derivateFilterTimeConstantSecond / (p.derivateFilterTimeConstantSecond + p.sampleTimeSecond); // filter constant
	p4 = p.proportionalGain * p.derivateTimeSecond * p.sampleTimeSecond / (p.derivateFilterTimeConstantSecond + p.sampleTimeSecond) *
		(p.derivateFilterTimeConstantSecond + p.sampleTimeSecond); // derivative gain
	p5 = p.proportionalGain * p.sampleTimeSecond / p.integrationTimeSecond; // integral gain
	p6 = p.sampleTimeSecond / p.trackingTimeConstantSecond; // anti-windup gain
	// Bumpless parameter changes
	this->integralPart = this->integralPart + this->oldProportionalGain * (this->oldSetpointWeightingFactor * this->setPoint - this->actualValue) -
		p.proportionalGain * (p.setpointWeightingFactor * this->setPoint - this->actualValue);
	this->oldProportionalGain = p.proportionalGain;
	this->oldSetpointWeightingFactor = p.setpointWeightingFactor;
}

float PIDcontroller::Compute(float setPoint, float actualValue, float lowerLimitControlSignal, float upperLimitControlSignal)
{
	this->setPoint = setPoint;
	this->actualValue = actualValue;

	float controlSignal = p1 * setPoint - p2 * actualValue + this->x + this->integralPart; // compute nominal output
	float controlSignalLimited = SaturateControlSignal(controlSignal, lowerLimitControlSignal, upperLimitControlSignal); // saturate output
	this->x = p3 * this->x + p4 * actualValue; // part of D-part & filter
	this->integralPart = this->integralPart + p5 * (setPoint - actualValue) + p6 * (controlSignalLimited - controlSignal); // integral part

	return controlSignalLimited; // set manipulated variable
}

float PIDcontroller::SaturateControlSignal(float controlSignal, float lowerLimitControlSignal, float upperLimitControlSignal)
{
	float temp;

	if (lowerLimitControlSignal > upperLimitControlSignal)
	{
		temp = upperLimitControlSignal;
		upperLimitControlSignal = lowerLimitControlSignal;
		lowerLimitControlSignal = temp;
	}

	if (controlSignal < lowerLimitControlSignal)
	{
		controlSignal = lowerLimitControlSignal;
	}
	else if (controlSignal > upperLimitControlSignal)
	{
		controlSignal = upperLimitControlSignal;
	}

	return controlSignal;
}