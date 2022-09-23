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
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

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

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
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
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    FPlayingCard PlayingCard;
    if (CardDeck.Num() == 0)
    {
        return PlayingCard;
    }

    // CardDeck의 Index 추출 후 해당 Index 데이터 삭제
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

    UE_LOG(LogTemp, Log, TEXT("[%s] End. CardDeckIndex:%d, CardDeckValue:%d"), 
        ANSI_TO_TCHAR(__FUNCTION__), CardDeckArrayIndex, CardDeckValue);

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
    // Add 5 cards for community card set
    for (int i = 0; i < 5; ++i)
    {
        CommunityCards.Add(GetCardFromCardDeck());
    }
    
    for (FPlayingCard& CommunityCard : CommunityCards)
    {
        UE_LOG(LogTemp, Log, TEXT("[%s] BettingRound(%s) Suit(%s) Value(%s)"),
            ANSI_TO_TCHAR(__FUNCTION__),
            *UTHGameDebugManager::GetEnumAsString(BettingRound),
            *UTHGameDebugManager::GetEnumAsString(CommunityCard.Suit),
            *UTHGameDebugManager::GetEnumAsString(CommunityCard.Value));
    }
}

FPlayerHandRankInfo UTHHoldemPlayManager::GetHandRankInfo(const TArray<FPlayingCard> InHandCards)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    FPlayerHandRankInfo PlayerHandRankInfo;

    // 핸드카드는 2장이어야 한다.
    if (InHandCards.Num() != 2)
    {
        return PlayerHandRankInfo;
    }

    // 공유카드와 핸드 2장을 합친 카드 생성
    TArray<FPlayingCard> FinalHandCards;
    FinalHandCards.Append(CommunityCards);
    FinalHandCards.Append(InHandCards);
    
    //// 7장의 최종카드가 만들어지지 않았다면 공백카드로 채워 7장을 만들어 아래 로직 수행
    //if (FinalHandCards.Num() < 7)
    //{
    //    TArray<FPlayingCard> BlankCards;
    //    BlankCards.Init(FPlayingCard(), 7 - FinalHandCards.Num());
    //    FinalHandCards.Append(BlankCards);
    //}

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
        // Error. 이 곳으로 빠지는 경우는 없어야 한다.
        checkNoEntry();
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] End. HandRank:%s"), 
        ANSI_TO_TCHAR(__FUNCTION__),
        *UTHGameDebugManager::GetEnumAsString(PlayerHandRankInfo.HandRank));

    return PlayerHandRankInfo;
}

