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

    // 카드더미에서 카드 한 장을 받는다
    const FPlayingCard GetCardFromCardDeck();

	// 현재 베팅라운드 반환
	const EBettingRound GetBettingRound() const;
	
    // 공유카드 반환
	TArray<FPlayingCard> GetCommunityCards() const;

	// 덱의 남은 카드 수 반환
	const int GetCurrentCardDeckCount() const;

	// 최종카드 족보 반환
	const EHandRanking GetHandRanking(const TArray<FPlayingCard> HandCards);
	const EHandRanking DebugGetHandRanking(const TArray<FPlayingCard> HandCards, EHandRanking HandRanking = EHandRanking::None);

private:
	// 베팅라운드에 따른 공유카드 설정
	void AddCardToCommunityCards();

	// 최종카드 족보(랭크) 체크
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
	// 카드 더미
	UPROPERTY()
	TArray<int32> CardDeck;

	// 베팅 라운드
	UPROPERTY()
	EBettingRound BettingRound;

	// 테이블에 펼쳐질 공유카드
	UPROPERTY()
	TArray<FPlayingCard> CommunityCards;
};
