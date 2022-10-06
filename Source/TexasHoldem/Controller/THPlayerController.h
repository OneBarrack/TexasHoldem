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
    virtual void Destroyed() override;

protected:
	virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    UFUNCTION(BlueprintCallable)
    void Init();

    UFUNCTION(BlueprintPure)
    ATHGameMode* GetGameMode() const;

    UFUNCTION(BlueprintPure)
	ATHGameState* GetGameState() const;

    UFUNCTION(BlueprintPure)
	ATHPlayerState* GetPlayerState() const;

    UFUNCTION(BlueprintPure)
    ATHPlayer* GetPlayerPawn() const;

    // 게임 종료
    UFUNCTION()
    void ExitGame();

    UFUNCTION(BlueprintImplementableEvent)
    void BP_ExitGame();

public:
    UFUNCTION(BlueprintCallable)
    void SetPlayerSaveData(const FPlayerSaveData& InPlayerSaveData);

    UFUNCTION(BlueprintCallable)
    const FPlayerActionActivateInfo GetPlayerActionActivateInfo();

    UFUNCTION(BlueprintCallable)
    void CheckForActionActivate();

	UFUNCTION(BlueprintCallable)
	void ToggleReservedToExitState();

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

private: // RPC
	// Server
    UFUNCTION(Server, Reliable)
    void Server_ToggleReservedToExitState();
    void Server_ToggleReservedToExitState_Implementation();
    bool Server_ToggleReservedToExitState_Validate() { return true; }

    UFUNCTION(Server, Reliable)
    void Server_SendNotifyPlayerAction(const EPlayerAction& InPlayerAction, int32 CallMoney = 0, int32 RaiseMoney = 0);
	void Server_SendNotifyPlayerAction_Implementation(const EPlayerAction& InPlayerAction, int32 CallMoney = 0, int32 RaiseMoney = 0);
	bool Server_SendNotifyPlayerAction_Validate(const EPlayerAction& InPlayerAction, int32 CallMoney = 0, int32 RaiseMoney = 0) { return true; }
    
    UFUNCTION(Server, Reliable)
    void Server_SetGamePause(const bool bPaused);
    void Server_SetGamePause_Implementation(const bool bPaused);
    bool Server_SetGamePause_Validate(const bool bPaused) { return true; }

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void Server_SetPlayerSaveData(const FPlayerSaveData& InPlayerSaveData);
    void Server_SetPlayerSaveData_Implementation(const FPlayerSaveData& InPlayerSaveData);
    bool Server_SetPlayerSaveData_Validate(const FPlayerSaveData& InPlayerSaveData) { return true; }

    // Client
    UFUNCTION(Client, Reliable)
    void Client_SendNotifyExitGame();
    void Client_SendNotifyExitGame_Implementation();
    bool Client_SendNotifyExitGame_Validate() { return true; }

public: // Debug
    /************** For Debug **************/
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
    UFUNCTION(BlueprintCallable)
    void ChangeHUDWidget(TSubclassOf<UUserWidget> NewHUDWidgetClass);
    /******************************************/

private:
    UPROPERTY(replicated)
    FPlayerActionActivateInfo PlayerActionActivateInfo;

    UPROPERTY()
    UUserWidget* CurrentHUDWidget = nullptr;

	UPROPERTY()
    ATHPlayer* PossessedPlayer = nullptr;
};
