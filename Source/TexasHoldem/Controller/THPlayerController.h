// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "THPlayerController.generated.h"

class ATHPlayer;

/** PlayerController class used to enable cursor */
UCLASS()
class ATHPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	static const FName InputActionMouseLeft;
	static const FName InputActionSpaceBar;

public:
	ATHPlayerController();

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

public:
	//UFUNCTION(Server, Reliable)
	//void ActionSpaceBar();
	//bool ActionSpaceBar_Validate() { return true; }

	//UFUNCTION(NetMulticast, Reliable)
	//void MultiActionSpaceBar();
	//bool MultiActionSpaceBar_Validate() { return true; }

private:
    ATHPlayer* PossessedPlayer;
};
