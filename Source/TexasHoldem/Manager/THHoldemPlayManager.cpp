// Fill out your copyright notice in the Description page of Project Settings.

#include "THHoldemPlayManager.h"
#include "Manager/THGameDebugManager.h"
#include "Algo/MaxElement.h"

UTHHoldemPlayManager::UTHHoldemPlayManager()
    : BettingRound(EBettingRound::None)
{
    CardDeck.Reserve(NumOfAllCards);
    CommunityCards.Reserve(MaxNumOfCommunityCards);
}

void UTHHoldemPlayManager::Init()
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

    UE_LOG(LogTemp, Log, TEXT("UTHHoldemPlayManager::Init"));
}

void UTHHoldemPlayManager::SetBettingRound(const EBettingRound InBettingRound)
{
    BettingRound = InBettingRound;
}

const EBettingRound UTHHoldemPlayManager::GetBettingRound() const
{
    return BettingRound;
}

const FPlayingCard UTHHoldemPlayManager::GetCardFromCardDeck()
{
    FPlayingCard PlayingCard;
    if (CardDeck.Num() == 0)
    {
        return PlayingCard;
    }

    // CardDeck�� Index ���� �� �ش� Index ������ ����
    int CardDeckArrayIndex = FMath::RandRange(0, CardDeck.Num() - 1);
    int CardDeckValue = CardDeck[CardDeckArrayIndex];
    CardDeck.RemoveAt(CardDeckArrayIndex);

    UE_LOG(LogTemp, Log, TEXT("CardDeckIndex:%d, CardDeckValue:%d"), CardDeckArrayIndex, CardDeckValue);

    // Card suit
    switch (CardDeckValue / NumOfCardsForSuit)
    {
    case 0: PlayingCard.Suit = EPlayingCardSuit::Spades;   break;
    case 1: PlayingCard.Suit = EPlayingCardSuit::Diamonds; break;
    case 2: PlayingCard.Suit = EPlayingCardSuit::Hearts;   break;
    case 3: PlayingCard.Suit = EPlayingCardSuit::Clubs;    break;
    default:
        checkNoEntry();
        break;
    }

    // Card value
    int32 CardNumber = (CardDeckValue % NumOfCardsForSuit) + 1;
    PlayingCard.Value = static_cast<EPlayingCardValue>(CardNumber);

    return PlayingCard;
}

TArray<FPlayingCard> UTHHoldemPlayManager::GetCommunityCards() const
{
    return CommunityCards;
}

const int UTHHoldemPlayManager::GetCurrentCardDeckCount() const
{
    return CardDeck.Num();
}

void UTHHoldemPlayManager::AddCardToCommunityCards()
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
    
    for (FPlayingCard& CommunityCard : CommunityCards)
    {
        UE_LOG(LogTemp, Log, TEXT("UTHHoldemPlayManager::AddCardToCommunityCards BettingRound(%s) Suit(%s) Value(%s)"),
            *UTHGameDebugManager::GetEnumAsString(BettingRound),
            *UTHGameDebugManager::GetEnumAsString(CommunityCard.Suit),
            *UTHGameDebugManager::GetEnumAsString(CommunityCard.Value));
    }
}