/*
* RoyalFlush 
* : Straight Flush 중 10, J, Q, K, A인 조합
* 
* 카드들을 Suit 기준 Array로 분류한 후 Array 별로 10, J, Q, K, A 카드가 존재하는지 확인
*/
bool UTHHoldemPlayManager::IsRoyalFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;

    // 최종 카드를 Suit 기준 TMap으로 분류 (Key : Card suit, Value : Card Value)
    TMap<EPlayingCardSuit, TArray<EPlayingCardValue>> CardsForSuit;
    CardsForSuit.Add(EPlayingCardSuit::Spades);
    CardsForSuit.Add(EPlayingCardSuit::Diamonds);
    CardsForSuit.Add(EPlayingCardSuit::Hearts);
    CardsForSuit.Add(EPlayingCardSuit::Clubs);

    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardsForSuit[FinalCard.Suit].Add(FinalCard.Value);
    }

    // Suit가 동일한 카드들에 대해 CardValue 체크
    for (auto& CardForSuit : CardsForSuit)
    {
        TArray<EPlayingCardValue>& CardValuesForSuit = CardForSuit.Value;
        
        // 카드가 5장 미만이라면 스킵
        if (CardValuesForSuit.Num() < 5)
        {
            continue;
        }
        
        // 10, 11(J), 12(Q), 13(K), 14(A)가 존재하면 True 반환
        if (CardValuesForSuit.Contains(EPlayingCardValue::Ten) &&
            CardValuesForSuit.Contains(EPlayingCardValue::Jack) &&
            CardValuesForSuit.Contains(EPlayingCardValue::Queen) &&
            CardValuesForSuit.Contains(EPlayingCardValue::King) &&
            CardValuesForSuit.Contains(EPlayingCardValue::Ace))
        {
            // 핸드랭크 카드리스트 적재
            CardsForHandRank.Add(FPlayingCard{ CardForSuit.Key, EPlayingCardValue::Ten });
            CardsForHandRank.Add(FPlayingCard{ CardForSuit.Key, EPlayingCardValue::Jack });
            CardsForHandRank.Add(FPlayingCard{ CardForSuit.Key, EPlayingCardValue::Queen });
            CardsForHandRank.Add(FPlayingCard{ CardForSuit.Key, EPlayingCardValue::King });
            CardsForHandRank.Add(FPlayingCard{ CardForSuit.Key, EPlayingCardValue::Ace });            

            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    return bResult;
}

/**
* StraightFlush 
* : 문양이 같으며 동시에 연속하는 5장의 카드
* 
* 카드들을 Value 기준으로 정렬한 후 Suit 기준 Array로 분류하고, 
* 분류된 Array 별로 5장의 연속된 Value가 존재하는 지 확인
*/
bool UTHHoldemPlayManager::IsStraightFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // 내림차순으로 카드 정렬
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });
    
    // 정렬된 최종 카드를 Suit 기준 TMap으로 분류 (Key : Card suit, Value : Card Value)
    TMap<EPlayingCardSuit, TArray<EPlayingCardValue>> CardsForSuit;
    CardsForSuit.Add(EPlayingCardSuit::Spades);
    CardsForSuit.Add(EPlayingCardSuit::Diamonds);
    CardsForSuit.Add(EPlayingCardSuit::Hearts);
    CardsForSuit.Add(EPlayingCardSuit::Clubs);

    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardsForSuit[FinalCard.Suit].Add(FinalCard.Value);
    }

    // Suit가 동일한 카드들에 대해 CardValue 체크
    for (auto& CardForSuit : CardsForSuit)
    {
        TArray<EPlayingCardValue>& CardValuesForSuit = CardForSuit.Value;

        // Suit가 동일한 카드가 5장 미만이라면 스킵
        if (CardValuesForSuit.Num() < 5)
        {
            continue;
        }

        // Ace카드가 존재하면 1과 14의 값으로 계산될 수 있도록 MaxAce카드(14)를 Array 뒤에 추가 해준다.
        if (CardValuesForSuit.Contains(EPlayingCardValue::Ace))
        {
            CardValuesForSuit.Add(EPlayingCardValue::HighAce);
        }

        int32 StraightNumCount = 0; // 연속성 체크 카운트
        int32 PrevCardNum = 0; // 직전 카드의 숫자
        for (EPlayingCardValue& CardValue : CardValuesForSuit)
        {
            // 실제 Value(HighAce라면 Ace로 변환)
            EPlayingCardValue ActualCardValue = (CardValue == EPlayingCardValue::HighAce) ? EPlayingCardValue::Ace : CardValue;

            // 현재 카드 숫자
            int32 CardNum = static_cast<int32>(CardValue);

            // 카드가 5장 미만이라면 스킵
            if (CardValuesForSuit.Num() < 5)
            {
                continue;
            }
                        
            // 첫번째 체크되는 숫자
            if (StraightNumCount == 0)
            {
                // 가장 높은 숫자이므로 핸드랭크의 하이밸류 적재
                HighValuesOfHandRank.Add(CardValue);

                // 핸드랭크 카드리스트 적재
                CardsForHandRank.Add(FPlayingCard{ CardForSuit.Key, ActualCardValue });

                StraightNumCount = 1;
                PrevCardNum = CardNum;
            }
            // 직전 카드의 숫자보다 1이 작은지
            else if (CardNum == PrevCardNum - 1)
            {
                // 핸드랭크 카드리스트 적재
                CardsForHandRank.Add(FPlayingCard{ CardForSuit.Key, ActualCardValue });

                ++StraightNumCount;
                PrevCardNum = CardNum;
            }
            // 연속성이 깨졌으므로 초기화
            else
            {
                PlayerHandRankInfo.CardsForHandRank.Empty();

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

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* FourOfAKind
* : 같은 값의 카드 4장
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 4장 존재하는 지 확인
*/
bool UTHHoldemPlayManager::IsFourOfAKind(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)카드가 있다면 모두 HighAce(14)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // 내림차순으로 카드 정렬
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // HighAce(14)카드를 다시 모두 Ace(1)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::HighAce; }))
    {
        AceCard->Value = EPlayingCardValue::Ace;
    }

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }
    
    // 분류된 Value 
    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;        
        });

        // 카드 수가 4장이라면
        if (CardsForCardValue.Num() == 4)
        {
            // 핸드랭크의 하이밸류 적재
            HighValuesOfHandRank.Add(CardValue);

            // 최종카드에서 포카드에 해당하는 카드 삭제
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });
            
            // 핸드랭크 카드리스트 적재. 
            CardsForHandRank.Add(FPlayingCard{ EPlayingCardSuit::Spades, CardValue });
            CardsForHandRank.Add(FPlayingCard{ EPlayingCardSuit::Diamonds, CardValue });
            CardsForHandRank.Add(FPlayingCard{ EPlayingCardSuit::Hearts, CardValue });
            CardsForHandRank.Add(FPlayingCard{ EPlayingCardSuit::Clubs, CardValue });

            // 포카드를 제외한 카드 중 가장 높은 Value를 키커에 적재
            Kickers.Add(FinalCards[0]);

            // True 반환
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

