#include "PawnCharacterPlayerController.h"
#include "EnhancedInputSubsystems.h"

APawnCharacterPlayerController::APawnCharacterPlayerController()
	:InputMappingContext(nullptr), MoveAction(nullptr), LookAction(nullptr) {}

void APawnCharacterPlayerController::BeginPlay()
{
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

}

