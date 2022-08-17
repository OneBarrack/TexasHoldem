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

	// ī�� �� ���� �޾ƿ´�.
	const FPlayingCard GetCard();

private:
	// ���ö��忡 ���� CommunityCard ����
	void AddCardToCommunityCards();

private:
	// ī�� ����
	TArray<int32> CardDeck;

	// ���� ����
	EBettingRound BettingRound;

	// ���̺� ������ ����ī��
	TArray<FPlayingCard> CommunityCards;
};
