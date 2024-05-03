#pragma once

#ifndef SCALER_H
#define SCALER_H

/* Scales raw values to engineeing value.
*/
class Scaler
{
public:
	float FloatScale(float minRaw, float maxRaw, float minEU, float maxEU, float rawValue);

private:

};
#endif // SCALER_H

