#include "BFL_Helper.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

TArray<FKey> UBFL_Helper::GetKeysForIA(UInputMappingContext* InputMapping, UInputAction* TargetIA)
{
	TArray<FKey> MappedKeys;

	if (!InputMapping || !TargetIA)
	{
		return MappedKeys;
	}

	// Get all mappings from the context
	const TArray<FEnhancedActionKeyMapping>& Mappings = InputMapping->GetMappings();

	for (const FEnhancedActionKeyMapping& Mapping : Mappings)
	{
		if (Mapping.Action == TargetIA)
		{
			MappedKeys.Add(Mapping.Key);
		}
	}

	return MappedKeys;
}