/**
* FullHouse
* : Three of a kind(Triple)와 One Pair의 조합
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후 
* 분류된 Value에 해당하는 Triple과 One Pair가 존재하는 지 확인 (Triple과 One Pair는 서로 다른 Value)
*/
bool UTHHoldemPlayManager::IsFullHouse(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // Ace(1)카드가 있다면 모두 HighAce(14)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // 내림차순으로 카드 정렬
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // HighAce(14)카드를 다시 모두 Ace(1)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::HighAce; }))
    {
        AceCard->Value = EPlayingCardValue::Ace;
    }

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // Value로 바로확인
    EPlayingCardValue TripleValue = EPlayingCardValue::None; // Triple(같은 숫자의 카드 수 3장) Value
    EPlayingCardValue PairValue = EPlayingCardValue::None;   // Pair(같은 숫자의 카드 수 2) Value
    for (EPlayingCardValue& CardValue : CardValues)
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
                // 이미 찾은 Pair가 없는 경우 Value 적재
                if (PairValue == EPlayingCardValue::None)
                {
                    // 핸드랭크 카드리스트 적재
                    CardsForHandRank.Add(CardsForCardValue[0]);
                    CardsForHandRank.Add(CardsForCardValue[1]);

                    PairValue = CardValue;
                }
            }
            break;
        case 3: [[fallthrough]];
        case 4:
            // Triple 체크
            if (CardsForCardValue.Num() == 3)
            {
                // 이미 찾은 Triple이 없는 경우 Triple로 적재
                if (TripleValue == EPlayingCardValue::None)
                {
                    // 핸드랭크 카드리스트 적재
                    CardsForHandRank.Add(CardsForCardValue[0]);
                    CardsForHandRank.Add(CardsForCardValue[1]);
                    CardsForHandRank.Add(CardsForCardValue[2]);

                    TripleValue = CardValue;
                }
                // 이미 찾은 Triple이 있다면 Pair로 2장만 적재
                else
                {
                    // 핸드랭크 카드리스트 적재
                    CardsForHandRank.Add(CardsForCardValue[0]);
                    CardsForHandRank.Add(CardsForCardValue[1]);

                    PairValue = CardValue;
                }
            }
            break;
        default:
            break;
        }

        // TripleValue와 PairValue를 모두 찾았다면
        if (TripleValue != EPlayingCardValue::None && PairValue != EPlayingCardValue::None)
        {
            // Triple과 Pair에 대한 High Value 적재
            HighValuesOfHandRank.Add(TripleValue);
            HighValuesOfHandRank.Add(PairValue);

            // True 반환
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* Flush
* : 같은 문양의 카드 5장
* 
* 최종 핸드카드에 존재하는 Suit들을 Set으로 분류하고,
* 분류된 Suit에 해당하는 카드가 5장이상 존재하는 지 확인
*/
bool UTHHoldemPlayManager::IsFlush(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // Ace(1)카드가 있다면 모두 HighAce(14)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // 카드에 존재하는 Suit들을 Set으로 분류
    TSet<EPlayingCardSuit> CardSuits;
    for (auto& FinalCard : FinalCards)
    {
        CardSuits.Add(FinalCard.Suit);
    }

    // 분류된 Suit
    for (auto& CardSuit : CardSuits)
    {
        // Suit에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardSuit = FinalCards.FilterByPredicate([&CardSuit](const FPlayingCard& FinalCard) {
            return FinalCard.Suit == CardSuit;
        });

        // 카드 수가 5장이라면 Flush
        if (CardsForCardSuit.Num() >= 5)
        {
            // 높은 Value 순의 내림차순으로 정렬
            CardsForCardSuit.Sort([](const FPlayingCard& CardA, const FPlayingCard& CardB) {
                return CardA.Value > CardB.Value;
            });

            // HighValue 적재
            HighValuesOfHandRank.Add(CardsForCardSuit[0].Value);

            // 핸드랭크 카드리스트 적재
            for (int32 CardIndex = 0; CardIndex < 5; ++CardIndex)
            {
                // 실제 Value(HighAce라면 Ace로 변환)
                EPlayingCardValue ActualCardValue = (CardsForCardSuit[CardIndex].Value == EPlayingCardValue::HighAce) ? EPlayingCardValue::Ace : CardsForCardSuit[CardIndex].Value;
                CardsForHandRank.Add(FPlayingCard{ CardsForCardSuit[CardIndex].Suit, ActualCardValue });
            }

            // True 반환
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* Straight
* : 연속하는 5장의 카드
* 
* 최종 핸드카드에 존재하는 Value들의 숫자를 Set으로 분류하여 정렬한 후
* 5장의 연속된 Value가 존재하는 지 확인
*/
bool UTHHoldemPlayManager::IsStraight(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);

        // Ace카드가 존재하면 1과 14의 값으로 계산될 수 있도록 MaxAce카드(14)를 추가로 Add 해준다.
        if (FinalCard.Value == EPlayingCardValue::Ace)
        {
            CardValues.Add(EPlayingCardValue::HighAce);
        }
    }

    // Value List를 내림차순으로 Value 정렬
    CardValues.Sort([](const EPlayingCardValue& CardValueA, const EPlayingCardValue& CardValueB) {
        return CardValueA > CardValueB;
    });

    int32 StraightNumCount = 0; // 연속성 체크 카운트
    int32 PrevCardNum = 0; // 직전 카드의 숫자
    for (auto& CardValue : CardValues)
    {
        // 실제 Value(HighAce라면 Ace로 변환)
        EPlayingCardValue ActualCardValue = (CardValue == EPlayingCardValue::HighAce) ? EPlayingCardValue::Ace : CardValue;

        // 현재 카드 숫자
        int32 CardNum = static_cast<int32>(CardValue);

        // 첫번째 체크되는 숫자
        if (StraightNumCount == 0) 
        {
            // 가장 높은 숫자이므로 핸드랭크의 하이밸류 적재
            HighValuesOfHandRank.Add(CardValue);
            
            // 핸드랭크 카드리스트 적재
            CardsForHandRank.Add(*FinalCards.FindByPredicate([&ActualCardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == ActualCardValue;
            }));

            StraightNumCount = 1;
            PrevCardNum = CardNum;
        }
        // 직전 카드의 숫자보다 1이 작은지
        else if (CardNum == PrevCardNum - 1) 
        {
            // 핸드랭크 카드리스트 적재
            CardsForHandRank.Add(*FinalCards.FindByPredicate([&ActualCardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == ActualCardValue;
            }));

            ++StraightNumCount;
            PrevCardNum = CardNum;
        }
        // 연속성이 깨졌으므로 초기화
        else 
        {
            // 핸드랭크 카드리스트 적재
            CardsForHandRank.Empty();

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

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    return bResult;
}

/**
* Three of a kind(Triple)
* : 같은 값의 카드 3장
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 3장 존재하는 지 확인
*/
bool UTHHoldemPlayManager::IsThreeOfAKind(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)카드가 있다면 모두 HighAce(14)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // 내림차순으로 카드 정렬
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // HighAce(14)카드를 다시 모두 Ace(1)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::HighAce; }))
    {
        AceCard->Value = EPlayingCardValue::Ace;
    }

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    // 분류된 Value 
    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // 카드 수가 3장이라면
        if (CardsForCardValue.Num() == 3)
        {
            // 핸드랭크 카드리스트 적재
            CardsForHandRank.Add(CardsForCardValue[0]);
            CardsForHandRank.Add(CardsForCardValue[1]);
            CardsForHandRank.Add(CardsForCardValue[2]);

            // 핸드랭크의 하이밸류 적재
            HighValuesOfHandRank.Add(CardValue);

            // 최종카드에서 트리플 Value에 해당하는 카드 삭제
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });

            // 트리플 Value를 제외한 카드 중 가장 높은 순의 Value 카드 2장을 키커에 적재
            Kickers.Add(FinalCards[0]);
            Kickers.Add(FinalCards[1]);

            // True 반환
            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

/**
* Two pair
* : 같은 값의 카드 2장 2세트
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 2장씩 2세트가 존재하는 지 확인
*/
bool UTHHoldemPlayManager::IsTwoPair(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)카드가 있다면 모두 HighAce(14)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // 내림차순으로 카드 정렬
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // HighAce(14)카드를 다시 모두 Ace(1)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::HighAce; }))
    {
        AceCard->Value = EPlayingCardValue::Ace;
    }

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    int32 PairCount = 0; // Pair 수(같은 숫자의 카드 수 2)
    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // 같은 Value의 카드가 두 장이라면
        if (CardsForCardValue.Num() == 2)
        {
            // Pair 수 증가
            ++PairCount;

            // 핸드랭크 카드리스트 적재
            CardsForHandRank.Add(CardsForCardValue[0]);
            CardsForHandRank.Add(CardsForCardValue[1]);

            // 핸드랭크의 하이밸류 적재
            HighValuesOfHandRank.Add(CardValue);

            // 최종카드에서 Pair Value에 해당하는 카드 삭제
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });

            // Pair 수가 2개로 Two Pair가 되었다면
            if (PairCount == 2)
            {
                // 2개의 Pair Value를 제외한 카드 중 가장 높은 순의 Value 카드 1장을 키커에 적재
                Kickers.Add(FinalCards[0]);

                // True 반환
                bResult = true;
                break;
            }
        }
    }

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

