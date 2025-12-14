// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDA_Calculations.h"

UPDA_Calculations::UPDA_Calculations()
{
	CalculationType = E_CalculationType::Multiply;
}

void UPDA_Calculations::Calculate(double Modifier, double ChangeAmount, double& OutChange)
{
	switch (CalculationType)
	{
	case E_CalculationType::Multiply:
		OutChange = Modifier * ChangeAmount;
		break;
	default:
		OutChange = 0.0;
		break;
	}
}
