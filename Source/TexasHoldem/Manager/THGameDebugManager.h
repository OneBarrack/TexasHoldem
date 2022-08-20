// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TexasHoldem.h"
#include "THGameDebugManager.generated.h"

/**
 * 
 */
UCLASS()
class TEXASHOLDEM_API UTHGameDebugManager : public UObject
{
	GENERATED_BODY()
	
public:
	static const FString GetEnumAsString(const EPlayingCardShape PlayingCardValue);
	static const FString GetEnumAsString(const EPlayingCardValue PlayingCardValue);
	static const FString GetEnumAsString(const EBettingRound BettingRound);
	static const FString GetEnumAsString(const EHandRanking HandRanking);
};
