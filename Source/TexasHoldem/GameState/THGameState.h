// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TexasHoldem.h"
#include "THGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNotifyRestartGameSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedGamePlayStateSignature, const EGamePlayState, InGamePlayState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedCurrentTurnPlayerSignature, const ATHPlayerState*, InCurrentTurnPlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedBettingRoundSignature, const EBettingRound, InBettingRound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedCommunityCardsSignature, const TArray<FPlayingCard>&, InCommunityCards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedPlayersForTableSeattingPosSignature, const TArray<ATHPlayerState*>&, InPlayersForTableSeattingPos);

class ATHPlayerState;

UCLASS()
class TEXASHOLDEM_API ATHGameState : public AGameState
{
	GENERATED_BODY()

public:
	ATHGameState();

public:
    UFUNCTION()
    void Init();

protected:
    virtual void PostInitializeComponents() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaSeconds) override;

public:
    UFUNCTION(BlueprintPure)
    const int32 GetGamePlayCount() const;

    UFUNCTION(BlueprintPure)
    const int32 GetLoginPlayerCount() const;

    UFUNCTION(BlueprintPure)
    const int32 GetLogInGamePlayerCount() const;

    UFUNCTION(BlueprintPure)
    const EGamePlayState GetGamePlayState() const;

    UFUNCTION(BlueprintPure)
    ATHPlayerState* GetPlayerForPlayerRole(const EPlayerRole InPlayerRole) const;

    UFUNCTION(BlueprintPure)
    ATHPlayerState* GetCurrentTurnPlayer() const;

    UFUNCTION(BlueprintPure)
    TArray<ATHPlayerState*> GetWinnerPlayers() const;

    UFUNCTION(BlueprintPure)
    const EBettingRound GetBettingRound() const;

    UFUNCTION(BlueprintPure)
    const int32 GetBlindBettingMoney() const;

    UFUNCTION(BlueprintPure)
    const int32 GetTotalPotMoney() const;

    UFUNCTION(BlueprintPure)
    const int32 GetCallMoneyForCurrentPlayer() const;

    UFUNCTION(BlueprintPure)
    const int32 GetHighRoundBettingMoney() const;

    UFUNCTION(BlueprintPure)
    const int32 GetMinRaiseMoney() const;

    UFUNCTION(BlueprintPure)
    const bool IsAppeardRaiseAction() const;

    UFUNCTION(BlueprintPure)
    TArray<FPlayingCard> GetCommunityCards() const;

    UFUNCTION(BlueprintPure)
    TArray<ATHPlayerState*> GetPlayersForTableSeattingPos() const;

    UFUNCTION(BlueprintPure)
    TArray<ATHPlayerState*> GetInGamePlayersAll() const;

    UFUNCTION(BlueprintPure)
    TArray<ATHPlayerState*> GetInGameSurvivedPlayers() const;

    UFUNCTION(BlueprintPure)
    ATHPlayerState* GetNextInGamePlayer(ATHPlayerState* InCurrentPlayer) const;

    UFUNCTION(BlueprintPure)
    const float GetRemainBettingTimeSeconds() const;

    UFUNCTION(BlueprintCallable)
    void IncreaseGamePlayCount();

    UFUNCTION(BlueprintCallable)
    void InitGamePlayCount();

    UFUNCTION(BlueprintCallable)
    void SetGamePlayState(const EGamePlayState& InGamePlayState);

    UFUNCTION(BlueprintCallable)
    void SetCurrentTurnPlayer(ATHPlayerState* InCurrentTurnPlayer);

    UFUNCTION(BlueprintCallable)
    void SetWinnerPlayers(TArray<ATHPlayerState*> InWinnerPlayers);

    UFUNCTION(BlueprintCallable)
    void SetBettingRound(const EBettingRound& InBettingRound);

    UFUNCTION(BlueprintCallable)
    void SetBlindBettingMoney(const int32& InBlindBettingMoney);

    UFUNCTION(BlueprintCallable)
    void AddBlindBettingMoney(const int32& InBlindBettingMoney);

    UFUNCTION(BlueprintCallable)
    void SetTotalPotMoney(const int32& InTotalPotMoney);

    UFUNCTION(BlueprintCallable)
    void AddTotalPotMoney(const int32& InTotalPotMoney);

    UFUNCTION(BlueprintCallable)
    void SetCallMoneyForCurrentPlayer(const int32& InCallMoneyForCurrentPlayer);

    UFUNCTION(BlueprintCallable)
    void SetHighRoundBettingMoney(const int32& InHighRoundBettingMoney);

    UFUNCTION(BlueprintCallable)
    void SetMinRaiseMoney(const int32& InMinRaiseMoney);

    UFUNCTION(BlueprintCallable)
    void SetAppeardRaiseAction(const bool& bInApperedRaiseAction);

    UFUNCTION(BlueprintCallable)
    void SetCommunityCards(const TArray<FPlayingCard>& InCommunityCards);

    UFUNCTION(BlueprintCallable)
    void SetPlayersForTableSeattingPos(const TArray<ATHPlayerState*>& InPlayersForTableSeattingPos);

    UFUNCTION(BlueprintCallable)
    void SetInGamePlayersAll(const TArray<ATHPlayerState*>& InInGamePlayersAll);

    UFUNCTION(BlueprintCallable)
    void SetInGameSurvivedPlayers(const TArray<ATHPlayerState*>& InInGameSurvivedPlayers);

    UFUNCTION(BlueprintCallable)
    void RemoveInGameSurvivedPlayer(ATHPlayerState* InPlayerState);

