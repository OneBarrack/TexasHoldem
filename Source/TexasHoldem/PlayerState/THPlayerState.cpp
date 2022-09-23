// Fill out your copyright notice in the Description page of Project Settings.

#include "THPlayerState.h"
#include "GameState/THGameState.h"
#include "Controller/THPlayerController.h"
#include "Manager/THGameDebugManager.h"

ATHPlayerState::ATHPlayerState()
{
}

void ATHPlayerState::Init()
{
    bReady            = true;
    PlayerTurnState   = EPlayerTurnState::None;
    PlayerRole        = EPlayerRole::None;
    BettingMoney      = 0;
    RoundBettingMoney = 0;
    ProfitMoney       = 0;
    PlayerAction      = EPlayerAction::None;
    bIsWinner         = false;
    HandRankInfo      = FPlayerHandRankInfo();
    HandCards.Empty();
}

void ATHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATHPlayerState, bReady);
    DOREPLIFETIME(ATHPlayerState, TableSeattingPos);
    DOREPLIFETIME(ATHPlayerState, PlayerTurnState);
    DOREPLIFETIME(ATHPlayerState, PlayerNickName);
    DOREPLIFETIME(ATHPlayerState, Money);
    DOREPLIFETIME(ATHPlayerState, RequiredMoneyForCall);
    DOREPLIFETIME(ATHPlayerState, BettingMoney);
    DOREPLIFETIME(ATHPlayerState, RoundBettingMoney);
    DOREPLIFETIME(ATHPlayerState, ProfitMoney);
    DOREPLIFETIME(ATHPlayerState, PlayerRole);
    DOREPLIFETIME(ATHPlayerState, PlayerAction);
    DOREPLIFETIME(ATHPlayerState, bIsWinner);
    DOREPLIFETIME(ATHPlayerState, HandRankInfo);
    DOREPLIFETIME(ATHPlayerState, HandCards);
}
void ATHPlayerState::BeginPlay()
{
    Super::BeginPlay();

    GetGameState()->OnNotifyRestartGame.AddDynamic(this, &ATHPlayerState::Init);
}

ATHGameState* ATHPlayerState::GetGameState() const
{
    return GetWorld() ? Cast<ATHGameState>(GetWorld()->GetGameState()) : nullptr;
}

ATHPlayerController* ATHPlayerState::GetPlayerController() const
{
    return THPlayerController;
}

void ATHPlayerState::SetPlayerController(ATHPlayerController* InTHPlayerController)
{
    THPlayerController = InTHPlayerController;
}

const bool ATHPlayerState::IsReady() const
{
    return bReady;
}

const int32 ATHPlayerState::GetTableSeattingPos() const
{
    return TableSeattingPos;
}

const EPlayerTurnState ATHPlayerState::GetPlayerTurnState() const
{
    return PlayerTurnState;
}

const FString ATHPlayerState::GetPlayerNickName() const
{
    return PlayerNickName;
}

const EPlayerRole ATHPlayerState::GetPlayerRole() const
{
    return PlayerRole;
}

const int32 ATHPlayerState::GetMoney() const
{
    return Money;
}

const int32 ATHPlayerState::GetRequiredMoneyForCall() const
{
    return RequiredMoneyForCall;
}

const int32 ATHPlayerState::GetBettingMoney() const
{
    return BettingMoney;
}

const int32 ATHPlayerState::GetRoundBettingMoney() const
{
    return RoundBettingMoney;
}

const int32 ATHPlayerState::GetProfitMoney() const
{
    return ProfitMoney;
}

TArray<FPlayingCard> ATHPlayerState::GetHandCards() const
{
    return HandCards;
}

const EPlayerAction ATHPlayerState::GetPlayerAction() const
{
    return PlayerAction;
}

const bool ATHPlayerState::IsWinner() const
{
    return bIsWinner;
}

const FPlayerHandRankInfo ATHPlayerState::GetPlayerHandRankInfo() const
{
    return HandRankInfo;
}

void ATHPlayerState::SetReadyState(const bool& bInReady)
{
    bReady = bInReady;

    UE_LOG(LogTemp, Log, TEXT("[%s] ReadyState:%d Player::%s"), ANSI_TO_TCHAR(__FUNCTION__), bReady, *GetPlayerNickName());
}

void ATHPlayerState::SetTableSeattingPos(const int32& InTableSeattingPos)
{
    TableSeattingPos = InTableSeattingPos;

    UE_LOG(LogTemp, Log, TEXT("[%s] TableSeattingPos:%d Player::%s"), ANSI_TO_TCHAR(__FUNCTION__), TableSeattingPos, *GetPlayerNickName());
}

void ATHPlayerState::SetPlayerTurnState(const EPlayerTurnState& InPlayerTurnState)
{
    PlayerTurnState = InPlayerTurnState;

    UE_LOG(LogTemp, Log, TEXT("[%s] TurnState(%s) Player::%s"), 
        ANSI_TO_TCHAR(__FUNCTION__), *UTHGameDebugManager::GetEnumAsString(PlayerTurnState), *GetPlayerNickName());
}

void ATHPlayerState::SetPlayerNickName(const FString& InPlayerNickName)
{
    PlayerNickName = InPlayerNickName;

    UE_LOG(LogTemp, Log, TEXT("[%s] PlayerNickName(%s) Player::%s"), ANSI_TO_TCHAR(__FUNCTION__), *PlayerNickName, *GetPlayerNickName());
}

