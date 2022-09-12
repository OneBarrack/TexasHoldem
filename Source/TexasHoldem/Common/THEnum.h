// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "THEnum.generated.h"

UENUM(BlueprintType)
enum class EPlayingCardSuit : uint8
{
    None = 0,
    Spades,
    Diamonds,
    Hearts,
    Clubs,
    Max
};

UENUM(BlueprintType)
enum class EPlayingCardValue : uint8
{
    None = 0,
    Ace,
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
enum class EGamePlayState : uint8
{
    None = 0,
    Prepare,
    StartUp,
    PreFlop,
    Flop,
    Turn,
    River,
    Betting,
    Showdown,
    FinishUp,    
    Wait
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
enum class EHandRank : uint8
{
    None = 0,
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
    Max
};

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
    None = 0,
    Dealer,
    SmallBlind,
    BigBlind,
    Max
};

UENUM(BlueprintType)
enum class EPlayerAction : uint8
{
    None = 0,
    Quarter,
    Half,
    Full,
    Raise,
    Allin,
    Check,
    Call,
    Fold    
};

UENUM(BlueprintType)
enum class EPlayerTurnState : uint8
{
    None = 0,
    Wait,
    InProgress,
    Done,
};
