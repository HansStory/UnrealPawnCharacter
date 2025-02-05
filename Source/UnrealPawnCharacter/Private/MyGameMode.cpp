#include "MyGameMode.h"
#include "PawnCharacter.h"
#include "PawnCharacterPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = APawnCharacter::StaticClass();
	PlayerControllerClass = APawnCharacterPlayerController::StaticClass();

}