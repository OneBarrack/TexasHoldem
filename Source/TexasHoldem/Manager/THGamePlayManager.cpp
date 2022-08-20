// Fill out your copyright notice in the Description page of Project Settings.

#include "THGamePlayManager.h"

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

void UTHGamePlayManager::SetNextBettingRound()
{
    BettingRound = static_cast<EBettingRound>(static_cast<int32>(BettingRound) + 1);
    AddCardToCommunityCards();
}

const EBettingRound UTHGamePlayManager::GetBettingRound() const
{
    return BettingRound;
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

    // Card value
    int32 CardNumber = (CardDeckValue % NumOfCardsForShape) + 1;
    Card.Value = static_cast<EPlayingCardValue>(CardNumber);

    return Card;
}

TArray<FPlayingCard> UTHGamePlayManager::GetCommunityCards() const
{
    return CommunityCards;
}

const int UTHGamePlayManager::GetCurrentCardDeckCount() const
{
    return CardDeck.Num();
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
* RoyalFlush 
* : Straight Flush 중 10, J, Q, K, A인 조합
* 
* 카드들을 Shape 기준 Array로 분류한 후 Array 별로 10, J, Q, K, A 카드가 존재하는지 확인
*/
bool UTHGamePlayManager::IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
        
    // TMap 생성 (Key : Card shape, Value : Card value)
    TMap<EPlayingCardShape, TArray<EPlayingCardValue>> CardsForShape;

    // 정렬된 최종 카드를 Shape 기준으로 분류
    for (auto& FinalCard : FinalCards)
    {
        if (!CardsForShape.Contains(FinalCard.Shape))
        {
            CardsForShape.Add(FinalCard.Shape, TArray<EPlayingCardValue>{ FinalCard.Value });
        }
        else
        {
            CardsForShape[FinalCard.Shape].Add(FinalCard.Value);
        }
    }

    // Shape가 동일한 카드들에 대해 CardValue 체크
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardValue>& CardValuesForShape = CardForShape.Value;
        
        // 카드가 5장 미만이라면 스킵
        if (CardValuesForShape.Num() < 5)
        {
            continue;
        }
        
        // 10, 11(J), 12(Q), 13(K), 14(A)가 존재하면 True 반환
        if (CardValuesForShape.Contains(EPlayingCardValue::Ten) &&
            CardValuesForShape.Contains(EPlayingCardValue::Jack) &&
            CardValuesForShape.Contains(EPlayingCardValue::Queen) &&
            CardValuesForShape.Contains(EPlayingCardValue::King) &&
            CardValuesForShape.Contains(EPlayingCardValue::Ace))
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

/**
* StraightFlush 
* : 문양이 같으며 동시에 연속하는 5장의 카드
* 
* 카드들을 Value 기준으로 정렬한 후 Shape 기준 Array로 분류하고, 
* 분류된 Array 별로 5장의 연속된 Value가 존재하는 지 확인
*/
bool UTHGamePlayManager::IsStraightFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // 카드 정렬    
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return static_cast<int32>(FinalCardA.Value) < static_cast<int32>(FinalCardB.Value);
    });
    
    // 정렬된 최종 카드를 Shape 기준 TMap으로 분류 (Key : Card shape, Value : Card Value)
    TMap<EPlayingCardShape, TArray<EPlayingCardValue>> CardsForShape;
    for (auto& FinalCard : FinalCards)
    {
        if (!CardsForShape.Contains(FinalCard.Shape))
        {
            CardsForShape.Add(FinalCard.Shape, TArray<EPlayingCardValue>{ FinalCard.Value });
        }
        else
        {
            CardsForShape[FinalCard.Shape].Add(FinalCard.Value);
        }
    }

    // Shape가 동일한 카드들에 대해 CardValue 체크
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardValue>& CardValuesForShape = CardForShape.Value;

        // 카드가 5장 미만이라면 스킵
        if (CardValuesForShape.Num() < 5)
        {
            continue;
        }

        // Ace카드가 존재하면 1과 14의 값으로 계산될 수 있도록 MaxAce카드(14)를 Array 뒤에 추가 해준다.
        if (CardValuesForShape.Contains(EPlayingCardValue::Ace))
        {
            CardValuesForShape.Add(EPlayingCardValue::HighAce);
        }

        int32 StraightNumCount = 0; // 연속성 체크 카운트
        int32 PrevCardNum = 0; // 직전 카드의 숫자
        for (auto& CardValue : CardValuesForShape)
        {
            // 현재 카드 숫자
            int32 CardNum = static_cast<int32>(CardValue);

            // 카드가 5장 미만이라면 스킵
            if (CardValuesForShape.Num() < 5)
            {
                continue;
            }
                        
            // 첫번째 체크되는 숫자
            if (StraightNumCount == 0)
            {
                StraightNumCount = 1;
                PrevCardNum = CardNum;
            }
            // 직전 카드의 숫자보다 1이 큰 지
            else if (CardNum == PrevCardNum + 1)
            {
                ++StraightNumCount;
                PrevCardNum = CardNum;
            }
            // 연속성이 깨졌으므로 초기화
            else
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
* FourOfAKind
* : 같은 값의 카드 4장
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 4장 존재하는 지 확인
*/
bool UTHGamePlayManager::IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }
    
    // 분류된 Value 
    for (auto& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;        
        });

        // 카드 수가 4장이라면 True 반환
        if (CardsForCardValue.Num() == 4)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

