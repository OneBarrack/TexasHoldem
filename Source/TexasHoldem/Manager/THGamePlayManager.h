// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TexasHoldem.h"
#include "THGamePlayManager.generated.h"

/**
 * TexasHold`em's game play logic manager
 */
UCLASS()
class TEXASHOLDEM_API UTHGamePlayManager : public UObject
{
	GENERATED_BODY()

public:
	UTHGamePlayManager();

public:
	void Init();
	void SetNextBettingRound();

    // ī����̿��� ī�� �� ���� �޴´�
    const FPlayingCard GetCardFromCardDeck();

	// ���� ���ö��� ��ȯ
	const EBettingRound GetBettingRound() const;
	
    // ����ī�� ��ȯ
	TArray<FPlayingCard> GetCommunityCards() const;

	// ���� ���� ī�� �� ��ȯ
	const int GetCurrentCardDeckCount() const;

	// ����ī�� ���� ��ȯ
	const EHandRanking GetHandRanking(const TArray<FPlayingCard> HandCards);
	const EHandRanking DebugGetHandRanking(const TArray<FPlayingCard> HandCards, EHandRanking HandRanking = EHandRanking::None);

private:
	// ���ö��忡 ���� ����ī�� ����
	void AddCardToCommunityCards();

	// ����ī�� ����(��ũ) üũ
	bool IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards);
	bool IsStraightFlush(const TArray<FPlayingCard> FinalHandCards);
	bool IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards);
	bool IsFullHouse(const TArray<FPlayingCard> FinalHandCards);
	bool IsFlush(const TArray<FPlayingCard> FinalHandCards);
	bool IsStraight(const TArray<FPlayingCard> FinalHandCards);
	bool IsThreeOfAKind(const TArray<FPlayingCard> FinalHandCards);
	bool IsTwoPair(const TArray<FPlayingCard> FinalHandCards);
	bool IsOnePair(const TArray<FPlayingCard> FinalHandCards);

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
