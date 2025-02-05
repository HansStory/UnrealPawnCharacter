#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnCharacterPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class UNREALPAWNCHARACTER_API APawnCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APawnCharacterPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;
	
protected:
	virtual void BeginPlay() override;
};
