// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TexasHoldem.h"
#include "THPlayerState.generated.h"

class ATHGameState;
class ATHPlayerController;

UCLASS()
class TEXASHOLDEM_API ATHPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
    ATHPlayerState();

public:
    UFUNCTION()
    void Init();

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds);

public:
    UFUNCTION(BlueprintPure)
    ATHGameState* GetGameState() const;

    UFUNCTION(BlueprintPure)
    ATHPlayerController* GetPlayerController() const;

    UFUNCTION()
    void SetPlayerController(ATHPlayerController* InTHPlayerController);

public:
    UFUNCTION(BlueprintPure)
    const int32 GetPlayerImageIndex() const;

    UFUNCTION(BlueprintPure)
    const bool IsReservedToExit() const;

    UFUNCTION(BlueprintPure)
    const int32 GetTableSeattingPos() const;

    UFUNCTION(BlueprintPure)
    const EPlayerTurnState GetPlayerTurnState() const;

    UFUNCTION(BlueprintPure)
    const FString GetPlayerNickName() const;

    UFUNCTION(BlueprintPure)
    const EPlayerRole GetPlayerRole() const;

    UFUNCTION(BlueprintPure)
    const int32 GetMoney() const;

    UFUNCTION(BlueprintPure)
    const int32 GetRequiredMoneyForCall() const;
    
    UFUNCTION(BlueprintPure)
    const int32 GetBettingMoney() const;

    UFUNCTION(BlueprintPure)
    const int32 GetRoundBettingMoney() const;

    UFUNCTION(BlueprintPure)
    const int32 GetProfitMoney() const;

    UFUNCTION(BlueprintPure)
    const EPlayerAction GetPlayerAction() const;

    UFUNCTION(BlueprintPure)
    const bool IsWinner() const;

    UFUNCTION(BlueprintPure)
    const FPlayerHandRankInfo GetPlayerHandRankInfo() const;

    UFUNCTION(BlueprintPure)
    TArray<FPlayingCard> GetHandCards() const;

    UFUNCTION(BlueprintCallable)
    void SetPlayerImageIndex(const int32 InPlayerImageIndex);

    UFUNCTION(BlueprintCallable)
    void SetReservedToExitState(const bool bInReservedToExit);

    UFUNCTION(BlueprintCallable)
    void SetTableSeattingPos(const int32& InTableSeattingPos);

    UFUNCTION(BlueprintCallable)
    void SetPlayerTurnState(const EPlayerTurnState& InPlayerTurnState);

    UFUNCTION(BlueprintCallable)
    void SetPlayerNickName(const FString& InPlayerNickName);

    UFUNCTION(BlueprintCallable)
    void SetPlayerRole(const EPlayerRole& InPlayerRole);

    UFUNCTION(BlueprintCallable)
    void SetMoney(const int32& InMoney);

    UFUNCTION(BlueprintCallable)
    void AddMoney(const int32& InMoney);

    UFUNCTION(BlueprintCallable)
    void SetRequiredMoneyForCall(const int32& InRequiredMoneyForCall);

    UFUNCTION(BlueprintCallable)
    void SetBettingMoney(const int32& InBettingMoney);

    UFUNCTION(BlueprintCallable)
    void AddBettingMoney(const int32& InBettingMoney);

    UFUNCTION(BlueprintCallable)
    void SetRoundBettingMoney(const int32& InRoundBettingMoney);

    UFUNCTION(BlueprintCallable)
    void AddRoundBettingMoney(const int32& InRoundBettingMoney);

    UFUNCTION(BlueprintCallable)
    void SetProfitMoney(const int32& InProfitMoney);

    UFUNCTION(BlueprintCallable)
    void AddProfitMoney(const int32& InProfitMoney);

    UFUNCTION(BlueprintCallable)
    void SetPlayerAction(const EPlayerAction& InPlayerAction);

    UFUNCTION(BlueprintCallable)
    void SetIsWinner(const bool& bInIsWinner);

    UFUNCTION(BlueprintCallable)
    void SetPlayerHandRankInfo(const FPlayerHandRankInfo InHandRankInfo);

    UFUNCTION(BlueprintCallable)
    void SetHandCards(const TArray<FPlayingCard>& InHandCards);

private:
    // �÷��̾� �̹���
    UPROPERTY(Replicated)
    int32 PlayerImageIndex = -1;

    // �����⿹�� ����
    UPROPERTY(Replicated)
    bool bReservedToExit = false;

    // ���̺� �� ���� �ڸ�
    UPROPERTY(Replicated)
    int32 TableSeattingPos = 0;

    // �÷��̾� �� ����
    UPROPERTY(Replicated)
    EPlayerTurnState PlayerTurnState = EPlayerTurnState::None;

    // �̸�
    UPROPERTY(Replicated)
    FString PlayerNickName = FString(TEXT("Anonymous"));

    // ������
    UPROPERTY(Replicated)
    EPlayerRole PlayerRole = EPlayerRole::None;

    // ���� �ݾ�
    UPROPERTY(Replicated)
    int32 Money = StartPlayerMoney;

    // ���� �Ͽ��� �� �ϱ� ���� �ʿ��� �ݾ�
    UPROPERTY(Replicated)
    int32 RequiredMoneyForCall = 0;

    // �� ���� �ݾ�
    UPROPERTY(Replicated)
    int32 BettingMoney = 0;

    // ���� �� ���� �ݾ�
    UPROPERTY(Replicated)
    int32 RoundBettingMoney = 0;

    // ȹ�� �ݾ�
    UPROPERTY(Replicated)
    int32 ProfitMoney = 0;

    // �׼�
    UPROPERTY(Replicated)
    EPlayerAction PlayerAction = EPlayerAction::None;

    // ��������
    UPROPERTY(Replicated)
    bool bIsWinner = false;

    // �ڵ巩ũ ����
    UPROPERTY(Replicated)
    FPlayerHandRankInfo HandRankInfo;

    // �ڵ�ī��
    UPROPERTY(Replicated)
    TArray<FPlayingCard> HandCards;

private:
    UPROPERTY()
    ATHPlayerController* THPlayerController = nullptr;
};
