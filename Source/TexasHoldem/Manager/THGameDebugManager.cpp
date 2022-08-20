// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/THGameDebugManager.h"

const FString UTHGameDebugManager::GetEnumAsString(EPlayingCardShape PlayingCardShape)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayingCardShape"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EPlayingCardShape Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)PlayingCardShape);
}

const FString UTHGameDebugManager::GetEnumAsString(EPlayingCardValue PlayingCardValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayingCardValue"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EPlayingCardValue Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)PlayingCardValue);
}

const FString UTHGameDebugManager::GetEnumAsString(EBettingRound BettingRound)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EBettingRound"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EBettingRound Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)BettingRound);
}

const FString UTHGameDebugManager::GetEnumAsString(EHandRanking HandRanking)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EHandRanking"), true);
    if (!EnumPtr)
    {
        return FString("GetEnumAsString()::EHandRanking Invalid");
    }
    return EnumPtr->GetNameStringByIndex((int32)HandRanking);
}
