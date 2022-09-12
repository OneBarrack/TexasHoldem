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

	// Dealer 포지션 기준으로 시계방향으로 가장 가까운 플레이어들을 순차적으로 GamePlayers에 적재 및 PlayerRole별 포지션 적재
	void ExtractOrderedInGamePlayers();
	void SetPlayerForPlayerRole(ATHPlayerState* TargetPlayer, EPlayerRole& PlayerRole); 

	// 승자 추출 : 단독승리(Array Count : 1)
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

    // 액션에 대한 Pot(테이블 머니) 계산
    void CalcPotMoneyForCheckAction(ATHPlayerState* BettingPlayer);
    void CalcPotMoneyForCallAction(ATHPlayerState* BettingPlayer, const int32 CallMoney);
    void CalcPotMoneyForRaiseAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney);
    void CalcPotMoneyForFoldAction(ATHPlayerState* BettingPlayer);

public:
	// 2인(1대1) 매치인지
	UPROPERTY()
	bool bIsOneOnOneMatch = false;

	// 베팅 라운드가 종료되었는지
	UPROPERTY()
	bool bIsBettingRoundEnded = false;

    // 우승 플레이어
    UPROPERTY()
    TArray<ATHPlayerState*> WinnerPlayers;

private:    
	// 게임스테이트
    UPROPERTY()
    ATHGameState* THGameState = nullptr;

    // Showdown 이후 FinishiUp 넘어가기까지 대기시간 타이머
    FTimerHandle ShowdownTimerHandle;
	float ShowdownTimerDelay = 3.0f;

	// 게임 플레이 매니저
    UPROPERTY()
    UTHHoldemPlayManager* GamePlayManager = nullptr;

public:
	FORCEINLINE UTHHoldemPlayManager* GetGamePlayManager() { return GamePlayManager; }
};
