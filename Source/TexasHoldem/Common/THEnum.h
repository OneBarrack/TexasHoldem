// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "THEnum.generated.h"

UENUM(BlueprintType)
enum class EPlayingCardShape : uint8
{
    None,
    Spade,
    Diamond,
    Heart,
    Clover,
};

UENUM(BlueprintType)
enum class EBettingRound : uint8
{    
    PreFlop,
    Flop,
    Turn,
    River
};

UENUM(BlueprintType)
enum class EHandRanking : uint8
{
    RoyalFlush,
    StraightFlush,
    FourOfAKind,
    FullHouse,
    Flush,
    Straight,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard
};