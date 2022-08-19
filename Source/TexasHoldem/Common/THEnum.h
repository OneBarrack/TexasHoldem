// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "THEnum.generated.h"

UENUM(BlueprintType)
enum class EPlayingCardShape : uint8
{
    None = 0,
    Spade,
    Diamond,
    Heart,
    Clover,
    Max
};

UENUM(BlueprintType)
enum class EPlayingCardName : uint8
{
    None = 0,
    Ace,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    MaxAce
};

UENUM(BlueprintType)
enum class EBettingRound : uint8
{
    None = 0,
    PreFlop,
    Flop,
    Turn,
    River,
    Max
};

UENUM(BlueprintType)
enum class EHandRanking : uint8
{
    None = 0,
    RoyalFlush,
    StraightFlush,
    FourOfAKind,
    FullHouse,
    Flush,
    Straight,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard,
    Max
};
