// Fill out your copyright notice in the Description page of Project Settings.

#include "THGameState.h"
#include "GameMode/THGameMode.h"
#include "Manager/THGameDebugManager.h"

ATHGameState::ATHGameState()
{
}

void ATHGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATHGameState, BettingRound);
}

void ATHGameState::OnRep_BettingRound()
{
    UE_LOG(LogTemp, Log, TEXT("Start Next BettingRound! :: %s"), 
        *UTHGameDebugManager::GetEnumAsString(BettingRound));
}

const EBettingRound ATHGameState::GetBettingRound() const
{
    return BettingRound;
}

TArray<FPlayingCard> ATHGameState::GetCommunityCards() const
{
    return CommunityCards;
}

void ATHGameState::SetBettingRound(const EBettingRound InBettingRound)
{
    BettingRound = InBettingRound;
}

void ATHGameState::Multicast_SetBettingRound_Implementation(const EBettingRound InBettingRound)
{
    BettingRound = InBettingRound;
}