FPlayerHandRankInfo UTHHoldemPlayManager::GetHandRankInfo(const TArray<FPlayingCard> InHandCards)
{
    FPlayerHandRankInfo PlayerHandRankInfo;

    // ����ī�� 5��� �ڵ� 2������ �� 7���� �Ǿ� �־�� �Ѵ�.
    if (CommunityCards.Num() != 5 || InHandCards.Num() != 2)
    {
        return PlayerHandRankInfo;
    }

    // ����ī�� 5��� �ڵ� 2���� ��ģ 7���� ����ī�� ����
    TArray<FPlayingCard> FinalHandCards;
    FinalHandCards.Append(CommunityCards);
    FinalHandCards.Append(InHandCards);

    if (IsRoyalFlush(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::RoyalFlush;
    }
    else if (IsStraightFlush(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::StraightFlush;
    }
    else if (IsFourOfAKind(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::FourOfAKind;
    }
    else if (IsFullHouse(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::FullHouse;
    }
    else if (IsFlush(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::Flush;
    }
    else if (IsStraight(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::Straight;
    }
    else if (IsThreeOfAKind(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::ThreeOfAKind;
    }
    else if (IsTwoPair(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::TwoPair;
    }
    else if (IsOnePair(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::OnePair;
    }
    else if (IsHighCard(FinalHandCards, PlayerHandRankInfo))
    {
        PlayerHandRankInfo.HandRank = EHandRank::HighCard;
    }
    else
    {
        // Error. �� ������ ������ ���� ����� �Ѵ�.
        checkNoEntry();
    }

    UE_LOG(LogTemp, Log, TEXT("UTHHoldemPlayManager::GetHandRank HandRank:%s"), *UTHGameDebugManager::GetEnumAsString(PlayerHandRankInfo.HandRank));
    return PlayerHandRankInfo;
}

/*
* RoyalFlush 
* : Straight Flush �� 10, J, Q, K, A�� ����
* 
* ī����� Suit ���� Array�� �з��� �� Array ���� 10, J, Q, K, A ī�尡 �����ϴ��� Ȯ��
*/
bool UTHHoldemPlayManager::IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    
    // ���� ī�带 Suit ���� TMap���� �з� (Key : Card suit, Value : Card Value)
    TMap<EPlayingCardSuit, TArray<EPlayingCardValue>> CardsForSuit;
    CardsForSuit.Add(EPlayingCardSuit::Spades);
    CardsForSuit.Add(EPlayingCardSuit::Diamonds);
    CardsForSuit.Add(EPlayingCardSuit::Hearts);
    CardsForSuit.Add(EPlayingCardSuit::Clubs);

    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardsForSuit[FinalCard.Suit].Add(FinalCard.Value);
    }

    // Suit�� ������ ī��鿡 ���� CardValue üũ
    for (auto& CardForSuit : CardsForSuit)
    {
        TArray<EPlayingCardValue>& CardValuesForSuit = CardForSuit.Value;
        
        // ī�尡 5�� �̸��̶�� ��ŵ
        if (CardValuesForSuit.Num() < 5)
        {
            continue;
        }
        
        // 10, 11(J), 12(Q), 13(K), 14(A)�� �����ϸ� True ��ȯ
        if (CardValuesForSuit.Contains(EPlayingCardValue::Ten) &&
            CardValuesForSuit.Contains(EPlayingCardValue::Jack) &&
            CardValuesForSuit.Contains(EPlayingCardValue::Queen) &&
            CardValuesForSuit.Contains(EPlayingCardValue::King) &&
            CardValuesForSuit.Contains(EPlayingCardValue::Ace))
        {
            PlayerHandRankInfo.HighValuesOfHandRank.Add(EPlayingCardValue::Ace);
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
* ī����� Value �������� ������ �� Suit ���� Array�� �з��ϰ�, 
* �з��� Array ���� 5���� ���ӵ� Value�� �����ϴ� �� Ȯ��
*/
bool UTHHoldemPlayManager::IsStraightFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // ������������ ī�� ����
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });
    
    // ���ĵ� ���� ī�带 Suit ���� TMap���� �з� (Key : Card suit, Value : Card Value)
    TMap<EPlayingCardSuit, TArray<EPlayingCardValue>> CardsForSuit;
    CardsForSuit.Add(EPlayingCardSuit::Spades);
    CardsForSuit.Add(EPlayingCardSuit::Diamonds);
    CardsForSuit.Add(EPlayingCardSuit::Hearts);
    CardsForSuit.Add(EPlayingCardSuit::Clubs);

    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardsForSuit[FinalCard.Suit].Add(FinalCard.Value);
    }

    // Suit�� ������ ī��鿡 ���� CardValue üũ
    for (auto& CardForSuit : CardsForSuit)
    {
        TArray<EPlayingCardValue>& CardValuesForSuit = CardForSuit.Value;

        // Suit�� ������ ī�尡 5�� �̸��̶�� ��ŵ
        if (CardValuesForSuit.Num() < 5)
        {
            continue;
        }

        // Aceī�尡 �����ϸ� 1�� 14�� ������ ���� �� �ֵ��� MaxAceī��(14)�� Array �ڿ� �߰� ���ش�.
        if (CardValuesForSuit.Contains(EPlayingCardValue::Ace))
        {
            CardValuesForSuit.Add(EPlayingCardValue::HighAce);
        }

        int32 StraightNumCount = 0; // ���Ӽ� üũ ī��Ʈ
        int32 PrevCardNum = 0; // ���� ī���� ����
        for (EPlayingCardValue& CardValue : CardValuesForSuit)
        {
            // ���� ī�� ����
            int32 CardNum = static_cast<int32>(CardValue);

            // ī�尡 5�� �̸��̶�� ��ŵ
            if (CardValuesForSuit.Num() < 5)
            {
                continue;
            }
                        
            // ù��° üũ�Ǵ� ����
            if (StraightNumCount == 0)
            {
                // ���� ���� �����̹Ƿ� �ڵ巩ũ�� ���̹�� ����
                HighValuesOfHandRank.Add(CardValue);

                StraightNumCount = 1;
                PrevCardNum = CardNum;
            }
            // ���� ī���� ���ں��� 1�� ������
            else if (CardNum == PrevCardNum - 1)
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

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* FourOfAKind
* : ���� ���� ī�� 4��
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 4�� �����ϴ� �� Ȯ��
*/
bool UTHHoldemPlayManager::IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)ī�尡 �ִٸ� ��� HighAce(14)�� �ٲپ��ش�.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // ������������ ī�� ����
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }
    
    // �з��� Value 
    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;        
        });

        // ī�� ���� 4���̶��
        if (CardsForCardValue.Num() == 4)
        {
            // �ڵ巩ũ�� ���̹�� ����
            HighValuesOfHandRank.Add(CardValue);

            // ����ī�忡�� ��ī�忡 �ش��ϴ� ī�� ����
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });
            
            // ��ī�带 ������ ī�� �� ���� ���� Value�� ŰĿ�� ����
            Kickers.Add(FinalCards[0]);

            // True ��ȯ
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

/**
* FullHouse
* : Three of a kind(Triple)�� One Pair�� ����
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� �� 
* �з��� Value�� �ش��ϴ� Triple�� One Pair�� �����ϴ� �� Ȯ�� (Triple�� One Pair�� ���� �ٸ� Value)
*/
bool UTHHoldemPlayManager::IsFullHouse(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // Ace(1)ī�尡 �ִٸ� ��� HighAce(14)�� �ٲپ��ش�.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // ������������ ī�� ����
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // Value�� �ٷ�Ȯ��
    EPlayingCardValue TripleValue = EPlayingCardValue::None; // Triple(���� ������ ī�� �� 3��) Value
    EPlayingCardValue PairValue = EPlayingCardValue::None;   // Pair(���� ������ ī�� �� 2) Value
    for (EPlayingCardValue& CardValue : CardValues)
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
                // �̹� ã�� Pair�� ���� ��� Value ����
                if (PairValue == EPlayingCardValue::None)
                {
                    PairValue = CardValue;
                }
            }
            break;
        case 3: [[fallthrough]];
        case 4:
            // Triple üũ
            if (CardsForCardValue.Num() == 3)
            {
                // �̹� Triple�� ã�� ��������
                if (TripleValue == EPlayingCardValue::None)
                {                    
                    TripleValue = CardValue;
                }
                else
                {
                    PairValue = CardValue;
                }
            }
            break;
        default:
            break;
        }

        // TripleValue�� PairValue�� ��� ã�Ҵٸ�
        if (TripleValue != EPlayingCardValue::None && PairValue != EPlayingCardValue::None)
        {
            // Triple�� Pair�� ���� High Value ����
            HighValuesOfHandRank.Add(TripleValue);
            HighValuesOfHandRank.Add(PairValue);

            // True ��ȯ
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* Flush
* : ���� ������ ī�� 5��
* 
* ���� �ڵ�ī�忡 �����ϴ� Suit���� Set���� �з��ϰ�,
* �з��� Suit�� �ش��ϴ� ī�尡 5���̻� �����ϴ� �� Ȯ��
*/
bool UTHHoldemPlayManager::IsFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // Ace(1)ī�尡 �ִٸ� ��� HighAce(14)�� �ٲپ��ش�.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // ī�忡 �����ϴ� Suit���� Set���� �з�
    TSet<EPlayingCardSuit> CardSuits;
    for (auto& FinalCard : FinalCards)
    {
        CardSuits.Add(FinalCard.Suit);
    }

    // �з��� Suit
    for (auto& CardSuit : CardSuits)
    {
        // Suit�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardSuit = FinalCards.FilterByPredicate([&CardSuit](const FPlayingCard& FinalCard) {
            return FinalCard.Suit == CardSuit;
        });

        // ī�� ���� 5���̶�� Flush
        if (CardsForCardSuit.Num() >= 5)
        {
            // 5�� �� HighValueCard ����
            FPlayingCard HighValueCard = *Algo::MaxElement(CardsForCardSuit, [](const FPlayingCard& CardA, const FPlayingCard& CardB) {
                return CardA.Value < CardB.Value;
            });

            // HighValue ����
            HighValuesOfHandRank.Add(HighValueCard.Value);

            // True ��ȯ
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* Straight
* : �����ϴ� 5���� ī��
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� ���ڸ� Set���� �з��Ͽ� ������ ��
* 5���� ���ӵ� Value�� �����ϴ� �� Ȯ��
*/
bool UTHHoldemPlayManager::IsStraight(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);

        // Aceī�尡 �����ϸ� 1�� 14�� ������ ���� �� �ֵ��� MaxAceī��(14)�� �߰��� Add ���ش�.
        if (FinalCard.Value == EPlayingCardValue::Ace)
        {
            CardValues.Add(EPlayingCardValue::HighAce);
        }
    }

    // Value List�� ������������ Value ����
    CardValues.Sort([](const EPlayingCardValue& CardValueA, const EPlayingCardValue& CardValueB) {
        return CardValueA > CardValueB;
    });

    int32 StraightNumCount = 0; // ���Ӽ� üũ ī��Ʈ
    int32 PrevCardNum = 0; // ���� ī���� ����
    for (auto& CardValue : CardValues)
    {
        // ���� ī�� ����
        int32 CardNum = static_cast<int32>(CardValue);

        // ù��° üũ�Ǵ� ����
        if (StraightNumCount == 0) 
        {
            // ���� ���� �����̹Ƿ� �ڵ巩ũ�� ���̹�� ����
            HighValuesOfHandRank.Add(CardValue);

            StraightNumCount = 1;
            PrevCardNum = CardNum;
        }
        // ���� ī���� ���ں��� 1�� ������
        else if (CardNum == PrevCardNum - 1) 
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

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* Three of a kind(Triple)
* : ���� ���� ī�� 3��
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 3�� �����ϴ� �� Ȯ��
*/
bool UTHHoldemPlayManager::IsThreeOfAKind(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)ī�尡 �ִٸ� ��� HighAce(14)�� �ٲپ��ش�.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // ������������ ī�� ����
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // �з��� Value 
    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // ī�� ���� 3���̶��
        if (CardsForCardValue.Num() == 3)
        {
            // �ڵ巩ũ�� ���̹�� ����
            HighValuesOfHandRank.Add(CardValue);

            // ����ī�忡�� Ʈ���� Value�� �ش��ϴ� ī�� ����
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });

            // Ʈ���� Value�� ������ ī�� �� ���� ���� ���� Value ī�� 2���� ŰĿ�� ����
            Kickers.Add(FinalCards[0]);
            Kickers.Add(FinalCards[1]);

            // True ��ȯ
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

/**
* Two pair
* : ���� ���� ī�� 2�� 2��Ʈ
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 2�徿 2��Ʈ�� �����ϴ� �� Ȯ��
*/
bool UTHHoldemPlayManager::IsTwoPair(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)ī�尡 �ִٸ� ��� HighAce(14)�� �ٲپ��ش�.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // ������������ ī�� ����
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    int32 PairCount = 0; // Pair ��(���� ������ ī�� �� 2)
    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // ���� Value�� ī�尡 �� ���̶��
        if (CardsForCardValue.Num() == 2)
        {
            // Pair �� ����
            ++PairCount;

            // �ڵ巩ũ�� ���̹�� ����
            HighValuesOfHandRank.Add(CardValue);

            // ����ī�忡�� Pair Value�� �ش��ϴ� ī�� ����
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });

            // Pair ���� 2���� Two Pair�� �Ǿ��ٸ�
            if (PairCount == 2)
            {
                // 2���� Pair Value�� ������ ī�� �� ���� ���� ���� Value ī�� 1���� ŰĿ�� ����
                Kickers.Add(FinalCards[0]);

                // True ��ȯ
                bResult = true;
                break;
            }
        }
    }

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

