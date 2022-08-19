// Fill out your copyright notice in the Description page of Project Settings.

#include "THGamePlayManager.h"
#include "Math/UnrealMathUtility.h"
#include "Common/THDefine.h"

UTHGamePlayManager::UTHGamePlayManager()
    : BettingRound(EBettingRound::None)
{
    CardDeck.Reserve(NumOfAllCards);
    CommunityCards.Reserve(MaxNumOfCommunityCards);

    Init();
}

void UTHGamePlayManager::Init()
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

void UTHGamePlayManager::SetBettingRoundNext()
{
    BettingRound = static_cast<EBettingRound>(static_cast<int32>(BettingRound) + 1);
    AddCardToCommunityCards();
}

const FPlayingCard UTHGamePlayManager::GetCardFromCardDeck()
{
    FPlayingCard Card;
    if (CardDeck.Num() == 0)
    {
        return Card;
    }

    // CardDeck의 Index 추출 후 해당 Index 데이터 삭제
    int CardDeckArrayIndex = FMath::RandRange(0, CardDeck.Num() - 1);
    int CardDeckValue = CardDeck[CardDeckArrayIndex];
    CardDeck.RemoveAt(CardDeckArrayIndex);

    UE_LOG(LogTemp, Log, TEXT("CardDeckIndex:%d, CardDeckValue:%d"), CardDeckArrayIndex, CardDeckValue);

    // Card shape
    switch (CardDeckValue / NumOfCardsForShape)
    {
    case 0: Card.Shape = EPlayingCardShape::Spade;    break;
    case 1: Card.Shape = EPlayingCardShape::Diamond;  break;
    case 2: Card.Shape = EPlayingCardShape::Heart;    break;
    case 3: Card.Shape = EPlayingCardShape::Clover;   break;
    default:
        checkNoEntry();
        break;
    }

    // Card name
    int32 CardNumber = (CardDeckValue % NumOfCardsForShape) + 1;
    Card.Name = static_cast<EPlayingCardName>(CardNumber);

    return Card;
}

void UTHGamePlayManager::AddCardToCommunityCards()
{    
    switch (BettingRound)
    {
    case EBettingRound::PreFlop:
        break;
    case EBettingRound::Flop: // Added 3 card
        for (int i = 0; i < 3; ++i)
        {
            CommunityCards.Add(GetCardFromCardDeck());
        }
        break;
    case EBettingRound::Turn: // Added 1 card
        CommunityCards.Add(GetCardFromCardDeck()); 
        break;
    case EBettingRound::River: // Added 1 card
        CommunityCards.Add(GetCardFromCardDeck()); 
        break;
    default:
        checkNoEntry();
        break;
    }
}

const EHandRanking UTHGamePlayManager::GetHandRanking(const TArray<FPlayingCard> HandCards)
{
    // 공유카드 5장과 핸드 2장으로 총 7장이 되어 있어야 한다.
    if (CommunityCards.Num() != 5 || HandCards.Num() != 2)
        return EHandRanking::None;

    TArray<FPlayingCard> FinalHandCards = HandCards;
    FinalHandCards += CommunityCards;

    if (IsRoyalFlush(FinalHandCards))    return EHandRanking::RoyalFlush;
    if (IsStraightFlush(FinalHandCards)) return EHandRanking::StraightFlush;
    if (IsFourOfAKind(FinalHandCards))   return EHandRanking::FourOfAKind;
    if (IsFullHouse(FinalHandCards))     return EHandRanking::FullHouse;
    if (IsFlush(FinalHandCards))         return EHandRanking::Flush;
    if (IsStraight(FinalHandCards))      return EHandRanking::Straight;
    if (IsThreeOfAKind(FinalHandCards))  return EHandRanking::ThreeOfAKind;
    if (IsTwoPair(FinalHandCards))       return EHandRanking::TwoPair;
    if (IsOnePair(FinalHandCards))       return EHandRanking::OnePair;

    return EHandRanking::HighCard;
}