/**
* One pair
* : 같은 값의 카드 2장 1세트
* 
* 최종 핸드카드에 존재하는 Value들을 Set으로 분류한 후
* 분류된 Value에 해당하는 카드가 최종 핸드카드 내에 2장 존재하는 지 확인
*/
bool UTHHoldemPlayManager::IsOnePair(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    bool bResult = false;
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<FPlayingCard> CardsForHandRank;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)카드가 있다면 모두 HighAce(14)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // 내림차순으로 카드 정렬
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // HighAce(14)카드를 다시 모두 Ace(1)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::HighAce; }))
    {
        AceCard->Value = EPlayingCardValue::Ace;
    }

    // 카드에 존재하는 Value들을 Set으로 분류
    TSet<EPlayingCardValue> CardValues;
    for (FPlayingCard& FinalCard : FinalCards)
    {
        CardValues.Add(FinalCard.Value);
    }

    for (EPlayingCardValue& CardValue : CardValues)
    {
        // Value에 해당하는 카드리스트
        TArray<FPlayingCard> CardsForCardValue = FinalCards.FilterByPredicate([&CardValue](const FPlayingCard& FinalCard) {
            return FinalCard.Value == CardValue;
        });

        // Pair 체크
        if (CardsForCardValue.Num() == 2)
        {
            // 핸드랭크 카드리스트 적재
            CardsForHandRank.Add(CardsForCardValue[0]);
            CardsForHandRank.Add(CardsForCardValue[1]);

            // 핸드랭크의 하이밸류 적재
            HighValuesOfHandRank.Add(CardValue);

            // 최종카드에서 Pair Value에 해당하는 카드 삭제
            FinalCards.RemoveAll([&CardValue](const FPlayingCard& FinalCard) {
                return FinalCard.Value == CardValue;
            });

            // Pair Value를 제외한 카드 중 가장 높은 순의 Value 카드 3장을 키커에 적재
            Kickers.Add(FinalCards[0]);
            Kickers.Add(FinalCards[1]);
            Kickers.Add(FinalCards[2]);

            bResult = true;
            break;
        }
    }

    PlayerHandRankInfo.CardsForHandRank = CardsForHandRank;
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return bResult;
}

