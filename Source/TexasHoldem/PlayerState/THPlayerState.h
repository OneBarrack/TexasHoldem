// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TexasHoldem.h"
#include "THPlayerState.generated.h"

UCLASS()
class TEXASHOLDEM_API ATHPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
    ATHPlayerState();

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    UFUNCTION()
    void OnRep_Ready();

    UFUNCTION()
    bool GetReadyState(); 
    
    // Server
    UFUNCTION(Reliable, Server)
    void Server_ToggleReady(); 
    void Server_ToggleReady_Implementation();

private:
    // 레디 상태 변경
    void ToggleReady();

private:
    // 레디 상태
    UPROPERTY(ReplicatedUsing = OnRep_Ready)
    bool bReady = false;

    // 플레이어 이름
    UPROPERTY()
    FString PlayerName = FString(TEXT("Anonymous"));

    // 플레이어 포지션
    UPROPERTY()
    EPlayerPosition PlayerPosition = EPlayerPosition::None;

    // 플레이어 액션
    UPROPERTY()
    EPlayerAction PlayerAction = EPlayerAction::None;

    // 플레이어 핸드카드
    UPROPERTY()
    TArray<FPlayingCard> HandCards;
};
