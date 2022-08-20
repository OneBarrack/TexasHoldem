// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TexasHoldem.h"
#include "THGameState.generated.h"

UCLASS()
class TEXASHOLDEM_API ATHGameState : public AGameState
{
	GENERATED_BODY()

public:
	ATHGameState();

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    UFUNCTION()
    void OnRep_BettingRound();

    UFUNCTION(BlueprintPure)
    const EBettingRound GetBettingRound() const;

    UFUNCTION(BlueprintPure)
    TArray<FPlayingCard> GetCommunityCards() const;

    void SetBettingRound(const EBettingRound InBettingRound);

    // Multicast
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SetBettingRound(const EBettingRound InBettingRound);
    void Multicast_SetBettingRound_Implementation(const EBettingRound InBettingRound);

private:
    // 베팅라운드
    UPROPERTY(ReplicatedUsing = OnRep_BettingRound)
    EBettingRound BettingRound = EBettingRound::None;

    // 테이블에 펼쳐질 공유카드
    UPROPERTY()
    TArray<FPlayingCard> CommunityCards;
};
