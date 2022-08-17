// Fill out your copyright notice in the Description page of Project Settings.

#include "THGamePlayManager.h"
#include "Math/UnrealMathUtility.h"
#include "Common/THDefine.h"

UTHGamePlayManager::UTHGamePlayManager()
    : BettingRound(EBettingRound::PreFlop)
{
    CardDeck.Reserve(NumOfAllCards);
    CommunityCards.Reserve(MaxNumOfCommunityCards);
    
    InitGamePlay();
}

void UTHGamePlayManager::InitGamePlay()
{
    // 베팅라운드 초기화
    BettingRound = EBettingRound::PreFlop;

    // 카드 더미 초기화
    CardDeck.Empty(NumOfAllCards);
    for (int i = 0; i < NumOfAllCards; ++i)
    {
        CardDeck.Add(i);
    }

    // Init CommunityCards;
    CommunityCards.Empty(MaxNumOfCommunityCards);
}

void UTHGamePlayManager::SetBettingRound(EBettingRound InBettingRound)
{
    BettingRound = InBettingRound;
}

const FPlayingCard UTHGamePlayManager::GetCard()
{
    FPlayingCard Card;
    if (CardDeck.Num() == 0)
    {
        return Card;
    }

    // CardDeck의 Index 추출 후 해당 Index 데이터 삭제
    int CardDeckIndex = FMath::RandRange(0, CardDeck.Num());
    CardDeck.RemoveAt(CardDeckIndex);

    // Card shape
    switch (CardDeckIndex / NumOfCardsForShape)
    {
    case 0: Card.Shape = EPlayingCardShape::Spade;    break;
    case 1: Card.Shape = EPlayingCardShape::Diamond;  break;
    case 2: Card.Shape = EPlayingCardShape::Heart;    break;
    case 3: Card.Shape = EPlayingCardShape::Clover;   break;
    default:
        checkNoEntry();
        break;
    }

    // Card number
    Card.Number = (CardDeckIndex % NumOfCardsForShape) + 1;

    return Card;
}

void UTHGamePlayManager::AddCardToCommunityCards()
{    
    switch (BettingRound)
    {
    case EBettingRound::PreFlop:
        break;
    case EBettingRound::Flop: // Added 3 Card
        for (int i = 0; i < 3; ++i)
        {
            CommunityCards.Add(GetCard());
        }
        break;
    case EBettingRound::Turn: // Added 1 Card
        CommunityCards.Add(GetCard()); 
        break;
    case EBettingRound::River: // Added 1 Card
        CommunityCards.Add(GetCard()); 
        break;
    default:
        checkNoEntry();
        break;
    }
}
