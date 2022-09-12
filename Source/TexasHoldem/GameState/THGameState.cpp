// Fill out your copyright notice in the Description page of Project Settings.

#include "THGameState.h"
#include "GameMode/THGameMode.h"
#include "PlayerState/THPlayerState.h"
#include "Manager/THGameDebugManager.h"

ATHGameState::ATHGameState()
{
    // MaxPlayerCount 수 만큼 인게임 플레이어 자리 생성
    PlayersForTable.Init(nullptr, MaxPlayerCount);
}

void ATHGameState::Init()
{
    GamePlayState         = EGamePlayState::None;
    DealerPlayer          = nullptr;
    SmallBlindPlayer      = nullptr;
    BigBlindPlayer        = nullptr;
    CurrentTurnPlayer     = nullptr;
    BettingRound          = EBettingRound::None;
    TotalPotMoney         = 0;
    HighRoundBettingMoney = 0;
    MinRaiseMoney         = BlindBettingMoney;
    bAppeardRaiseAction   = false;
    CommunityCards.Empty();
    InGamePlayersAll.Empty();
    InGameSurvivedPlayers.Empty();
}

void ATHGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATHGameState, GamePlayCount);
    DOREPLIFETIME(ATHGameState, DealerPlayer);
    DOREPLIFETIME(ATHGameState, SmallBlindPlayer);
    DOREPLIFETIME(ATHGameState, BigBlindPlayer);
    DOREPLIFETIME(ATHGameState, CurrentTurnPlayer);
    DOREPLIFETIME(ATHGameState, GamePlayState);
    DOREPLIFETIME(ATHGameState, BettingRound);
    DOREPLIFETIME(ATHGameState, BlindBettingMoney);
    DOREPLIFETIME(ATHGameState, TotalPotMoney);
    DOREPLIFETIME(ATHGameState, CallMoneyForCurrentPlayer);
    DOREPLIFETIME(ATHGameState, HighRoundBettingMoney);
    DOREPLIFETIME(ATHGameState, MinRaiseMoney);
    DOREPLIFETIME(ATHGameState, bAppeardRaiseAction);
    DOREPLIFETIME(ATHGameState, CommunityCards);
    DOREPLIFETIME(ATHGameState, PlayersForTable);
    DOREPLIFETIME(ATHGameState, InGamePlayersAll);
    DOREPLIFETIME(ATHGameState, InGameSurvivedPlayers);
}

const int32 ATHGameState::GetGamePlayCount() const
{
    return GamePlayCount;
}

const int32 ATHGameState::GetLoginUserCount() const
{
    return PlayerArray.Num();
}

const int32 ATHGameState::GetLogInGamePlayerCount() const
{
    return InGameSurvivedPlayers.Num();
}

const EGamePlayState ATHGameState::GetGamePlayState() const
{
    return GamePlayState;
}

ATHPlayerState* ATHGameState::GetPlayerForPlayerRole(const EPlayerRole InPlayerRole) const
{
    ATHPlayerState* ResultPlayer = nullptr;

    switch (InPlayerRole)
    {
    case EPlayerRole::Dealer:     ResultPlayer = DealerPlayer;     break;
    case EPlayerRole::SmallBlind: ResultPlayer = SmallBlindPlayer; break;
    case EPlayerRole::BigBlind:   ResultPlayer = BigBlindPlayer;   break;
    default:
        break;
    }

    return ResultPlayer;
}

ATHPlayerState* ATHGameState::GetCurrentTurnPlayer() const
{
    return CurrentTurnPlayer;
}

const EBettingRound ATHGameState::GetBettingRound() const
{
    return BettingRound;
}

const int32 ATHGameState::GetBlindBettingMoney() const
{
    return BlindBettingMoney;
}

const int32 ATHGameState::GetTotalPotMoney() const
{
    return TotalPotMoney;
}

const int32 ATHGameState::GetCallMoneyForCurrentPlayer() const
{
    return CallMoneyForCurrentPlayer;
}

const int32 ATHGameState::GetHighRoundBettingMoney() const
{
    return HighRoundBettingMoney;
}

const int32 ATHGameState::GetMinRaiseMoney() const
{
    return MinRaiseMoney;
}

const bool ATHGameState::IsAppeardRaiseAction() const
{
    return bAppeardRaiseAction;
}

