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
    UPROPERTY(BlueprintReadOnly)
    EPlayingCardSuit Suit = EPlayingCardSuit::None;

    UPROPERTY(BlueprintReadOnly)
    EPlayingCardValue Value = EPlayingCardValue::None;
};

USTRUCT(BlueprintType)
struct FPlayerActionActivateInfo
{
    GENERATED_BODY()

public:
    // Enabled Action Button
    UPROPERTY(BlueprintReadOnly)
    bool bEnabledQuarter = true;

    UPROPERTY(BlueprintReadOnly)
    bool bEnabledHalf = true;

    UPROPERTY(BlueprintReadOnly)
    bool bEnabledFull = true;

    UPROPERTY(BlueprintReadOnly)
    bool bEnabledRaise = true;

    UPROPERTY(BlueprintReadOnly)
    bool bEnabledAllin = true;

    UPROPERTY(BlueprintReadOnly)
    bool bEnabledCheck = true;

    UPROPERTY(BlueprintReadOnly)
    bool bEnabledCall = true;

    UPROPERTY(BlueprintReadOnly)
    bool bEnabledFold = true;

    // Required Money For ...
    UPROPERTY(BlueprintReadOnly)
    int32 RequiredMoneyForQuarter = 0;

    UPROPERTY(BlueprintReadOnly)
    int32 RequiredMoneyForHalf = 0;

    UPROPERTY(BlueprintReadOnly)
    int32 RequiredMoneyForFull = 0;

    UPROPERTY(BlueprintReadOnly)
    int32 RequiredMoneyForCall = 0;
};

USTRUCT(BlueprintType)
struct FPlayerHandRankInfo
{
    GENERATED_BODY()

public:
    // 족보(Hand Rank)
    UPROPERTY(BlueprintReadOnly)
    EHandRank HandRank = EHandRank::None;

    // 족보 내 HighValues(세부 족보 수 만큼 높은 순으로 적재)
    UPROPERTY(BlueprintReadOnly)
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // HighValues 키커
    UPROPERTY(BlueprintReadOnly)
    TArray<FPlayingCard> Kickers;

public:
    bool operator>(const FPlayerHandRankInfo& InHandRankInfo) const
    {
        // Compare HandRank
        if (this->HandRank > InHandRankInfo.HandRank)
        {
            return true;
        }
        if (this->HandRank < InHandRankInfo.HandRank)
        {
            return false;
        }

        // Compare High Values of HandRank
        int32 HighValuesCount = this->HighValuesOfHandRank.Num();
        for (int32 HighValueIndex = 0; HighValueIndex < HighValuesCount; ++HighValueIndex)
        {
            if (this->HighValuesOfHandRank[HighValueIndex] > InHandRankInfo.HighValuesOfHandRank[HighValueIndex])
            {
                return true;
            }
            if (this->HighValuesOfHandRank[HighValueIndex] < InHandRankInfo.HighValuesOfHandRank[HighValueIndex])
            {
                return false;
            }
        }

        // Compare Kickers
        int32 KickersCount = this->Kickers.Num();
        for (int32 KickerIndex = 0; KickerIndex < KickersCount; ++KickerIndex)
        {
            if (this->Kickers[KickerIndex].Value > InHandRankInfo.Kickers[KickerIndex].Value)
            {
                return true;
            }
            if (this->Kickers[KickerIndex].Value < InHandRankInfo.Kickers[KickerIndex].Value)
            {
                return false;
            }
        }

        return false;
    }

    bool operator<(const FPlayerHandRankInfo& InHandRankInfo) const
    {
        // Compare HandRank
        if (this->HandRank < InHandRankInfo.HandRank)
        {
            return true;
        }
        if (this->HandRank > InHandRankInfo.HandRank)
        {
            return false;
        }

        // Compare High Values of HandRank
        int32 HighValuesCount = this->HighValuesOfHandRank.Num();
        for (int32 HighValueIndex = 0; HighValueIndex < HighValuesCount; ++HighValueIndex)
        {
            if (this->HighValuesOfHandRank[HighValueIndex] < InHandRankInfo.HighValuesOfHandRank[HighValueIndex])
            {
                return true;
            }
            if (this->HighValuesOfHandRank[HighValueIndex] > InHandRankInfo.HighValuesOfHandRank[HighValueIndex])
            {
                return false;
            }
        }

        // Compare Kickers
        int32 KickersCount = this->Kickers.Num();
        for (int32 KickerIndex = 0; KickerIndex < KickersCount; ++KickerIndex)
        {
            if (this->Kickers[KickerIndex].Value < InHandRankInfo.Kickers[KickerIndex].Value)
            {
                return true;
            }
            if (this->Kickers[KickerIndex].Value > InHandRankInfo.Kickers[KickerIndex].Value)
            {
                return false;
            }
        }

        return false;
    }

    bool operator==(const FPlayerHandRankInfo& InHandRankInfo) const
    {
        // Compare HandRank
        if (this->HandRank != InHandRankInfo.HandRank)
        {
            return false;
        }

        // Compare High Values of HandRank
        int32 HighValuesCount = this->HighValuesOfHandRank.Num();
        for (int32 HighValueIndex = 0; HighValueIndex < HighValuesCount; ++HighValueIndex)
        {
            if (this->HighValuesOfHandRank[HighValueIndex] != InHandRankInfo.HighValuesOfHandRank[HighValueIndex])
            {
                return false;
            }
        }
        
        // Compare Kickers
        int32 KickersCount = this->Kickers.Num();
        for (int32 KickerIndex = 0; KickerIndex < KickersCount; ++KickerIndex)
        {
            if (this->Kickers[KickerIndex].Value != InHandRankInfo.Kickers[KickerIndex].Value)
            {
                return false;
            }
        }

        return true;
    }
};

FORCEINLINE uint32 GetTypeHash(const FPlayerHandRankInfo& PlayerHandRankInfo)
{
    return FCrc::MemCrc32(&PlayerHandRankInfo, sizeof(FPlayerHandRankInfo));
}
