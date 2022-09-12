// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TexasHoldem.h"
#include "GameFramework/GameMode.h"
#include "Manager/THHoldemPlayManager.h"
#include "THGameMode.generated.h"

class ATHGameState;
class ATHPlayerState;
class ATHPlayerController;

UCLASS()
class TEXASHOLDEM_API ATHGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ATHGameMode();

protected:
	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	virtual void StartPlay() override;	

public:
	void Init();
	void RestartTexasHoldem();
	void GiveTurnToPlayer(ATHPlayerState* BettingPlayer);
	void ReceiveNotifyPlayerAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney);

private:
	// Related init
    void InitBettingRound(bool bNotifyRaiseAction = false);
	void InitSurvivedPlayersForBettingRound(bool bNotifyRaiseAction);

	void SetGamePlayState(EGamePlayState InGamePlayState);
	void AddPlayerInHoldemTable(ATHPlayerController* LoginPlayerController);
	void RemovePlayerInHoldemTable(ATHPlayerController* LogoutPlayerController);
	bool IsReadyForAllPlayers();

	// Dealer ������ �������� �ð�������� ���� ����� �÷��̾���� ���������� GamePlayers�� ���� �� PlayerRole�� ������ ����
	void ExtractOrderedInGamePlayers();
	void SetPlayerForPlayerRole(ATHPlayerState* TargetPlayer, EPlayerRole& PlayerRole); 

	// ���� ���� : �ܵ��¸�(Array Count : 1)
	TArray<ATHPlayerState*> ExtractWinners();
	void CalculatePotMoney(TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>>& PlayersForHandRankInfo);
	void CalculatePotMoneySingle(TArray<ATHPlayerState*>& PotPlayers, int32& PrevMaxBettingMoney, int32& RemainTotalPot);
	void CalculatePotMoneyChop(TArray<ATHPlayerState*>& PotPlayers, int32& PrevMaxBettingMoney, int32& RemainTotalPot);

private:
    // Play Cycle
    void RunPlayCycle();
    void RunPlayCyclePrepare();
    void RunPlayCycleStartUp();
    void RunPlayCyclePreFlop();
    void RunPlayCycleFlop();
    void RunPlayCycleTurn();
    void RunPlayCycleRiver();
    void RunPlayCycleShowdown();
    void RunPlayCycleFinishUp();
    void RunPlayCycleBetting();

    // �׼ǿ� ���� Pot(���̺� �Ӵ�) ���
    void CalcPotMoneyForCheckAction(ATHPlayerState* BettingPlayer);
    void CalcPotMoneyForCallAction(ATHPlayerState* BettingPlayer, const int32 CallMoney);
    void CalcPotMoneyForRaiseAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney);
    void CalcPotMoneyForFoldAction(ATHPlayerState* BettingPlayer);

public:
	// 2��(1��1) ��ġ����
	UPROPERTY()
	bool bIsOneOnOneMatch = false;

	// ���� ���尡 ����Ǿ�����
	UPROPERTY()
	bool bIsBettingRoundEnded = false;

    // ��� �÷��̾�
    UPROPERTY()
    TArray<ATHPlayerState*> WinnerPlayers;

private:    
	// ���ӽ�����Ʈ
    UPROPERTY()
    ATHGameState* THGameState = nullptr;

    // Showdown ���� FinishiUp �Ѿ����� ���ð� Ÿ�̸�
    FTimerHandle ShowdownTimerHandle;
	float ShowdownTimerDelay = 3.0f;

	// ���� �÷��� �Ŵ���
    UPROPERTY()
    UTHHoldemPlayManager* GamePlayManager = nullptr;

public:
	FORCEINLINE UTHHoldemPlayManager* GetGamePlayManager() { return GamePlayManager; }
};
