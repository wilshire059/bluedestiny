#include "CS_SubtleHit.h"

UCS_SubtleHit::UCS_SubtleHit()
{
	OscillationDuration = 0.2f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	// Rotation oscillation
	RotOscillation.Pitch.Amplitude = 0.5f;
	RotOscillation.Pitch.Frequency = 10.0f;
	RotOscillation.Yaw.Amplitude = 0.5f;
	RotOscillation.Yaw.Frequency = 8.0f;
	RotOscillation.Roll.Amplitude = 0.3f;
	RotOscillation.Roll.Frequency = 8.0f;

	// Location oscillation
	LocOscillation.X.Amplitude = 0.1f;
	LocOscillation.X.Frequency = 5.0f;
	LocOscillation.Y.Amplitude = 0.1f;
	LocOscillation.Y.Frequency = 5.0f;
	LocOscillation.Z.Amplitude = 0.2f;
	LocOscillation.Z.Frequency = 5.0f;

	// FOV oscillation
	FOVOscillation.Amplitude = 0.1f;
	FOVOscillation.Frequency = 5.0f;
}
