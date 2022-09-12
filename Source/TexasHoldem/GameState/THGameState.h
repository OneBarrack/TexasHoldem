// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TexasHoldem.h"
#include "THGameState.generated.h"

class ATHPlayerState;

UCLASS()
class TEXASHOLDEM_API ATHGameState : public AGameState
{
	GENERATED_BODY()

public:
	ATHGameState();

public:
    void Init();

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    UFUNCTION(BlueprintPure)
    const int32 GetGamePlayCount() const;

    UFUNCTION(BlueprintPure)
    const int32 GetLoginUserCount() const;

    UFUNCTION(BlueprintPure)
    const int32 GetLogInGamePlayerCount() const;

    UFUNCTION(BlueprintPure)
    const EGamePlayState GetGamePlayState() const;

    UFUNCTION(BlueprintPure)
    ATHPlayerState* GetPlayerForPlayerRole(const EPlayerRole InPlayerRole) const;

    UFUNCTION(BlueprintPure)
    ATHPlayerState* GetCurrentTurnPlayer() const;

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
    TArray<ATHPlayerState*> GetPlayersForTable() const;

    UFUNCTION(BlueprintPure)
    TArray<ATHPlayerState*> GetInGamePlayersAll() const;

    UFUNCTION(BlueprintPure)
    TArray<ATHPlayerState*> GetInGameSurvivedPlayers() const;

    UFUNCTION(BlueprintPure)
    ATHPlayerState* GetNextInGamePlayer(ATHPlayerState* InCurrentPlayer) const;

    UFUNCTION(BlueprintCallable)
    void IncreaseGamePlayCount();

    UFUNCTION(BlueprintCallable)
    void SetPlayerForPlayerRole(ATHPlayerState* InTHPlayerState, const EPlayerRole& InPlayerRole);

    UFUNCTION(BlueprintCallable)
    void SetGamePlayState(const EGamePlayState& InGamePlayState);

    UFUNCTION(BlueprintCallable)
    void SetCurrentTurnPlayer(ATHPlayerState* InCurrentTurnPlayer);

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
    void SetPlayersForTable(const TArray<ATHPlayerState*>& InPlayersForTableSeattingPos);

    UFUNCTION(BlueprintCallable)
    void SetInGamePlayersAll(const TArray<ATHPlayerState*>& InInGamePlayersAll);

    UFUNCTION(BlueprintCallable)
    void SetInGameSurvivedPlayers(const TArray<ATHPlayerState*>& InInGameSurvivedPlayers);

    UFUNCTION(BlueprintCallable)
    void RemovePlayerInGamePlayers(ATHPlayerState* InPlayerState);
    
private:
    // ���� ���� Ƚ��
    UPROPERTY(Replicated)
    int32 GamePlayCount = 0;

    // ���� ���� ����
    UPROPERTY(Replicated)
    EGamePlayState GamePlayState = EGamePlayState::None;

    // Dealer �÷��̾�
    UPROPERTY(Replicated)
    ATHPlayerState* DealerPlayer = nullptr;

    // SmallBlind �÷��̾�
    UPROPERTY(Replicated)
    ATHPlayerState* SmallBlindPlayer = nullptr;

    // BigBlind �÷��̾�
    UPROPERTY(Replicated)
    ATHPlayerState* BigBlindPlayer = nullptr;

    // ���� �÷��̾� ��
    UPROPERTY(Replicated)
    ATHPlayerState* CurrentTurnPlayer = nullptr;

    // ���ö���
    UPROPERTY(Replicated)
    EBettingRound BettingRound = EBettingRound::None;

    // ����ε� ���� �ݾ�
    UPROPERTY(Replicated)
    int32 BlindBettingMoney = FirstBlindBettingMoney;

    // �� �� �ݾ�
    UPROPERTY(Replicated)
    int32 TotalPotMoney = 0;

    // ���� �� �÷��̾��� �� �ݾ�
    UPROPERTY(Replicated)
    int32 CallMoneyForCurrentPlayer = 0;

    // ���� �� ���� ���� ���� �ݾ�
    UPROPERTY(Replicated)
    int32 HighRoundBettingMoney = 0;

    // ����� �ʿ��� �ݾ�
    UPROPERTY(Replicated)
    int32 MinRaiseMoney = 0;

    // ���� ���忡 Raise �׼��� ���Դ���
    UPROPERTY(Replicated)
    bool bAppeardRaiseAction = false;

    // ���̺� ������ ����ī��
    UPROPERTY(Replicated)
    TArray<FPlayingCard> CommunityCards;

    // ���̺� �ڸ��� ���� �÷��̾� ����
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> PlayersForTable;

    // ���� �������� �÷��̾� ��ü
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> InGamePlayersAll;

    // ���� �� ��Ƴ��� �÷��̾�
    UPROPERTY(Replicated)
    TArray<ATHPlayerState*> InGameSurvivedPlayers;
};
