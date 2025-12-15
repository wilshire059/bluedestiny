#include "CS_Boss_Roar.h"

UCS_Boss_Roar::UCS_Boss_Roar()
{
	OscillationDuration = 0.5f;

	// Rotation oscillation - strong shake for boss roar
	RotOscillation.Pitch.Amplitude = 5.0f;
	RotOscillation.Pitch.Frequency = 3.0f;
	RotOscillation.Yaw.Amplitude = 5.0f;
	RotOscillation.Yaw.Frequency = 4.0f;
	RotOscillation.Roll.Amplitude = 3.0f;
	RotOscillation.Roll.Frequency = 2.0f;

	// Location oscillation
	LocOscillation.X.Amplitude = 15.0f;
	LocOscillation.X.Frequency = 3.0f;
	LocOscillation.Y.Amplitude = 10.0f;
	LocOscillation.Y.Frequency = 4.0f;
	LocOscillation.Z.Amplitude = 5.0f;
	LocOscillation.Z.Frequency = 2.0f;

	// FOV oscillation
	FOVOscillation.Amplitude = 2.0f;
	FOVOscillation.Frequency = 2.0f;
}
