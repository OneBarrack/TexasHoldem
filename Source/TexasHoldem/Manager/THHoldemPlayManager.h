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
	
    // 다음 베팅라운드로 이동
    void SetBettingRound(const EBettingRound InBettingRound);

    // 베팅라운드에 따른 공유카드 설정
    void AddCardToCommunityCards();

    // 카드더미에서 카드 한 장을 받는다
    const FPlayingCard GetCardFromCardDeck();

	// 현재 베팅라운드 반환
	const EBettingRound GetBettingRound() const;
	
    // 공유카드 반환
	TArray<FPlayingCard> GetCommunityCards() const;

public:
	// 덱의 남은 카드 수 반환
	const int32 GetCurrentCardDeckCount() const;

	// 최종카드 족보 반환
	FPlayerHandRankInfo GetHandRankInfo(const TArray<FPlayingCard> InHandCards);
	
	// Debug
	TArray<FPlayingCard>& DebugGetCommunityCards() { return CommunityCards; }

private:
	// 최종카드 족보(랭크) 체크
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
