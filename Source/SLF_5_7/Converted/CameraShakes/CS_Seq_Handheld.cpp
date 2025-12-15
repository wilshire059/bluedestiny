#include "CS_Seq_Handheld.h"

UCS_Seq_Handheld::UCS_Seq_Handheld()
{
	// Handheld camera feel - subtle, continuous movement
	OscillationDuration = 0.0f; // Infinite duration for sequences
	bSingleInstance = true;

	// Very subtle rotation for handheld feel
	RotOscillation.Pitch.Amplitude = 0.3f;
	RotOscillation.Pitch.Frequency = 1.5f;
	RotOscillation.Yaw.Amplitude = 0.2f;
	RotOscillation.Yaw.Frequency = 1.0f;
	RotOscillation.Roll.Amplitude = 0.15f;
	RotOscillation.Roll.Frequency = 0.8f;

	// Subtle location shake
	LocOscillation.X.Amplitude = 0.1f;
	LocOscillation.X.Frequency = 1.0f;
	LocOscillation.Y.Amplitude = 0.1f;
	LocOscillation.Y.Frequency = 0.8f;
	LocOscillation.Z.Amplitude = 0.15f;
	LocOscillation.Z.Frequency = 1.2f;
}
