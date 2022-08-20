// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "THEnum.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "THStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayingCard
{
    GENERATED_BODY()

public:
    UPROPERTY()
    EPlayingCardShape Shape = EPlayingCardShape::None;

    UPROPERTY()
    EPlayingCardValue Value = EPlayingCardValue::None;
};
