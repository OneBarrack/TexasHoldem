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
enum class EPlayingCardValue : uint8
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
    HighAce
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

UENUM(BlueprintType)
enum class EPlayerPosition : uint8
{
    None = 0,
    Button,
    SmallBlind,
    BigBlind
};

UENUM(BlueprintType)
enum class EPlayerAction : uint8
{
    None = 0,
    Check,
    Bet,
    Call,
    Raise,
    Fold
};