TArray<FPlayingCard> ATHGameState::GetCommunityCards() const
{
    return CommunityCards;
}

TArray<ATHPlayerState*> ATHGameState::GetPlayersForTable() const
{
    return PlayersForTable;
}

TArray<ATHPlayerState*> ATHGameState::GetInGamePlayersAll() const
{
    return InGamePlayersAll;
}

TArray<ATHPlayerState*> ATHGameState::GetInGameSurvivedPlayers() const
{
    return InGameSurvivedPlayers;
}

ATHPlayerState* ATHGameState::GetNextInGamePlayer(ATHPlayerState* InCurrentPlayer) const
{
    int32 CurrentPlayerIndex = InGameSurvivedPlayers.Find(InCurrentPlayer);
    int32 NextPlayerIndex = (CurrentPlayerIndex + 1) % GetLogInGamePlayerCount();
    
    return InGameSurvivedPlayers[NextPlayerIndex];
}

void ATHGameState::IncreaseGamePlayCount()
{
    ++GamePlayCount;
}

void ATHGameState::SetPlayerForPlayerRole(ATHPlayerState* InTHPlayerState, const EPlayerRole& InPlayerRole)
{
    switch (InPlayerRole)
    {
    case EPlayerRole::Dealer:     DealerPlayer     = InTHPlayerState; break;
    case EPlayerRole::SmallBlind: SmallBlindPlayer = InTHPlayerState; break;
    case EPlayerRole::BigBlind:   BigBlindPlayer   = InTHPlayerState; break;
    default:
        break;
    }
}

void ATHGameState::SetGamePlayState(const EGamePlayState& InGamePlayState)
{
    GamePlayState = InGamePlayState;
}
void ATHGameState::SetCurrentTurnPlayer(ATHPlayerState* InCurrentTurnPlayer)
{
    CurrentTurnPlayer = InCurrentTurnPlayer;
}

void ATHGameState::SetBettingRound(const EBettingRound& InBettingRound)
{
    BettingRound = InBettingRound;    
}

void ATHGameState::SetBlindBettingMoney(const int32& InBlindBettingMoney)
{
    BlindBettingMoney = InBlindBettingMoney;
    SetMinRaiseMoney(BlindBettingMoney);
}

void ATHGameState::AddBlindBettingMoney(const int32& InBlindBettingMoney)
{
    BlindBettingMoney += InBlindBettingMoney;
}

void ATHGameState::SetTotalPotMoney(const int32& InTotalPotMoney)
{
    TotalPotMoney = InTotalPotMoney;
}

void ATHGameState::AddTotalPotMoney(const int32& InTotalPotMoney)
{
    TotalPotMoney += InTotalPotMoney;
}

void ATHGameState::SetCallMoneyForCurrentPlayer(const int32& InCallMoneyForCurrentPlayer)
{
    CallMoneyForCurrentPlayer = InCallMoneyForCurrentPlayer;
}

void ATHGameState::SetHighRoundBettingMoney(const int32& InHighRoundBettingMoney)
{
    HighRoundBettingMoney = InHighRoundBettingMoney;
}

void ATHGameState::SetMinRaiseMoney(const int32& InMinRaiseMoney)
{
    MinRaiseMoney = InMinRaiseMoney;
}

void ATHGameState::SetAppeardRaiseAction(const bool& bInApperedRaiseAction)
{
    bAppeardRaiseAction = bInApperedRaiseAction;
}

void ATHGameState::SetCommunityCards(const TArray<FPlayingCard>& InCommunityCards)
{
    CommunityCards = InCommunityCards;
}

void ATHGameState::SetPlayersForTable(const TArray<ATHPlayerState*>& InPlayersForTableSeattingPos)
{
    PlayersForTable = InPlayersForTableSeattingPos;
}

void ATHGameState::SetInGamePlayersAll(const TArray<ATHPlayerState*>& InInGamePlayersAll)
{
    InGamePlayersAll = InInGamePlayersAll;
}

void ATHGameState::SetInGameSurvivedPlayers(const TArray<ATHPlayerState*>& InInGameSurvivedPlayers)
{
    InGameSurvivedPlayers = InInGameSurvivedPlayers;
}

void ATHGameState::RemovePlayerInGamePlayers(ATHPlayerState* InPlayerState)
{
    InGameSurvivedPlayers.Remove(InPlayerState);
}
