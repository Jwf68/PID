#include "Scaler.h"

float Scaler::RawToEngineering(float minRaw, float maxRaw, float minEu, float maxEu, float rawValue)
{
	return (rawValue - minRaw) * ((maxEu - minEu) / (maxRaw - minRaw)) + minEu;
}
	
float Scaler::EngineeringToRaw(float minRaw, float maxRaw, float minEu, float maxEu, float euValue)
{
	return (euValue - minEu) * ((maxRaw - minRaw) / (maxEu - minEu)) + minRaw;
}

/*
If you select Linear, the result is calculated using linear interpolation
between the end points. The algorithm for linear scaling of input is:
EUValue = (RawValue - MinRaw) * ((MaxEU - MinEU) /
(MaxRaw - MinRaw)) + MinEU

The algorithm for linear scaling of output is:
RawValue = (EUValue - MinEU) * ((MaxRaw - MinRaw) /
(MaxEU - MinEU)) + MinRaw

If you select Square Root, the raw counts values are used for
interpolation. This is useful for scaling inputs from nonlinear devices such
as pressure transducers. The algorithm for square root scaling of input is:
EUValue = sqrt(RawValue - MinRaw) * ((MaxEU - MinEU) /
sqrt(MaxRaw - MinRaw)) + MinEU

The algorithm for square root scaling of output is:
RawValue = square((EUValue - MinEU) * (sqrt(MaxRaw –
MinRaw) / (MaxEU -MinEU))) + MinRaw
*/