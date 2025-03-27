#pragma once

#ifndef SCALER_H
#define SCALER_H

/* Scales raw values to engineeing value.
*/
class Scaler
{
public:
	float RawToEngineering(float minRaw, float maxRaw, float minEu, float maxEu, float rawValue);
	float EngineeringToRaw(float minRaw, float maxRaw, float minEu, float maxEu, float euValue);
private:

};
#endif // SCALER_H

