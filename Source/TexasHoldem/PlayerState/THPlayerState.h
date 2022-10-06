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
    // 플레이어 이미지
    UPROPERTY(Replicated)
    int32 PlayerImageIndex = -1;

    // 나가기예약 상태
    UPROPERTY(Replicated)
    bool bReservedToExit = false;

    // 테이블 내 앉은 자리
    UPROPERTY(Replicated)
    int32 TableSeattingPos = 0;

    // 플레이어 턴 상태
    UPROPERTY(Replicated)
    EPlayerTurnState PlayerTurnState = EPlayerTurnState::None;

    // 이름
    UPROPERTY(Replicated)
    FString PlayerNickName = FString(TEXT("Anonymous"));

    // 포지션
    UPROPERTY(Replicated)
    EPlayerRole PlayerRole = EPlayerRole::None;

    // 보유 금액
    UPROPERTY(Replicated)
    int32 Money = StartPlayerMoney;

    // 현재 턴에서 콜 하기 위해 필요한 금액
    UPROPERTY(Replicated)
    int32 RequiredMoneyForCall = 0;

    // 총 베팅 금액
    UPROPERTY(Replicated)
    int32 BettingMoney = 0;

    // 라운드 내 베팅 금액
    UPROPERTY(Replicated)
    int32 RoundBettingMoney = 0;

    // 획득 금액
    UPROPERTY(Replicated)
    int32 ProfitMoney = 0;

    // 액션
    UPROPERTY(Replicated)
    EPlayerAction PlayerAction = EPlayerAction::None;

    // 승자인지
    UPROPERTY(Replicated)
    bool bIsWinner = false;

    // 핸드랭크 정보
    UPROPERTY(Replicated)
    FPlayerHandRankInfo HandRankInfo;

    // 핸드카드
    UPROPERTY(Replicated)
    TArray<FPlayingCard> HandCards;

private:
    UPROPERTY()
    ATHPlayerController* THPlayerController = nullptr;
};