public:
    UFUNCTION()
    void NotifyRestartGame();

    UFUNCTION()
    void OnRep_GamePlayState();

    UFUNCTION()
    void OnRep_CurrentTurnPlayer();

    UFUNCTION()
    void OnRep_BettingRound();

    UFUNCTION()
    void OnRep_CommunityCards();

    UFUNCTION()
    void OnRep_PlayersForTableSeattingPos();

    // Multicast
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SendNotifyRestartGame();
    void Multicast_SendNotifyRestartGame_Implementation();
    bool Multicast_SendNotifyRestartGame_Validate() { return true; }

private:
    // 게임 진행 횟수
    UPROPERTY(Replicated)
    int32 GamePlayCount = 0;

    // 현재 게임 상태
    UPROPERTY(ReplicatedUsing = OnRep_GamePlayState)
    EGamePlayState GamePlayState = EGamePlayState::None;

    // 현재 플레이어 턴
    UPROPERTY(ReplicatedUsing = OnRep_CurrentTurnPlayer)
    ATHPlayerState* CurrentTurnPlayer = nullptr;

    // 승리 플레이어
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> WinnerPlayers;

    // 베팅라운드
    UPROPERTY(ReplicatedUsing = OnRep_BettingRound)
    EBettingRound BettingRound = EBettingRound::None;

    // 블라인드 베팅 금액
    UPROPERTY(Replicated)
    int32 BlindBettingMoney = FirstBlindBettingMoney;

    // 총 팟 금액
    UPROPERTY(Replicated)
    int32 TotalPotMoney = 0;

    // 현재 턴 플레이어의 콜 금액
    UPROPERTY(Replicated)
    int32 CallMoneyForCurrentPlayer = 0;

    // 라운드 내 가장 높은 베팅 금액
    UPROPERTY(Replicated)
    int32 HighRoundBettingMoney = 0;

    // 레이즈에 필요한 금액
    UPROPERTY(Replicated)
    int32 MinRaiseMoney = 0;

    // 플레이어의 남은 베팅 제한시간
    UPROPERTY(Replicated)
    float RemainBettingTimeSeconds = RemainBettingTimerDelay;

    // 현재 라운드에 Raise 액션이 나왔는지
    UPROPERTY(Replicated)
    bool bAppeardRaiseAction = false;

    // 테이블에 펼쳐질 공유카드
    UPROPERTY(ReplicatedUsing = OnRep_CommunityCards)
    TArray<FPlayingCard> CommunityCards;

    // 테이블 자리에 따른 플레이어 정보
    UPROPERTY(ReplicatedUsing = OnRep_PlayersForTableSeattingPos)
    TArray<ATHPlayerState*> PlayersForTableSeattingPos;

    // 게임 진행중인 플레이어 전체
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> InGamePlayersAll;

    // 게임 내 살아남은 플레이어
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> InGameSurvivedPlayers;

public:
    // Restart Game 알림 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnNotifyRestartGameSignature OnNotifyRestartGame;

    // GamePlayState 변동알림 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnChangedGamePlayStateSignature OnChangedGamePlayState;

    // CurrentTurnPlayer 변동알림 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnChangedCurrentTurnPlayerSignature OnChangedCurrentTurnPlayer;

    // BettingRound 변동알림 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnChangedBettingRoundSignature OnChangedBettingRound;

    // CommunityCards 변동알림 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnChangedCommunityCardsSignature OnChangedCommunityCards;

    // PlayersForTableSeattingPos 변동알림 델리게이트
    UPROPERTY(BlueprintAssignable)
    FOnChangedPlayersForTableSeattingPosSignature OnChangedPlayersForTableSeattingPos;

public:
    // 플레이어의 베팅 제한시간을 카운팅하기 위한 타이머 핸들
    FTimerHandle RemainBettingTimerHandle;
};