bool UTHHoldemPlayManager::IsHighCard(const TArray<FPlayingCard> FinalHandCards, FPlayerHandRankInfo& PlayerHandRankInfo)
{
    TArray<FPlayingCard> FinalCards = FinalHandCards;
    TArray<EPlayingCardValue> HighValuesOfHandRank;
    TArray<FPlayingCard> Kickers;

    // Ace(1)카드가 있다면 모두 HighAce(14)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::Ace; }))
    {
        AceCard->Value = EPlayingCardValue::HighAce;
    }

    // 내림차순으로 카드 정렬
    FinalCards.Sort([](const FPlayingCard& FinalCardA, const FPlayingCard& FinalCardB) {
        return FinalCardA.Value > FinalCardB.Value;
    });

    // HighAce(14)카드를 다시 모두 Ace(1)로 바꾸어준다.
    while (FPlayingCard* AceCard = FinalCards.FindByPredicate(
        [](const FPlayingCard& FinalCard) { return FinalCard.Value == EPlayingCardValue::HighAce; }))
    {
        AceCard->Value = EPlayingCardValue::Ace;
    }

    // 최종카드 중 가장 높은 순의 Value 카드 5장을 키커에 적재
    HighValuesOfHandRank.Add(FinalCards[0].Value);
    for (int32 CardIndex = 0; CardIndex < 5; ++CardIndex)
    {        
        Kickers.Add(FinalCards[CardIndex]);
    }
    
    PlayerHandRankInfo.HighValuesOfHandRank = HighValuesOfHandRank;
    PlayerHandRankInfo.Kickers = Kickers;
    return true;
}