void ATHPlayerState::SetPlayerRole(const EPlayerRole& InPlayerRole)
{
    PlayerRole = InPlayerRole;

    UE_LOG(LogTemp, Log, TEXT("[%s] PlayerRole(%s) Player::%s"), ANSI_TO_TCHAR(__FUNCTION__), *UTHGameDebugManager::GetEnumAsString(PlayerRole), *GetPlayerNickName());
}

void ATHPlayerState::SetMoney(const int32& InMoney)
{
    int32 OldMoney = Money;
    Money = InMoney;

    UE_LOG(LogTemp, Log, TEXT("[%s] Old(%d) New(%d) Diff(%d) Player::%s"), ANSI_TO_TCHAR(__FUNCTION__), OldMoney, Money, Money - OldMoney, *GetPlayerNickName());
}

void ATHPlayerState::AddMoney(const int32& InMoney)
{
    SetMoney(Money + InMoney);
}

void ATHPlayerState::SetRequiredMoneyForCall(const int32& InRequiredMoneyForCall)
{
    RequiredMoneyForCall = InRequiredMoneyForCall;
}

void ATHPlayerState::SetBettingMoney(const int32& InBettingMoney)
{
    int32 OldBettingMoney = BettingMoney;
    BettingMoney = InBettingMoney;

    UE_LOG(LogTemp, Log, TEXT("[%s] Old(%d) New(%d) Diff(%d) Player::%s"), ANSI_TO_TCHAR(__FUNCTION__),
        OldBettingMoney, BettingMoney, BettingMoney - OldBettingMoney, *GetPlayerNickName());
}

void ATHPlayerState::AddBettingMoney(const int32& InBettingMoney)
{
    SetBettingMoney(BettingMoney + InBettingMoney);
    AddMoney(-InBettingMoney);
}

void ATHPlayerState::SetRoundBettingMoney(const int32& InRoundBettingMoney)
{
    int32 OldRoundBettingMoney = RoundBettingMoney;
    RoundBettingMoney = InRoundBettingMoney;

    UE_LOG(LogTemp, Log, TEXT("[%s] Old(%d) New(%d) Diff(%d) Player::%s"), ANSI_TO_TCHAR(__FUNCTION__),
        OldRoundBettingMoney, RoundBettingMoney, RoundBettingMoney - OldRoundBettingMoney, *GetPlayerNickName());
}

void ATHPlayerState::AddRoundBettingMoney(const int32& InRoundBettingMoney)
{
    SetRoundBettingMoney(RoundBettingMoney + InRoundBettingMoney);
    AddBettingMoney(InRoundBettingMoney);
}

void ATHPlayerState::SetProfitMoney(const int32& InProfitMoney)
{
    int32 OldRewardMoney = ProfitMoney;
    ProfitMoney = InProfitMoney;

    UE_LOG(LogTemp, Log, TEXT("[%s] Old(%d) New(%d) Diff(%d) Player::%s"), ANSI_TO_TCHAR(__FUNCTION__),
        OldRewardMoney, ProfitMoney, ProfitMoney - OldRewardMoney, *GetPlayerNickName());
}

void ATHPlayerState::AddProfitMoney(const int32& InProfitMoney)
{
    SetProfitMoney(ProfitMoney + InProfitMoney);
    AddMoney(-InProfitMoney);
}

void ATHPlayerState::SetPlayerAction(const EPlayerAction& InPlayerAction)
{
    PlayerAction = InPlayerAction;

    UE_LOG(LogTemp, Log, TEXT("[%s] PlayerAction(%s) Player::%s"), ANSI_TO_TCHAR(__FUNCTION__),
        *UTHGameDebugManager::GetEnumAsString(PlayerAction), *GetPlayerNickName());
}

void ATHPlayerState::SetIsWinner(const bool& bInIsWinner)
{
    bIsWinner = bInIsWinner;
}

void ATHPlayerState::SetPlayerHandRankInfo(const FPlayerHandRankInfo InHandRankInfo)
{
    HandRankInfo = InHandRankInfo;
}

void ATHPlayerState::SetHandCards(const TArray<FPlayingCard>& InHandCards)
{
    HandCards = InHandCards;

    UE_LOG(LogTemp, Log, TEXT("[%s] HandCards(%s, %s), (%s, %s) Player::%s"),
        ANSI_TO_TCHAR(__FUNCTION__),
        *UTHGameDebugManager::GetEnumAsString(HandCards[0].Suit),
        *UTHGameDebugManager::GetEnumAsString(HandCards[0].Value),
        *UTHGameDebugManager::GetEnumAsString(HandCards[1].Suit),
        *UTHGameDebugManager::GetEnumAsString(HandCards[1].Value),
        *GetPlayerNickName());
}

void ATHPlayerState::OnRep_HandCards()
{    
    UE_LOG(LogTemp, Log, TEXT("[%s] IsServer(%d) HandCards(%s, %s), (%s, %s) Player::%s"),
        ANSI_TO_TCHAR(__FUNCTION__),
        HasAuthority(),
        *UTHGameDebugManager::GetEnumAsString(HandCards[0].Suit),
        *UTHGameDebugManager::GetEnumAsString(HandCards[0].Value),
        *UTHGameDebugManager::GetEnumAsString(HandCards[1].Suit),
        *UTHGameDebugManager::GetEnumAsString(HandCards[1].Value),
        *GetPlayerNickName());
}