const EHandRanking UTHGamePlayManager::DebugGetHandRanking(const TArray<FPlayingCard> HandCards, EHandRanking HandRanking)
{
    TArray<FPlayingCard> FinalHandCards = HandCards;

    switch (HandRanking)
    {
    case EHandRanking::None:
        if (IsRoyalFlush(FinalHandCards))    return EHandRanking::RoyalFlush;
        if (IsStraightFlush(FinalHandCards)) return EHandRanking::StraightFlush;
        if (IsFourOfAKind(FinalHandCards))   return EHandRanking::FourOfAKind;
        if (IsFullHouse(FinalHandCards))     return EHandRanking::FullHouse;
        if (IsFlush(FinalHandCards))         return EHandRanking::Flush;
        if (IsStraight(FinalHandCards))      return EHandRanking::Straight;
        if (IsThreeOfAKind(FinalHandCards))  return EHandRanking::ThreeOfAKind;
        if (IsTwoPair(FinalHandCards))       return EHandRanking::TwoPair;
        if (IsOnePair(FinalHandCards))       return EHandRanking::OnePair;
        break;
    case EHandRanking::RoyalFlush: 
        if (IsRoyalFlush(FinalHandCards))    return EHandRanking::RoyalFlush;
        break;
    case EHandRanking::StraightFlush: 
        if (IsStraightFlush(FinalHandCards)) return EHandRanking::StraightFlush; 
        break;
    case EHandRanking::FourOfAKind:
        if (IsFourOfAKind(FinalHandCards))   return EHandRanking::FourOfAKind;
        break;
    case EHandRanking::FullHouse:
        if (IsFullHouse(FinalHandCards))     return EHandRanking::FullHouse; 
        break;
    case EHandRanking::Flush:
        if (IsFlush(FinalHandCards))         return EHandRanking::Flush; 
        break;
    case EHandRanking::Straight:
        if (IsStraight(FinalHandCards))      return EHandRanking::Straight; 
        break;
    case EHandRanking::ThreeOfAKind:
        if (IsThreeOfAKind(FinalHandCards))  return EHandRanking::ThreeOfAKind; 
        break;
    case EHandRanking::TwoPair:
        if (IsTwoPair(FinalHandCards))       return EHandRanking::TwoPair; 
        break;
    case EHandRanking::OnePair:
        if (IsOnePair(FinalHandCards))       return EHandRanking::OnePair; 
        break;
    }

    return EHandRanking::HighCard;
}

/*
* Check for RoyalFlush
* 카드들을 Shape 기준 Array로 분류한 후 Array 별로 10, J, Q, K, A 카드가 존재하는지 확인
*/
bool UTHGamePlayManager::IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
        
    // TMap 생성 (Key : Shape, Value : Card Name)
    TMap<EPlayingCardShape, TArray<EPlayingCardName>> CardsForShape;

    // 정렬된 최종 카드를 Shape 기준으로 분류
    for (auto& FinalCard : FinalCards)
    {
        if (!CardsForShape.Contains(FinalCard.Shape))
        {
            CardsForShape.Add(FinalCard.Shape, TArray<EPlayingCardName>{ FinalCard.Name });
        }
        else
        {
            CardsForShape[FinalCard.Shape].Add(FinalCard.Name);
        }
    }

    // Shape가 동일한 카드들에 대해 CardName 체크
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardName>& CardNamesForShape = CardForShape.Value;
        
        // 카드가 5장 미만이라면 스킵
        if (CardNamesForShape.Num() < 5)
        {
            continue;
        }
        
        // 10, 11(J), 12(Q), 13(K), 14(A)가 존재하면 True 반환
        if (CardNamesForShape.Contains(EPlayingCardName::Ten) &&
            CardNamesForShape.Contains(EPlayingCardName::Jack) &&
            CardNamesForShape.Contains(EPlayingCardName::Queen) &&
            CardNamesForShape.Contains(EPlayingCardName::King) &&
            CardNamesForShape.Contains(EPlayingCardName::Ace))
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

