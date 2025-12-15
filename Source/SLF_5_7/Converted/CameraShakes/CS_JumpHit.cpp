#include "CS_JumpHit.h"

UCS_JumpHit::UCS_JumpHit()
{
	OscillationDuration = 0.3f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.1f;

	// Rotation oscillation - medium shake for jumping attack hits
	RotOscillation.Pitch.Amplitude = 1.5f;
	RotOscillation.Pitch.Frequency = 10.0f;
	RotOscillation.Yaw.Amplitude = 1.0f;
	RotOscillation.Yaw.Frequency = 8.0f;
	RotOscillation.Roll.Amplitude = 1.0f;
	RotOscillation.Roll.Frequency = 8.0f;

	// Location oscillation
	LocOscillation.X.Amplitude = 0.3f;
	LocOscillation.X.Frequency = 5.0f;
	LocOscillation.Y.Amplitude = 0.3f;
	LocOscillation.Y.Frequency = 5.0f;
	LocOscillation.Z.Amplitude = 0.5f;
	LocOscillation.Z.Frequency = 6.0f;

	// FOV oscillation
	FOVOscillation.Amplitude = 0.3f;
	FOVOscillation.Frequency = 4.0f;
}
