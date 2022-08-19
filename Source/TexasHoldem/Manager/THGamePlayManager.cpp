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
    // ���ö��� �ʱ�ȭ
    BettingRound = EBettingRound::PreFlop;

    // ī�� ���� �ʱ�ȭ
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

    // CardDeck�� Index ���� �� �ش� Index ������ ����
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
    // ����ī�� 5��� �ڵ� 2������ �� 7���� �Ǿ� �־�� �Ѵ�.
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
* ī����� Shape ���� Array�� �з��� �� Array ���� 10, J, Q, K, A ī�尡 �����ϴ��� Ȯ��
*/
bool UTHGamePlayManager::IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
        
    // TMap ���� (Key : Shape, Value : Card Name)
    TMap<EPlayingCardShape, TArray<EPlayingCardName>> CardsForShape;

    // ���ĵ� ���� ī�带 Shape �������� �з�
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

    // Shape�� ������ ī��鿡 ���� CardName üũ
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardName>& CardNamesForShape = CardForShape.Value;
        
        // ī�尡 5�� �̸��̶�� ��ŵ
        if (CardNamesForShape.Num() < 5)
        {
            continue;
        }
        
        // 10, 11(J), 12(Q), 13(K), 14(A)�� �����ϸ� True ��ȯ
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
* ī����� ������ �� Shape ���� Array�� �з��ϰ�, 
* �з��� Array ���� 5���� ���ӵ� ���ڰ� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsStraightFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // ī�� ����    
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Name < FinalCardB.Name;
    });
    
    // TMap ���� (Key : Shape, Value : Card Name)
    TMap<EPlayingCardShape, TArray<EPlayingCardName>> CardsForShape;

    // ���ĵ� ���� ī�带 Shape �������� �з�
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

    // Shape�� ������ ī��鿡 ���� CardName üũ
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardName>& CardNamesForShape = CardForShape.Value;

        // ī�尡 5�� �̸��̶�� ��ŵ
        if (CardNamesForShape.Num() < 5)
        {
            continue;
        }

        // Aceī�尡 �����ϸ� 1�� 14�� ������ ���� �� �ֵ��� MaxAceī��(14)�� Array �ڿ� �߰� ���ش�.
        if (CardNamesForShape.Contains(EPlayingCardName::Ace))
        {
            CardNamesForShape.Add(EPlayingCardName::MaxAce);
        }

        int32 StraightNumCount = 0; // ���Ӽ� üũ ī��Ʈ
        int32 PrevCardNum = 0; // ���� ī���� ����
        for (auto& CardName : CardNamesForShape)
        {
            int32 CardNum = static_cast<int32>(CardName);

            // ī�尡 5�� �̸��̶�� ��ŵ
            if (CardNamesForShape.Num() < 5)
            {
                continue;
            }
                        
            if (StraightNumCount == 0) // ù��° üũ�Ǵ� ����
            {
                StraightNumCount = 1;
                PrevCardNum = CardNum;
            }
            else if (CardNum == PrevCardNum + 1) // ���� ī���� ���ں��� 1�� ū ��
            {
                ++StraightNumCount;
                PrevCardNum = CardNum;
            }
            else // ���Ӽ��� �������Ƿ� �ʱ�ȭ
            {
                StraightNumCount = 0;
                PrevCardNum = 0;
            }

            // ���ӵ� ī�尡 5���� �Ǿ��ٸ� True ��ȯ
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
* ���� �ڵ�ī�忡 �����ϴ� Name���� Set���� �з��� ��
* �з��� Name�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 4�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TSet<EPlayingCardName> CardNames;

    // ī�忡 �����ϴ� Name���� Set���� �з�
    for (auto& FinalCard : FinalCards)
    {
        CardNames.Add(FinalCard.Name);
    }
    
    // �з��� Name 
    for (auto& CardName : CardNames)
    {
        // Name�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardName;
        CardsForCardName = FinalCards.FilterByPredicate([&CardName](const FPlayingCard& FinalCard) {
            return FinalCard.Name == CardName;        
        });

        // ī�� ���� 4���̶�� True ��ȯ
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
* ���� �ڵ�ī�忡 �����ϴ� Name���� Set���� �з��� ��
* �з��� Name�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 4�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsFullHouse(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TSet<EPlayingCardName> CardNames;

    // ī�忡 �����ϴ� Name���� Set���� �з�
    for (auto& FinalCard : FinalCards)
    {
        CardNames.Add(FinalCard.Name);
    }

    bool bHasTriple = false;
    bool bHasPair = false;

    // �з��� Name 
    for (auto& CardName : CardNames)
    {
        // Name�� �ش��ϴ� ī�帮��Ʈ        
        TArray<FPlayingCard> CardsForCardName;
        CardsForCardName = FinalCards.FilterByPredicate([&CardName](const FPlayingCard& FinalCard) {
            return FinalCard.Name == CardName;
            });
                
        switch (CardsForCardName.Num())
        {
        case 2:
            // Pair(���� ������ ī�� �� 2) üũ
            if (CardsForCardName.Num() == 2)
            {
                // �̹� Triple�� �����ϸ� True ��ȯ
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
            // Triple(���� ������ ī�� �� 3) üũ
            if (CardsForCardName.Num() == 3)
            {
                // �̹� Pair �Ǵ� Triple�� �����ϸ� True ��ȯ
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