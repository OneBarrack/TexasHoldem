// Fill out your copyright notice in the Description page of Project Settings.

#include "THPlayerState.h"
#include "GameState/THGameState.h"

ATHPlayerState::ATHPlayerState()
{
    HandCards.Reserve(NumOfCardsForPlayer);    
}

void ATHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATHPlayerState, bReady);
}

void ATHPlayerState::OnRep_Ready()
{
    if (HasAuthority())
    {
        UE_LOG(LogTemp, Log, TEXT("Server - OnRep_Ready"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Client - OnRep_Ready"));
    }
}

bool ATHPlayerState::GetReadyState()
{
    return bReady;
}

void ATHPlayerState::Server_ToggleReady_Implementation()
{
    ToggleReady();
}

void ATHPlayerState::ToggleReady()
{
    bReady ^= true;
}
