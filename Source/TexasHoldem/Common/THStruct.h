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

    UPROPERTY(BlueprintReadOnly)
    bool IsOneOfTheLastBest5Cards = false;

    bool operator==(const FPlayingCard& InPlayingCard) const
    {
        return (this->Suit == InPlayingCard.Suit   &&
                this->Value == InPlayingCard.Value &&
                this->IsOneOfTheLastBest5Cards == InPlayingCard.IsOneOfTheLastBest5Cards);
    }
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
    // ����(Hand Rank)
    UPROPERTY(BlueprintReadOnly)
    EHandRank HandRank = EHandRank::None;

    // ������ �ش��ϴ� ī�帮��Ʈ (����ī�� ����)
    UPROPERTY(BlueprintReadOnly)
    TArray<FPlayingCard> CardsForHandRank;

    // ���� �� HighValues(���� ���� �� ��ŭ ���� ������ ����)
    UPROPERTY(BlueprintReadOnly)
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // HighValues ŰĿ
    UPROPERTY(BlueprintReadOnly)
    TArray<FPlayingCard> Kickers;

public:
    bool operator>(const FPlayerHandRankInfo& InHandRankInfo) const
    {
        // Compare HandRank
        {
            EHandRank HandRankA = this->HandRank;
            EHandRank HandRankB = InHandRankInfo.HandRank;
            
            if (HandRankA > HandRankB)
            {
                return true;
            }
            if (HandRankA < HandRankB)
            {
                return false;
            }
        }

        // Compare High Values of HandRank
        int32 HighValuesCount = this->HighValuesOfHandRank.Num();
        for (int32 HighValueIndex = 0; HighValueIndex < HighValuesCount; ++HighValueIndex)
        {
            EPlayingCardValue HighValueA = this->HighValuesOfHandRank[HighValueIndex];
            EPlayingCardValue HighValueB = InHandRankInfo.HighValuesOfHandRank[HighValueIndex];

            if (HighValueA > HighValueB)
            {
                return true;
            }
            if (HighValueA < HighValueB)
            {
                return false;
            }
        }

        // Compare Kickers
        int32 KickersCount = this->Kickers.Num();
        for (int32 KickerIndex = 0; KickerIndex < KickersCount; ++KickerIndex)
        {
            EPlayingCardValue KickerValueA = this->Kickers[KickerIndex].Value;
            EPlayingCardValue KickerValueB = InHandRankInfo.Kickers[KickerIndex].Value;

            // Ace Kicker�� ���� ���� ���� �񱳵� �� �ְ� HighAce�� �����Ͽ� üũ
            if (KickerValueA == EPlayingCardValue::Ace)
            {
                KickerValueA = EPlayingCardValue::HighAce;
            }
            if (KickerValueB == EPlayingCardValue::Ace)
            {
                KickerValueB = EPlayingCardValue::HighAce;
            }

            // ��Һ�
            if (KickerValueA > KickerValueB)
            {
                return true;
            }
            if (KickerValueA < KickerValueB)
            {
                return false;
            }
        }

        return false;
    }

    bool operator<(const FPlayerHandRankInfo& InHandRankInfo) const
    {
        // Compare HandRank
        {
            EHandRank HandRankA = this->HandRank;
            EHandRank HandRankB = InHandRankInfo.HandRank;

            if (HandRankA < HandRankB)
            {
                return true;
            }
            if (HandRankA > HandRankB)
            {
                return false;
            }
        }

        // Compare High Values of HandRank
        int32 HighValuesCount = this->HighValuesOfHandRank.Num();
        for (int32 HighValueIndex = 0; HighValueIndex < HighValuesCount; ++HighValueIndex)
        {
            EPlayingCardValue HighValueA = this->HighValuesOfHandRank[HighValueIndex];
            EPlayingCardValue HighValueB = InHandRankInfo.HighValuesOfHandRank[HighValueIndex];

            if (HighValueA < HighValueB)
            {
                return true;
            }
            if (HighValueA > HighValueB)
            {
                return false;
            }
        }

        // Compare Kickers
        int32 KickersCount = this->Kickers.Num();
        for (int32 KickerIndex = 0; KickerIndex < KickersCount; ++KickerIndex)
        {
            EPlayingCardValue KickerValueA = this->Kickers[KickerIndex].Value;
            EPlayingCardValue KickerValueB = InHandRankInfo.Kickers[KickerIndex].Value;

            // Ace Kicker�� ���� ���� ���� �񱳵� �� �ְ� HighAce�� �����Ͽ� üũ
            if (KickerValueA == EPlayingCardValue::Ace)
            {
                KickerValueA = EPlayingCardValue::HighAce;
            }
            if (KickerValueB == EPlayingCardValue::Ace)
            {
                KickerValueB = EPlayingCardValue::HighAce;
            }

            // ��Һ�
            if (KickerValueA < KickerValueB)
            {
                return true;
            }
            if (KickerValueA > KickerValueB)
            {
                return false;
            }
        }

        return false;
    }

    bool operator==(const FPlayerHandRankInfo& InHandRankInfo) const
    {
        // Compare HandRank
        {
            EHandRank HandRankA = this->HandRank;
            EHandRank HandRankB = InHandRankInfo.HandRank;

            if (HandRankA != HandRankB)
            {
                return false;
            }
        }

        // Compare High Values of HandRank
        int32 HighValuesCount = this->HighValuesOfHandRank.Num();
        for (int32 HighValueIndex = 0; HighValueIndex < HighValuesCount; ++HighValueIndex)
        {
            EPlayingCardValue HighValueA = this->HighValuesOfHandRank[HighValueIndex];
            EPlayingCardValue HighValueB = InHandRankInfo.HighValuesOfHandRank[HighValueIndex];

            if (HighValueA != HighValueB)
            {
                return false;
            }
        }
        
        // Compare Kickers
        int32 KickersCount = this->Kickers.Num();
        for (int32 KickerIndex = 0; KickerIndex < KickersCount; ++KickerIndex)
        {
            EPlayingCardValue KickerValueA = this->Kickers[KickerIndex].Value;
            EPlayingCardValue KickerValueB = InHandRankInfo.Kickers[KickerIndex].Value;

            if (KickerValueA != KickerValueB)
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

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
        int32 PlayerImageIndex = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
        FString PlayerNickName = FString("Anonymous");
};
