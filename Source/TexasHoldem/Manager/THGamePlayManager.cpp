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
* RoyalFlush 
* : Straight Flush �� 10, J, Q, K, A�� ����
* 
* ī����� Shape ���� Array�� �з��� �� Array ���� 10, J, Q, K, A ī�尡 �����ϴ��� Ȯ��
*/
bool UTHGamePlayManager::IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
        
    // TMap ���� (Key : Card shape, Value : Card value)
    TMap<EPlayingCardShape, TArray<EPlayingCardValue>> CardsForShape;

    // ���ĵ� ���� ī�带 Shape �������� �з�
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

    // Shape�� ������ ī��鿡 ���� CardValue üũ
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardValue>& CardValuesForShape = CardForShape.Value;
        
        // ī�尡 5�� �̸��̶�� ��ŵ
        if (CardValuesForShape.Num() < 5)
        {
            continue;
        }
        
        // 10, 11(J), 12(Q), 13(K), 14(A)�� �����ϸ� True ��ȯ
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
* : ������ ������ ���ÿ� �����ϴ� 5���� ī��
* 
* ī����� Value �������� ������ �� Shape ���� Array�� �з��ϰ�, 
* �з��� Array ���� 5���� ���ӵ� Value�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsStraightFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // ī�� ����    
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return static_cast<int32>(FinalCardA.Value) < static_cast<int32>(FinalCardB.Value);
    });
    
    // ���ĵ� ���� ī�带 Shape ���� TMap���� �з� (Key : Card shape, Value : Card Value)
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

    // Shape�� ������ ī��鿡 ���� CardValue üũ
    for (auto& CardForShape : CardsForShape)
    {
        TArray<EPlayingCardValue>& CardValuesForShape = CardForShape.Value;

        // ī�尡 5�� �̸��̶�� ��ŵ
        if (CardValuesForShape.Num() < 5)
        {
            continue;
        }

        // Aceī�尡 �����ϸ� 1�� 14�� ������ ���� �� �ֵ��� MaxAceī��(14)�� Array �ڿ� �߰� ���ش�.
        if (CardValuesForShape.Contains(EPlayingCardValue::Ace))
        {
            CardValuesForShape.Add(EPlayingCardValue::HighAce);
        }

        int32 StraightNumCount = 0; // ���Ӽ� üũ ī��Ʈ
        int32 PrevCardNum = 0; // ���� ī���� ����
        for (auto& CardValue : CardValuesForShape)
        {
            // ���� ī�� ����
            int32 CardNum = static_cast<int32>(CardValue);

            // ī�尡 5�� �̸��̶�� ��ŵ
            if (CardValuesForShape.Num() < 5)
            {
                continue;
            }
                        
            // ù��° üũ�Ǵ� ����
            if (StraightNumCount == 0)
            {
                StraightNumCount = 1;
                PrevCardNum = CardNum;
            }
            // ���� ī���� ���ں��� 1�� ū ��
            else if (CardNum == PrevCardNum + 1)
            {
                ++StraightNumCount;
                PrevCardNum = CardNum;
            }
            // ���Ӽ��� �������Ƿ� �ʱ�ȭ
            else
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
* FourOfAKind
* : ���� ���� ī�� 4��
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 4�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }
    
    // �з��� Value 
    for (auto& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;        
        });

        // ī�� ���� 4���̶�� True ��ȯ
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
* : Three of a kind(Triple)�� One Pair�� ����
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� �� 
* �з��� Value�� �ش��ϴ� Triple�� One Pair�� �����ϴ� �� Ȯ�� (Triple�� One Pair�� ���� �ٸ� Value)
*/
bool UTHGamePlayManager::IsFullHouse(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    bool bFoundTriple = false; // Triple(���� ������ ī�� �� 3)
    bool bFoundPair = false; // Pair(���� ������ ī�� �� 2)
    for (auto& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ        
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });
                
        switch (CardsForCardValue.Num())
        {
        case 2:
            // Pair üũ
            if (CardsForCardValue.Num() == 2)
            {
                // �̹� Triple�� ã�� ���¶�� True ��ȯ
                if (bFoundTriple)
                {
                    bResult = true;
                }
                bFoundPair = true;
            }
            break;
        case 3: [[fallthrough]];
        case 4:
            // Triple üũ
            if (CardsForCardValue.Num() == 3)
            {
                // �̹� Pair �Ǵ� Triple�� ã�� ���¶�� True ��ȯ
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
* : ���� ������ ī�� 5��
* 
* ���� �ڵ�ī�忡 �����ϴ� Shape���� Set���� �з��ϰ�,
* �з��� Shape�� �ش��ϴ� ī�尡 5���̻� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsFlush(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // ī�忡 �����ϴ� Shape���� Set���� �з�
    TSet<EPlayingCardShape> CardShapes;
    for (auto& FinalCard : FinalCards)
    {
        CardShapes.Add(FinalCard.Shape);
    }

    // �з��� Shape
    for (auto& CardShape : CardShapes)
    {
        // Shape�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardShape;
        CardsForCardShape = FinalCards.FilterByPredicate([&CardShape](const FPlayingCard& FinalCard) {
            return FinalCard.Shape == CardShape;
        });

        // ī�� ���� 5���̶�� True ��ȯ
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
* : �����ϴ� 5���� ī��
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� ���ڸ� Set���� �з��Ͽ� ������ ��
* 5���� ���ӵ� Value�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsStraight(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    
    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // Value ����    
    CardValues.Sort([](const EPlayingCardValue& CardValueA, const EPlayingCardValue& CardValueB) {
        return static_cast<int32>(CardValueA) < static_cast<int32>(CardValueB);
    });

    // Aceī�尡 �����ϸ� 1�� 14�� ������ ���� �� �ֵ��� MaxAceī��(14)�� Array �ڿ� �߰� ���ش�.
    if (CardValues.Contains(EPlayingCardValue::Ace))
    {
        CardValues.Add(EPlayingCardValue::HighAce);
    }

    int32 StraightNumCount = 0; // ���Ӽ� üũ ī��Ʈ
    int32 PrevCardNum = 0; // ���� ī���� ����
    for (auto& CardValue : CardValues)
    {
        // ���� ī�� ����
        int32 CardNum = static_cast<int32>(CardValue);

        // ù��° üũ�Ǵ� ����
        if (StraightNumCount == 0) 
        {
            StraightNumCount = 1;
            PrevCardNum = CardNum;
        }
        // ���� ī���� ���ں��� 1�� ū ��
        else if (CardNum == PrevCardNum + 1) 
        {
            ++StraightNumCount;
            PrevCardNum = CardNum;
        }
        // ���Ӽ��� �������Ƿ� �ʱ�ȭ
        else 
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

    return bResult;
}

/**
* Three of a kind(Triple)
* : ���� ���� ī�� 3��
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 3�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsThreeOfAKind(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // �з��� Value 
    for (auto& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // ī�� ���� 3���̶�� True ��ȯ
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
* : ���� ���� ī�� 2�� 2��Ʈ
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 2�徿 2��Ʈ�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsTwoPair(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    
    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    bool bFoundPair = false; // Pair(���� ������ ī�� �� 2)
    for (auto& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // Pair üũ
        if (CardsForCardValue.Num() == 2)
        {
            // �̹� Pair�� ã�� ���¶�� True ��ȯ
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
* : ���� ���� ī�� 2�� 1��Ʈ
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 2�� �����ϴ� �� Ȯ��
*/
bool UTHGamePlayManager::IsOnePair(const TArray<FPlayingCard> FinalHandCards)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (auto& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    for (auto& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue;
        CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // Pair üũ
        if (CardsForCardValue.Num() == 2)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}