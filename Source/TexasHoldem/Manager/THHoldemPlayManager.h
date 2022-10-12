// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TexasHoldem.h"
#include "THHoldemPlayManager.generated.h"

/**
 * TexasHold`em's game play logic manager (Server only)
 */
UCLASS()
class TEXASHOLDEM_API UTHHoldemPlayManager : public UObject
{
	GENERATED_BODY()

public:
	UTHHoldemPlayManager();

public:
	void Init();
	
    // ���� ���ö���� �̵�
    void SetBettingRound(const EBettingRound InBettingRound);

    // ���ö��忡 ���� ����ī�� ����
    void AddCardToCommunityCards();

    // ī����̿��� ī�� �� ���� �޴´�
    const FPlayingCard GetCardFromCardDeck();

	// ���� ���ö��� ��ȯ
	const EBettingRound GetBettingRound() const;
	
    // ����ī�� ��ȯ
	TArray<FPlayingCard> GetCommunityCards() const;

public:
	// ���� ���� ī�� �� ��ȯ
	const int32 GetCurrentCardDeckCount() const;

	// ����ī�� ���� ��ȯ
	FPlayerHandRankInfo GetHandRankInfo(const TArray<FPlayingCard> InHandCards);
	
	// Debug
	TArray<FPlayingCard>& DebugGetCommunityCards() { return CommunityCards; }

private:
	// ����ī�� ����(��ũ) üũ
	bool IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsStraightFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsFullHouse(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsStraight(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsThreeOfAKind(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsTwoPair(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsOnePair(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);
	bool IsHighCard(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo);

private:
	// ī�� ����
	UPROPERTY()
	TArray<int32> CardDeck;

	// ���� ����
	UPROPERTY()
	EBettingRound BettingRound;

	// ���̺� ������ ����ī��
	UPROPERTY()
	TArray<FPlayingCard> CommunityCards;
};
