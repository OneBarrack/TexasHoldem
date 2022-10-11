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
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	virtual void StartPlay() override;	

public:
	// 홀덤 스타트
	UFUNCTION(BlueprintCallable)
	void RestartTexasHoldem();

	// 플레이어 턴 부여
	UFUNCTION()
	void GiveTurnToPlayer(ATHPlayerState* BettingPlayer);

	// 플레이어 액션에 대한 노티를 받아 수행하는 로직
	UFUNCTION()
	void ReceiveNotifyPlayerAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney);

	// 플레이어 턴 종료 로직
	UFUNCTION()
	void ProceedPlayersTurnDone(ATHPlayerState* BettingPlayer, bool bTimeOut = false);

	// 로그아웃 예정인 플레이어 체크(나가기예약 or 보유금액 오링)
    UFUNCTION()
    void CheckExitPlayer();

private:
	// Related init	
	void AddPlayerInHoldemTable(ATHPlayerController* LoginPlayerController);
	void RemovePlayerInHoldemTable(ATHPlayerController* LogoutPlayerController);
    void InitBettingRound(const bool bAppearedRaiseAction = false, ATHPlayerState* RaisePlayer = nullptr);
    void InitSurvivedPlayersForBettingRound(ATHPlayerState* RaisePlayer = nullptr);

    // 스타트를 위한 로그인 플레이어 수 체크
    void CheckLoginPlayerCountForStartUp();

	// Dealer 포지션 기준으로 시계방향으로 가장 가까운 플레이어들을 순차적으로 GamePlayers에 적재 및 PlayerRole별 포지션 적재
	void ExtractOrderedInGamePlayers();
	
	// 올 Fold로 인한 단독승리, 게임종료
	void FinishGameForFoldAll();

	// Showdown을 통한 승자 플레이어 추출. 단독승리(Array Count : 1), else : 무승부
	void ProceedShowDown();
	void MarkingForLastBest5Cards(TArray<ATHPlayerState*>& Winners);
	void CalculatePotMoney(TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>>& PlayersForHandRankInfo);
	void CalculatePotMoneySingle(TArray<ATHPlayerState*>& PotPlayers, int32& RemainTotalPot);
	void CalculatePotMoneyChop(TArray<ATHPlayerState*>& PotPlayers, int32& RemainTotalPot);

    // 액션에 대한 Pot(테이블 머니) 계산
    void CalcPotMoneyForCheckAction(ATHPlayerState* BettingPlayer);
    void CalcPotMoneyForCallAction(ATHPlayerState* BettingPlayer, const int32 CallMoney);
    void CalcPotMoneyForRaiseAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney);
    void CalcPotMoneyForFoldAction(ATHPlayerState* BettingPlayer);

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

