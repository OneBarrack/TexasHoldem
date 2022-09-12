// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TexasHoldem.h"
#include "Manager/THHoldemPlayManager.h"
#include "THPlayerController.generated.h"

class ATHGameMode;
class ATHGameState;
class ATHPlayerState;
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
	static const FName InputActionKeyReady;

public:
    ATHPlayerController();

public:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

protected:
	virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    void Init();

    ATHGameMode* GetGameMode() const;
	ATHGameState* GetGameState() const;
	ATHPlayerState* GetPlayerState() const;
    ATHPlayer* GetPlayerPawn() const;

public:
    UFUNCTION(BlueprintCallable)
    const FPlayerActionActivateInfo GetPlayerActionActivateInfo();

    UFUNCTION(BlueprintCallable)
    void CheckForActionActivate();

	UFUNCTION(BlueprintCallable)
	void ToggleReadyState();

    UFUNCTION(BlueprintCallable)
    void ActionQuarter();

    UFUNCTION(BlueprintCallable)
    void ActionHalf();

    UFUNCTION(BlueprintCallable)
    void ActionFull();

    UFUNCTION(BlueprintCallable)
    void ActionRaise(const int32 RaiseMoney);

    UFUNCTION(BlueprintCallable)
    void ActionAllin();

	UFUNCTION(BlueprintCallable)
	void ActionCheck();

	UFUNCTION(BlueprintCallable)
	void ActionCall();

	UFUNCTION(BlueprintCallable)
	void ActionFold();

private:
	// Server
    UFUNCTION(Server, Reliable)
    void Server_ToggleReadyState();
    void Server_ToggleReadyState_Implementation();
    bool Server_ToggleReadyState_Validate() { return true; }

    UFUNCTION(Server, Reliable)
    void Server_SendNotifyPlayerAction(const EPlayerAction& InPlayerAction, int32 CallMoney = 0, int32 RaiseMoney = 0);
	void Server_SendNotifyPlayerAction_Implementation(const EPlayerAction& InPlayerAction, int32 CallMoney = 0, int32 RaiseMoney = 0);
	bool Server_SendNotifyPlayerAction_Validate(const EPlayerAction& InPlayerAction, int32 CallMoney = 0, int32 RaiseMoney = 0) { return true; }

public: /* Debeg¿ë */    
    //UFUNCTION(Server, Reliable)
    void ActionSpaceBar();
    //bool ActionSpaceBar_Validate() { return true; }
    void ActionKeyBoard1();
    void ActionKeyBoard2();
    void ActionKeyBoard3();
    void ActionKeyBoard4();
    void ActionKeyBoard5();
    void ActionKeyBoard6();
    void ActionKeyReady();
    
    UPROPERTY()
    UTHHoldemPlayManager* GamePlayMgr = nullptr; //Debug    
    /////////////////////////

private:
    UPROPERTY(replicated)
    FPlayerActionActivateInfo PlayerActionActivateInfo;

	UPROPERTY()
    ATHPlayer* PossessedPlayer = nullptr;
};