/**
* One pair
* : ���� ���� ī�� 2�� 1��Ʈ
* 
* ���� �ڵ�ī�忡 �����ϴ� Value���� Set���� �з��� ��
* �з��� Value�� �ش��ϴ� ī�尡 ���� �ڵ�ī�� ���� 2�� �����ϴ� �� Ȯ��
*/
bool UTHHoldemPlayManager::IsOnePair(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)ī�尡 �ִٸ� ��� HighAce(14)�� �ٲپ��ش�.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // ������������ ī�� ����
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // ī�忡 �����ϴ� Value���� Set���� �з�
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value�� �ش��ϴ� ī�帮��Ʈ
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // Pair üũ
        if (CardsForCardValue.Num() == 2)
        {
            // �ڵ巩ũ�� ���̹�� ����
            HighValuesOfHandRank.Add(CardValue);

            // ����ī�忡�� Pair Value�� �ش��ϴ� ī�� ����
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });

            // Pair Value�� ������ ī�� �� ���� ���� ���� Value ī�� 3���� ŰĿ�� ����
            Kickers.Add(FinalCards[0]);
            Kickers.Add(FinalCards[1]);
            Kickers.Add(FinalCards[2]);

            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

bool UTHHoldemPlayManager::IsHighCard(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> Kickers;

    // Ace(1)ī�尡 �ִٸ� ��� HighAce(14)�� �ٲپ��ش�.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // ������������ ī�� ����
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // ����ī�� �� ���� ���� ���� Value ī�� 5���� ŰĿ�� ����
    for (int32 CardIndex = 0; CardIndex < 5; ++CardIndex)
    {
        Kickers.Add(FinalCards[CardIndex]);
    }
    
    PlayerHandRankInfo.Kickers = Kickers;
    return true;
}
