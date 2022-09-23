// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/THGameDebugManager.h"

const FString UTHGameDebugManager::GetEnumAsString(const EPlayingCardSuit& PlayingCardSuit)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayingCardSuit"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EPlayingCardSuit Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)PlayingCardSuit);
}

const FString UTHGameDebugManager::GetEnumAsString(const EPlayingCardValue& PlayingCardValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayingCardValue"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EPlayingCardValue Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)PlayingCardValue);
}

const FString UTHGameDebugManager::GetEnumAsString(const EBettingRound& BettingRound)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EBettingRound"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EBettingRound Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)BettingRound);
}

const FString UTHGameDebugManager::GetEnumAsString(const EHandRank& HandRank)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EHandRank"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EHandRanking Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)HandRank);
}

const FString UTHGameDebugManager::GetEnumAsString(const EPlayerRole& PlayerRole)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerRole"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EPlayerRole Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)PlayerRole);
}

const FString UTHGameDebugManager::GetEnumAsString(const EPlayerAction& PlayerAction)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerAction"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EPlayerAction Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)PlayerAction);
}

const FString UTHGameDebugManager::GetEnumAsString(const EPlayerTurnState& PlayerTurnState)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerTurnState"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EPlayerTurnState Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)PlayerTurnState);
}

const FString UTHGameDebugManager::GetPlayerHandRankInfoAsString(const FPlayerHandRankInfo& PlayerHandRankInfo)
{
    UE_LOG(LogTemp, Log, TEXT("HandRank:%s"), *UTHGameDebugManager::GetEnumAsString(PlayerHandRankInfo.HandRank));
    if (PlayerHandRankInfo.HighValuesOfHandRank.Num() > 0)
    {
        FString CardsForHandRankString("");
        for (FPlayingCard PlayingCard : PlayerHandRankInfo.CardsForHandRank)
        {
            CardsForHandRankString += FString("[") +
                *UTHGameDebugManager::GetEnumAsString(PlayingCard.Suit) + FString("_") +
                *UTHGameDebugManager::GetEnumAsString(PlayingCard.Value) + FString("], ");
        }

        UE_LOG(LogTemp, Log, TEXT("CardsForHandRank:%s"), *CardsForHandRankString);
    }
    if (PlayerHandRankInfo.Kickers.Num() > 0)
    {
        FString TempStr("");
        for (FPlayingCard Kicker : PlayerHandRankInfo.Kickers)
        {
            TempStr += FString("[") +
                *UTHGameDebugManager::GetEnumAsString(Kicker.Suit) + FString("_") +
                *UTHGameDebugManager::GetEnumAsString(Kicker.Value) + FString("], ");
        }
        UE_LOG(LogTemp, Log, TEXT("KickerList:%s"), *TempStr);
    }
    return FString();
}
