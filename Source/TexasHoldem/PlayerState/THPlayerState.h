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
    // ���� ���� ����
    void ToggleReady();

private:
    // ���� ����
    UPROPERTY(ReplicatedUsing = OnRep_Ready)
    bool bReady = false;

    // �÷��̾� �̸�
    UPROPERTY()
    FString PlayerName = FString(TEXT("Anonymous"));

    // �÷��̾� ������
    UPROPERTY()
    EPlayerPosition PlayerPosition = EPlayerPosition::None;

    // �÷��̾� �׼�
    UPROPERTY()
    EPlayerAction PlayerAction = EPlayerAction::None;

    // �÷��̾� �ڵ�ī��
    UPROPERTY()
    TArray<FPlayingCard> HandCards;
};
