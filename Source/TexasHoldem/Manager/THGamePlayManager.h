// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/THEnum.h"
#include "Common/THStruct.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
	void InitGamePlay();
	//void StartRound();

	const EBettingRound GetBettingRound() const { return BettingRound; }
	void SetBettingRound(const EBettingRound InBettingRound);
	
	const TArray<FPlayingCard> GetCommunityCards() const { return CommunityCards; }

	// 카드 한 장을 받아온다.
	const FPlayingCard GetCard();

private:
	// 베팅라운드에 따른 CommunityCard 설정
	void AddCardToCommunityCards();

private:
	// 카드 더미
	TArray<int32> CardDeck;

	// 베팅 라운드
	EBettingRound BettingRound;

	// 테이블에 펼쳐질 공유카드
	TArray<FPlayingCard> CommunityCards;
};