/**
* Check for StraightFlush
* 카드들을 정렬한 후 Shape 기준 Array로 분류하고, 
* 분류된 Array 별로 5장의 연속된 숫자가 존재하는 지 확인
*/
bool UTHGamePlayManager::IsStraightFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // 카드 정렬    
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Name < FinalCardB.Name;
    });
    
    // TMap 생성 (Key : Shape, Value : Card Name)
    TMap<EPlayingCardShape, TArray<EPlayingCardName>> CardsForShape;

    // 정렬된 최종 카드를 Shape 기준으로 분류
    for (auto& FinalCard : FinalCards)
    {
        if (!CardsForShape.Contains(FinalCard.Shape))
        {
            CardsForShape.Add(FinalCard.Shape, TArray<EPlayingCardName>{ FinalCard.Name });
        }
        else
        {
            CardsForShape[FinalCard.Shape].Add(FinalCard.Name);
        }
    }

    // Shape가 동일한 카드들에 대해 CardName 체크
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardName>& CardNamesForShape = CardForShape.Value;

        // 카드가 5장 미만이라면 스킵
        if (CardNamesForShape.Num() < 5)
        {
            continue;
        }

        // Ace카드가 존재하면 1과 14의 값으로 계산될 수 있도록 MaxAce카드(14)를 Array 뒤에 추가 해준다.
        if (CardNamesForShape.Contains(EPlayingCardName::Ace))
        {
            CardNamesForShape.Add(EPlayingCardName::MaxAce);
        }

        int32 StraightNumCount = 0; // 연속성 체크 카운트
        int32 PrevCardNum = 0; // 직전 카드의 숫자
        for (auto& CardName : CardNamesForShape)
        {
            int32 CardNum = static_cast<int32>(CardName);

            // 카드가 5장 미만이라면 스킵
            if (CardNamesForShape.Num() < 5)
            {
                continue;
            }
                        
            if (StraightNumCount == 0) // 첫번째 체크되는 숫자
            {
                StraightNumCount = 1;
                PrevCardNum = CardNum;
            }
            else if (CardNum == PrevCardNum + 1) // 직전 카드의 숫자보다 1이 큰 지
            {
                ++StraightNumCount;
                PrevCardNum = CardNum;
            }
            else // 연속성이 깨졌으므로 초기화
            {
                StraightNumCount = 0;
                PrevCardNum = 0;
            }

            // 연속된 카드가 5장이 되었다면 True 반환
            if (StraightNumCount == 5)
            {
                bResult = true;
                break;
            }
        }
    }

    return bResult;
}

/**
* Check for FourOfAKind
* 최종 핸드카드에 존재하는 Name들을 Set으로 분류한 후
* 분류된 Name에 해당하는 카드가 최종 핸드카드 내에 4장 존재하는 지 확인
*/
bool UTHGamePlayManager::IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TSet<EPlayingCardName> CardNames;

    // 카드에 존재하는 Name들을 Set으로 분류
    for (auto& FinalCard : FinalCards)
    {
        CardNames.Add(FinalCard.Name);
    }
    
    // 분류된 Name 
    for (auto& CardName : CardNames)
    {
        // Name에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardName;
        CardsForCardName = FinalCards.FilterByPredicate([&CardName](const FPlayingCard& FinalCard) {
            return FinalCard.Name == CardName;        
        });

        // 카드 수가 4장이라면 True 반환
        if (CardsForCardName.Num() == 4)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

/**
* Check for FourOfAKind
* 최종 핸드카드에 존재하는 Name들을 Set으로 분류한 후
* 분류된 Name에 해당하는 카드가 최종 핸드카드 내에 4장 존재하는 지 확인
*/
bool UTHGamePlayManager::IsFullHouse(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TSet<EPlayingCardName> CardNames;

    // 카드에 존재하는 Name들을 Set으로 분류
    for (auto& FinalCard : FinalCards)
    {
        CardNames.Add(FinalCard.Name);
    }

    bool bHasTriple = false;
    bool bHasPair = false;

    // 분류된 Name 
    for (auto& CardName : CardNames)
    {
        // Name에 해당하는 카드리스트        
        TArray<FPlayingCard> CardsForCardName;
        CardsForCardName = FinalCards.FilterByPredicate([&CardName](const FPlayingCard& FinalCard) {
            return FinalCard.Name == CardName;
            });
                
        switch (CardsForCardName.Num())
        {
        case 2:
            // Pair(같은 숫자의 카드 수 2) 체크
            if (CardsForCardName.Num() == 2)
            {
                // 이미 Triple이 존재하면 True 반환
                if (bHasTriple)
                {
                    bResult = true;
                    break;
                }
                bHasPair = true;
            }
            break;
        case 3: [[fallthrough]];
        case 4:
            // Triple(같은 숫자의 카드 수 3) 체크
            if (CardsForCardName.Num() == 3)
            {
                // 이미 Pair 또는 Triple이 존재하면 True 반환
                if (bHasTriple || bHasPair)
                {
                    bResult = true;
                    break;
                }
                bHasTriple = true;
            }
            break;
        default:
            break;
        }
    }

    return bResult;
}

bool UTHGamePlayManager::IsFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    return bResult;
}

bool UTHGamePlayManager::IsStraight(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    return bResult;
}

bool UTHGamePlayManager::IsThreeOfAKind(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    return bResult;
}

bool UTHGamePlayManager::IsTwoPair(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    return bResult;
}

bool UTHGamePlayManager::IsOnePair(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    return bResult;
}