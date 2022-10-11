// Fill out your copyright notice in the Description page of Project Settings.

#include "THGameState.h"
#include "GameMode/THGameMode.h"
#include "PlayerState/THPlayerState.h"
#include "Manager/THGameDebugManager.h"

ATHGameState::ATHGameState()
{
    // MaxPlayerCount 수 만큼 인게임 플레이어 자리 생성
    PlayersForTableSeattingPos.Init(nullptr, MaxPlayerCount);

    PrimaryActorTick.bCanEverTick = true;
}

void ATHGameState::Init()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    GamePlayState         = EGamePlayState::None;
    CurrentTurnPlayer     = nullptr;
    BettingRound          = EBettingRound::None;
    TotalPotMoney         = 0;
    HighRoundBettingMoney = 0;
    MinRaiseMoney         = BlindBettingMoney;
    bAppeardRaiseAction   = false;
    WinnerPlayers.Empty();
    CommunityCards.Empty();
    InGamePlayersAll.Empty();
    InGameSurvivedPlayers.Empty();

    if (RemainBettingTimerHandle.IsValid())
    {
        GetWorldTimerManager().ClearTimer(RemainBettingTimerHandle);
    }


    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameState::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    OnNotifyRestartGame.AddDynamic(this, &ATHGameState::Init);
}

void ATHGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATHGameState, GamePlayCount);
    DOREPLIFETIME(ATHGameState, CurrentTurnPlayer);
    DOREPLIFETIME(ATHGameState, WinnerPlayers);
    DOREPLIFETIME(ATHGameState, GamePlayState);
    DOREPLIFETIME(ATHGameState, BettingRound);
    DOREPLIFETIME(ATHGameState, BlindBettingMoney);
    DOREPLIFETIME(ATHGameState, TotalPotMoney);
    DOREPLIFETIME(ATHGameState, CallMoneyForCurrentPlayer);
    DOREPLIFETIME(ATHGameState, HighRoundBettingMoney);
    DOREPLIFETIME(ATHGameState, MinRaiseMoney);
    DOREPLIFETIME(ATHGameState, RemainBettingTimeSeconds);
    DOREPLIFETIME(ATHGameState, bAppeardRaiseAction);
    DOREPLIFETIME(ATHGameState, CommunityCards);
    DOREPLIFETIME(ATHGameState, PlayersForTableSeattingPos);
    DOREPLIFETIME(ATHGameState, InGamePlayersAll);
    DOREPLIFETIME(ATHGameState, InGameSurvivedPlayers);
}

void ATHGameState::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (RemainBettingTimerHandle.IsValid() && GetWorldTimerManager().IsTimerActive(RemainBettingTimerHandle))
    {
        RemainBettingTimeSeconds = GetWorldTimerManager().GetTimerRemaining(RemainBettingTimerHandle);
    }
}

const int32 ATHGameState::GetGamePlayCount() const
{
    return GamePlayCount;
}

const int32 ATHGameState::GetLoginPlayerCount() const
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
    ATHPlayerState* ResultPlayer = *InGamePlayersAll.FindByPredicate([&InPlayerRole](const ATHPlayerState* InGamePlayer) {
        return InGamePlayer->GetPlayerRole() == InPlayerRole;
    });

    return ResultPlayer;
}

ATHPlayerState* ATHGameState::GetCurrentTurnPlayer() const
{
    return CurrentTurnPlayer;
}

TArray<ATHPlayerState*> ATHGameState::GetWinnerPlayers() const
{
    return WinnerPlayers;
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

TArray<ATHPlayerState*> ATHGameState::GetPlayersForTableSeattingPos() const
{
    return PlayersForTableSeattingPos;
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

const float ATHGameState::GetRemainBettingTimeSeconds() const
{
    return RemainBettingTimeSeconds;
}

void ATHGameState::IncreaseGamePlayCount()
{
    ++GamePlayCount;
}

void ATHGameState::InitGamePlayCount()
{
    GamePlayCount = 0;
}

void ATHGameState::SetGamePlayState(const EGamePlayState& InGamePlayState)
{
    GamePlayState = InGamePlayState;
}

void ATHGameState::SetCurrentTurnPlayer(ATHPlayerState* InCurrentTurnPlayer)
{
    CurrentTurnPlayer = InCurrentTurnPlayer;
}

void ATHGameState::SetWinnerPlayers(TArray<ATHPlayerState*> InWinnerPlayers)
{
    WinnerPlayers = InWinnerPlayers;
    for (ATHPlayerState* WinnerPlayer : WinnerPlayers)
    {
        WinnerPlayer->SetIsWinner(true);
    }
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

void ATHGameState::SetPlayersForTableSeattingPos(const TArray<ATHPlayerState*>& InPlayersForTableSeattingPos)
{
    PlayersForTableSeattingPos = InPlayersForTableSeattingPos;
}

void ATHGameState::SetInGamePlayersAll(const TArray<ATHPlayerState*>& InInGamePlayersAll)
{
    InGamePlayersAll = InInGamePlayersAll;
}

void ATHGameState::SetInGameSurvivedPlayers(const TArray<ATHPlayerState*>& InInGameSurvivedPlayers)
{
    InGameSurvivedPlayers = InInGameSurvivedPlayers;
}

void ATHGameState::RemoveInGameSurvivedPlayer(ATHPlayerState* InPlayerState)
{
    InGameSurvivedPlayers.RemoveSingle(InPlayerState);
}

void ATHGameState::NotifyRestartGame()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));
    if (OnNotifyRestartGame.IsBound())
    {
        OnNotifyRestartGame.Broadcast();
    }

    Multicast_SendNotifyRestartGame();
}

void ATHGameState::Multicast_SendNotifyRestartGame_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));
    if (OnNotifyRestartGame.IsBound())
    {
        OnNotifyRestartGame.Broadcast();
    }
}

void ATHGameState::OnRep_GamePlayState()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));

    if (OnChangedGamePlayState.IsBound())
    {
        OnChangedGamePlayState.Broadcast(GamePlayState);
    }
}

void ATHGameState::OnRep_CurrentTurnPlayer()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));

    if (OnChangedCurrentTurnPlayer.IsBound())
    {
        OnChangedCurrentTurnPlayer.Broadcast(CurrentTurnPlayer);
    }
}

void ATHGameState::OnRep_BettingRound()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));

    if (OnChangedBettingRound.IsBound())
    {
        OnChangedBettingRound.Broadcast(BettingRound);
    }
}

void ATHGameState::OnRep_CommunityCards()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));

    if (OnChangedCommunityCards.IsBound())
    {
        OnChangedCommunityCards.Broadcast(CommunityCards);
    }
}

void ATHGameState::OnRep_PlayersForTableSeattingPos()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));

    if (OnChangedPlayersForTableSeattingPos.IsBound())
    {
        OnChangedPlayersForTableSeattingPos.Broadcast(PlayersForTableSeattingPos);
    }
}