private:
	// Get() Set() For GameState, PlayerState
	// GameState
	const int32 GetLoginPlayerCount();
	const int32 GetGamePlayCount();
	const int32 GetBlindBettingMoney();
	const int32 GetTotalPotMoney();
	const EBettingRound GetBettingRound();
	const EGamePlayState GetGamePlayState();
	const bool IsAppeardRaiseAction();
    ATHPlayerState* GetPlayerForPlayerRole(const EPlayerRole InPlayerRole);
	ATHPlayerState* GetCurrentTurnPlayer();
	ATHPlayerState* GetNextInGamePlayer(ATHPlayerState* TargetPlayer);
	TArray<ATHPlayerState*> GetWinnerPlayers();
	TArray<ATHPlayerState*> GetPlayersForTableSeattingPos();
	TArray<ATHPlayerState*> GetInGamePlayersAll();
	TArray<ATHPlayerState*> GetInGameSurvivedPlayers();
	TArray<FPlayingCard> GetCommunityCards();

	void SetGamePlayState(EGamePlayState InGamePlayState);
	void SetBlindBettingMoney(const int InBlindBettingMoney);
	void IncreaseGamePlayCount();
	void SetBettingRound(const EBettingRound& InBettingRound);
	void SetCommunityCards(const TArray<FPlayingCard>& InCommunityCards);
	void SetHighRoundBettingMoney(const int32& InHighRoundBettingMoney);
	void AddTotalPotMoney(const int32& InTotalPotMoney);
	void SetMinRaiseMoney(const int32& InMinRaiseMoney);
	void SetAppeardRaiseAction(const bool& bInAppeardRaseAction);
	void SetCurrentTurnPlayer(ATHPlayerState* InCurrentTurnPlayer);
	void SetWinnerPlayers(const TArray<ATHPlayerState*>& InWinnerPlayers);
	void SetCallMoneyForCurrentPlayer(const int32& InCallMoneyForCurrentPlayer);
	void SetInGamePlayersAll(const TArray<ATHPlayerState*>& InInGamePlayers);
	void SetInGameSurvivedPlayers(const TArray<ATHPlayerState*>& InInGamePlayers);
	void SetPlayersForTableSeattingPos(const TArray<ATHPlayerState*>& InPlayersForTableSeattingPos);
	void RemoveInGameSurvivedPlayer(ATHPlayerState* InTargetPlayer);

	// PlayerState
	const bool GetPlayerReservedToExit(ATHPlayerState* TargetPlayer);
	const int32 GetPlayerMoney(ATHPlayerState* TargetPlayer);
	const int32 GetPlayerBettingMoney(ATHPlayerState* TargetPlayer);
	const int32 GetPlayerProfitMoney(ATHPlayerState* TargetPlayer);
	const int32 GetPlayerRequiredMoneyForCall(ATHPlayerState* TargetPlayer);
	const int32 GetPlayerRoundBettingMoney(ATHPlayerState* TargetPlayer);
	const int32 GetPlayerTableSeattingPos(ATHPlayerState* TargetPlayer);
	ATHPlayerController* GetPlayerController(ATHPlayerState* TargetPlayer);
	const EPlayerAction GetPlayerAction(ATHPlayerState* TargetPlayer);
	const EPlayerTurnState GetPlayerTurnState(ATHPlayerState* TargetPlayer);
	const FString GetPlayerNickName(ATHPlayerState* TargetPlayer);
	const FPlayerHandRankInfo GetPlayerHandRankInfo(ATHPlayerState* TargetPlayer);
	TArray<FPlayingCard> GetPlayerHandCards(ATHPlayerState* TargetPlayer);

    void SetPlayerRole(ATHPlayerState* TargetPlayer, EPlayerRole& PlayerRole);
	void SetPlayerHandCards(ATHPlayerState* TargetPlayer, const TArray<FPlayingCard>& InHandCards);
	void SetPlayerRoundBettingMoney(ATHPlayerState* TargetPlayer, const int32 InRoundBettingMoney);
	void AddPlayerRoundBettingMoney(ATHPlayerState* TargetPlayer, const int32 InRoundBettingMoney);
	void SetPlayerBettingMoney(ATHPlayerState* TargetPlayer, const int32 InRoundBettingMoney);
	void SetPlayerTurnState(ATHPlayerState* TargetPlayer, const EPlayerTurnState& InPlayerTurnState);
	void AddPlayerMoney(ATHPlayerState* TargetPlayer, const int32 InMoney);
	void SetPlayerMoney(ATHPlayerState* TargetPlayer, const int32 InMoney);
	void SetPlayerNickName(ATHPlayerState* TargetPlayer, const FString InName);
	void SetPlayerAction(ATHPlayerState* TargetPlayer, const EPlayerAction& InPlayerAction);	
	void SetPlayerProfitMoney(ATHPlayerState* TargetPlayer, const int32 InProfitMoney);
	void SetPlayerHandRankInfo(ATHPlayerState* TargetPlayer, const FPlayerHandRankInfo& InHandRankInfo);
	void SetPlayerTableSeattingPos(ATHPlayerState* TargetPlayer, const int32 InTableSeattingPos);

	bool IsPlayerReady(ATHPlayerState* TargetPlayer);

public:
	// 2인(1대1) 매치인지
	UPROPERTY()
	bool bIsOneOnOneMatch = false;

	// 베팅 라운드가 종료되었는지
	UPROPERTY()
	bool bIsBettingRoundEnded = false;

    // 테이블 내 Dealer 포지션
    UPROPERTY()
    int32 DealerPosForTable = -1;

private:    
	// 게임스테이트
    UPROPERTY()
    ATHGameState* THGameState = nullptr;

    // 게임 플레이 매니저
    UPROPERTY()
    UTHHoldemPlayManager* GamePlayManager = nullptr;

    // 사이클 별 필요한 시간 갭을 두기위한 타이머 핸들	
    FTimerHandle CycleTimerHandle;

    // Showdown 이후 퇴장 플레이어 체크 로직을 수행하기 까지의 시간 갭을 두기위한 타이머 핸들
    FTimerHandle CheckExitTimerHandle;

public:
	FORCEINLINE UTHHoldemPlayManager* GetGamePlayManager() { return GamePlayManager; }
};