/**
* FullHouse
* : Three of a kind(Triple)와 One Pair의 조합
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후 
* 분류된 Value에 해당하는 Triple과 One Pair가 존재하는 지 확인 (Triple과 One Pair는 서로 다른 Value)
*/
bool UTHGamePlayManager::IsFullHouse(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    bool bFoundTriple = false; // Triple(같은 숫자의 카드 수 3)
    bool bFoundPair = false; // Pair(같은 숫자의 카드 수 2)
    for (auto& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트        
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });
                
        switch (CardsForCardValue.Num())
        {
        case 2:
            // Pair 체크
            if (CardsForCardValue.Num() == 2)
            {
                // 이미 Triple을 찾은 상태라면 True 반환
                if (bFoundTriple)
                {
                    bResult = true;
                }
                bFoundPair = true;
            }
            break;
        case 3: [[fallthrough]];
        case 4:
            // Triple 체크
            if (CardsForCardValue.Num() == 3)
            {
                // 이미 Pair 또는 Triple을 찾은 상태라면 True 반환
                if (bFoundTriple || bFoundPair)
                {
                    bResult = true;
                }
                bFoundTriple = true;
            }
            break;
        default:
            break;
        }

        if (bResult)
            break;
    }

    return bResult;
}

/**
* Flush
* : 같은 문양의 카드 5장
* 
* 최종 핸드카드에 존재하는 Shape들을 Set으로 분류하고,
* 분류된 Shape에 해당하는 카드가 5장이상 존재하는 지 확인
*/
bool UTHGamePlayManager::IsFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // 카드에 존재하는 Shape들을 Set으로 분류
    TSet<EPlayingCardShape> CardShapes;
    for (auto& FinalCard : FinalCards)
    {
        CardShapes.Add(FinalCard.Shape);
    }

    // 분류된 Shape
    for (auto& CardShape : CardShapes)
    {
        // Shape에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardShape;
        CardsForCardShape = FinalCards.FilterByPredicate([&CardShape](const FPlayingCard& FinalCard) {
            return FinalCard.Shape == CardShape;
        });

        // 카드 수가 5장이라면 True 반환
        if (CardsForCardShape.Num() >= 5)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

/**
* Straight
* : 연속하는 5장의 카드
* 
* 최종 핸드카드에 존재하는 Value들의 숫자를 Set으로 분류하여 정렬한 후
* 5장의 연속된 Value가 존재하는 지 확인
*/
bool UTHGamePlayManager::IsStraight(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    
    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // Value 정렬    
    CardValues.Sort([](const EPlayingCardValue& CardValueA, const EPlayingCardValue& CardValueB) {
        return static_cast<int32>(CardValueA) < static_cast<int32>(CardValueB);
    });

    // Ace카드가 존재하면 1과 14의 값으로 계산될 수 있도록 MaxAce카드(14)를 Array 뒤에 추가 해준다.
    if (CardValues.Contains(EPlayingCardValue::Ace))
    {
        CardValues.Add(EPlayingCardValue::HighAce);
    }

    int32 StraightNumCount = 0; // 연속성 체크 카운트
    int32 PrevCardNum = 0; // 직전 카드의 숫자
    for (auto& CardValue : CardValues)
    {
        // 현재 카드 숫자
        int32 CardNum = static_cast<int32>(CardValue);

        // 첫번째 체크되는 숫자
        if (StraightNumCount == 0) 
        {
            StraightNumCount = 1;
            PrevCardNum = CardNum;
        }
        // 직전 카드의 숫자보다 1이 큰 지
        else if (CardNum == PrevCardNum + 1) 
        {
            ++StraightNumCount;
            PrevCardNum = CardNum;
        }
        // 연속성이 깨졌으므로 초기화
        else 
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

    return bResult;
}

/**
* Three of a kind(Triple)
* : 같은 값의 카드 3장
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 3장 존재하는 지 확인
*/
bool UTHGamePlayManager::IsThreeOfAKind(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // 분류된 Value 
    for (auto& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // 카드 수가 3장이라면 True 반환
        if (CardsForCardValue.Num() == 3)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

/**
* Two pair
* : 같은 값의 카드 2장 2세트
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 2장씩 2세트가 존재하는 지 확인
*/
bool UTHGamePlayManager::IsTwoPair(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    
    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    bool bFoundPair = false; // Pair(같은 숫자의 카드 수 2)
    for (auto& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // Pair 체크
        if (CardsForCardValue.Num() == 2)
        {
            // 이미 Pair를 찾은 상태라면 True 반환
            if (bFoundPair)
            {
                bResult = true;
                break;
            }
            bFoundPair = true;
        }
    }

    return bResult;
}

/**
* One pair
* : 같은 값의 카드 2장 1세트
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 2장 존재하는 지 확인
*/
bool UTHGamePlayManager::IsOnePair(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    for (auto& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // Pair 체크
        if (CardsForCardValue.Num() == 2)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}