#include "Scaler.h"

float Scaler::FloatScale(float minRaw, float maxRaw, float minEU, float maxEU, float rawValue)
{
	return (rawValue - minRaw) * ((maxEU - minEU) / (maxRaw - minRaw)) + minEU;
}