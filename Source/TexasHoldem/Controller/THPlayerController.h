// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Common/THStruct.h"
#include "Manager/THGamePlayManager.h"
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
	static const FName InputActionKeyBoard1;
	static const FName InputActionKeyBoard2;
	static const FName InputActionKeyBoard3;
	static const FName InputActionKeyBoard4;
	static const FName InputActionKeyBoard5;
	static const FName InputActionKeyBoard6;

public:
	ATHPlayerController();

public:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

public:
	virtual void Tick(float DeltaSeconds);

public:
	//UFUNCTION(Server, Reliable)
	void ActionSpaceBar();
	//bool ActionSpaceBar_Validate() { return true; }
	void ActionKeyBoard1();
	void ActionKeyBoard2();
	void ActionKeyBoard3();
	void ActionKeyBoard4();
	void ActionKeyBoard5();
	void ActionKeyBoard6();

	//UFUNCTION(NetMulticast, Reliable)
	//void MultiActionSpaceBar();
	//bool MultiActionSpaceBar_Validate() { return true; }

private:
	UPROPERTY()
    ATHPlayer* PossessedPlayer;

	UPROPERTY()
	UTHGamePlayManager* GamePlayMgr; //Debug
};
