#include "CS_StrongHit.h"

UCS_StrongHit::UCS_StrongHit()
{
	OscillationDuration = 0.4f;
	OscillationBlendInTime = 0.05f;

	// Rotation oscillation - strong impact shake
	RotOscillation.Pitch.Amplitude = 3.0f;
	RotOscillation.Pitch.Frequency = 8.0f;
	RotOscillation.Yaw.Amplitude = 2.0f;
	RotOscillation.Yaw.Frequency = 6.0f;
	RotOscillation.Roll.Amplitude = 1.5f;
	RotOscillation.Roll.Frequency = 5.0f;

	// Location oscillation
	LocOscillation.X.Amplitude = 0.5f;
	LocOscillation.X.Frequency = 5.0f;
	LocOscillation.Y.Amplitude = 0.5f;
	LocOscillation.Y.Frequency = 5.0f;
	LocOscillation.Z.Amplitude = 0.5f;
	LocOscillation.Z.Frequency = 6.0f;

	// FOV oscillation
	FOVOscillation.Amplitude = 0.5f;
	FOVOscillation.Frequency = 6.0f;
}
