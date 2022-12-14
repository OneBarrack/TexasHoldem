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
    TArray<int32> GetForceLogoutPlayersBetMoneyList() const;    

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

    UFUNCTION(BlueprintCallable)
    void AddForceLogoutPlayersBetMoney(const int32& InForceLogoutPlayersBetMoney);

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
    // ???? ???? ????
    UPROPERTY(Replicated)
    int32 GamePlayCount = 0;

    // ???? ???? ????
    UPROPERTY(ReplicatedUsing = OnRep_GamePlayState)
    EGamePlayState GamePlayState = EGamePlayState::None;

    // ???? ???????? ??
    UPROPERTY(ReplicatedUsing = OnRep_CurrentTurnPlayer)
    ATHPlayerState* CurrentTurnPlayer = nullptr;

    // ???? ????????
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> WinnerPlayers;

    // ??????????
    UPROPERTY(ReplicatedUsing = OnRep_BettingRound)
    EBettingRound BettingRound = EBettingRound::None;

    // ???????? ???? ????
    UPROPERTY(Replicated)
    int32 BlindBettingMoney = FirstBlindBettingMoney;

    // ?? ?? ????
    UPROPERTY(Replicated)
    int32 TotalPotMoney = 0;

    // ???? ?? ?????????? ?? ????
    UPROPERTY(Replicated)
    int32 CallMoneyForCurrentPlayer = 0;

    // ?????? ?? ???? ???? ???? ????
    UPROPERTY(Replicated)
    int32 HighRoundBettingMoney = 0;

    // ???????? ?????? ????
    UPROPERTY(Replicated)
    int32 MinRaiseMoney = 0;

    // ?????????? ???? ???? ????????
    UPROPERTY(Replicated)
    float RemainBettingTimeSeconds = RemainBettingTimerDelay;

    // ???? ???????? Raise ?????? ????????
    UPROPERTY(Replicated)
    bool bAppeardRaiseAction = false;

    // ???????? ?????? ????????
    UPROPERTY(ReplicatedUsing = OnRep_CommunityCards)
    TArray<FPlayingCard> CommunityCards;

    // ?????? ?????? ???? ???????? ????
    UPROPERTY(ReplicatedUsing = OnRep_PlayersForTableSeattingPos)
    TArray<ATHPlayerState*> PlayersForTableSeattingPos;

    // ???? ???????? ???????? ????
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> InGamePlayersAll;

    // ???? ?? ???????? ????????
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> InGameSurvivedPlayers;

    // ?????? ?????? ?? ???? ?????? ???????????? ????????
    UPROPERTY(Replicated)
    TArray<int32> ForceLogoutPlayersBetMoneyList;

public:
    // Restart Game ???? ??????????
    UPROPERTY(BlueprintAssignable)
    FOnNotifyRestartGameSignature OnNotifyRestartGame;

    // GamePlayState ???????? ??????????
    UPROPERTY(BlueprintAssignable)
    FOnChangedGamePlayStateSignature OnChangedGamePlayState;

    // CurrentTurnPlayer ???????? ??????????
    UPROPERTY(BlueprintAssignable)
    FOnChangedCurrentTurnPlayerSignature OnChangedCurrentTurnPlayer;

    // BettingRound ???????? ??????????
    UPROPERTY(BlueprintAssignable)
    FOnChangedBettingRoundSignature OnChangedBettingRound;

    // CommunityCards ???????? ??????????
    UPROPERTY(BlueprintAssignable)
    FOnChangedCommunityCardsSignature OnChangedCommunityCards;

    // PlayersForTableSeattingPos ???????? ??????????
    UPROPERTY(BlueprintAssignable)
    FOnChangedPlayersForTableSeattingPosSignature OnChangedPlayersForTableSeattingPos;

public:
    // ?????????? ???? ?????????? ?????????? ???? ?????? ????
    FTimerHandle RemainBettingTimerHandle;
};
