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
	// Ȧ�� ��ŸƮ
	UFUNCTION(BlueprintCallable)
	void RestartTexasHoldem();

	// �÷��̾� �� �ο�
	UFUNCTION()
	void GiveTurnToPlayer(ATHPlayerState* BettingPlayer);

	// �÷��̾� �׼ǿ� ���� ��Ƽ�� �޾� �����ϴ� ����
	UFUNCTION()
	void ReceiveNotifyPlayerAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney);

	// �÷��̾� �� ���� ����
	UFUNCTION()
	void ProceedPlayersTurnDone(ATHPlayerState* BettingPlayer, bool bTimeOut = false);

	// �α׾ƿ� ������ �÷��̾� üũ(�����⿹�� or �����ݾ� ����)
    UFUNCTION()
    void CheckExitPlayer();

private:
	// Related init	
	void AddPlayerInHoldemTable(ATHPlayerController* LoginPlayerController);
	void RemovePlayerInHoldemTable(ATHPlayerController* LogoutPlayerController);
    void InitBettingRound(const bool bAppearedRaiseAction = false, ATHPlayerState* RaisePlayer = nullptr);
    void InitSurvivedPlayersForBettingRound(ATHPlayerState* RaisePlayer = nullptr);

    // ��ŸƮ�� ���� �α��� �÷��̾� �� üũ
    void CheckLoginPlayerCountForStartUp();

	// Dealer ������ �������� �ð�������� ���� ����� �÷��̾���� ���������� GamePlayers�� ���� �� PlayerRole�� ������ ����
	void ExtractOrderedInGamePlayers();
	
	// �� Fold�� ���� �ܵ��¸�, ��������
	void FinishGameForFoldAll();

	// Showdown�� ���� ���� �÷��̾� ����. �ܵ��¸�(Array Count : 1), else : ���º�
	void ProceedShowDown();
	void MarkingForLastBest5Cards(TArray<ATHPlayerState*>& Winners);
	void CalculatePotMoney(TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>>& PlayersForHandRankInfo);
	void CalculatePotMoneySingle(TArray<ATHPlayerState*>& PotPlayers, int32& RemainTotalPot);
	void CalculatePotMoneyChop(TArray<ATHPlayerState*>& PotPlayers, int32& RemainTotalPot);

    // �׼ǿ� ���� Pot(���̺� �Ӵ�) ���
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
	// 2��(1��1) ��ġ����
	UPROPERTY()
	bool bIsOneOnOneMatch = false;

	// ���� ���尡 ����Ǿ�����
	UPROPERTY()
	bool bIsBettingRoundEnded = false;

    // ���̺� �� Dealer ������
    UPROPERTY()
    int32 DealerPosForTable = -1;

private:    
	// ���ӽ�����Ʈ
    UPROPERTY()
    ATHGameState* THGameState = nullptr;

    // ���� �÷��� �Ŵ���
    UPROPERTY()
    UTHHoldemPlayManager* GamePlayManager = nullptr;

    // ����Ŭ �� �ʿ��� �ð� ���� �α����� Ÿ�̸� �ڵ�	
    FTimerHandle CycleTimerHandle;

    // Showdown ���� ���� �÷��̾� üũ ������ �����ϱ� ������ �ð� ���� �α����� Ÿ�̸� �ڵ�
    FTimerHandle CheckExitTimerHandle;

public:
	FORCEINLINE UTHHoldemPlayManager* GetGamePlayManager() { return GamePlayManager; }
};
