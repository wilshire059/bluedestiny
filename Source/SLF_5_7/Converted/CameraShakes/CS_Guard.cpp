#include "CS_Guard.h"

UCS_Guard::UCS_Guard()
{
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.02f;
	OscillationBlendOutTime = 0.1f;

	// Rotation oscillation - quick, sharp shake for blocking
	RotOscillation.Pitch.Amplitude = 5.0f;
	RotOscillation.Pitch.Frequency = 25.0f;
	RotOscillation.Yaw.Amplitude = 7.0f;
	RotOscillation.Yaw.Frequency = 30.0f;
	RotOscillation.Roll.Amplitude = 3.0f;
	RotOscillation.Roll.Frequency = 20.0f;

	// Location oscillation
	LocOscillation.X.Amplitude = 2.0f;
	LocOscillation.X.Frequency = 20.0f;
	LocOscillation.Y.Amplitude = 1.5f;
	LocOscillation.Y.Frequency = 25.0f;
	LocOscillation.Z.Amplitude = 3.0f;
	LocOscillation.Z.Frequency = 30.0f;

	// FOV oscillation
	FOVOscillation.Amplitude = 2.0f;
	FOVOscillation.Frequency = 15.0f;
}
