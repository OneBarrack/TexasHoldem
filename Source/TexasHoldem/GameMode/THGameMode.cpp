// Fill out your copyright notice in the Description page of Project Settings.


#include "THGameMode.h"
#include "GameState/THGameState.h"
#include "PlayerState/THPlayerState.h"
#include "Player/THPlayer.h"
#include "Controller/THPlayerController.h"
#include "Manager/THGameDebugManager.h"
#include "Algo/MaxElement.h"
#include "Kismet/KismetMathLibrary.h"

ATHGameMode::ATHGameMode()
{
    DefaultPawnClass = ATHPlayer::StaticClass();
    PlayerControllerClass = ATHPlayerController::StaticClass();
    GameStateClass = ATHGameState::StaticClass();
    PlayerStateClass = ATHPlayerState::StaticClass();
}

void ATHGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    THGameState = Cast<ATHGameState>(GameState);
}

void ATHGameMode::PostLogin(APlayerController* NewPlayer)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Begin"), ANSI_TO_TCHAR(__FUNCTION__));
    Super::PostLogin(NewPlayer);
    
    if (ATHPlayerController* LoginPlayerController = Cast<ATHPlayerController>(NewPlayer))
    {
        AddPlayerInHoldemTable(LoginPlayerController);
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::Logout(AController* Exiting)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Begin"), ANSI_TO_TCHAR(__FUNCTION__));
    Super::Logout(Exiting);

    if (ATHPlayerController* LogoutPlayerController = Cast<ATHPlayerController>(Exiting))
    {
        RemovePlayerInHoldemTable(LogoutPlayerController);
        if (ATHPlayerState* LogoutPlayerState = Cast<ATHPlayerState>(LogoutPlayerController))
        {
            THGameState->RemovePlayerInGamePlayers(LogoutPlayerState);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::BeginPlay()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));
    Super::BeginPlay();

    GamePlayManager = NewObject<UTHHoldemPlayManager>(this);    

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::StartPlay()
{
    Super::StartPlay();
        
    THGameState->SetBlindBettingMoney(FirstBlindBettingMoney);

    RestartTexasHoldem();

    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::Init()
{
    bIsOneOnOneMatch = false;
    bIsBettingRoundEnded = false;
    WinnerPlayers.Empty();

    TArray<ATHPlayerState*> PlayersForTable = THGameState->GetPlayersForTable();
    for (ATHPlayerState* THPlayerState : PlayersForTable)
    {
        if (THPlayerState)
        {
            THPlayerState->Init();
        }
    }

    THGameState->Init();
    GamePlayManager->Init();
}

void ATHGameMode::RestartTexasHoldem()
{
    UE_LOG(LogTemp, Log, TEXT("[%s]"), ANSI_TO_TCHAR(__FUNCTION__));
    // ���� �ʱ�ȭ �� ��ŸƮ
    Init();

    SetGamePlayState(EGamePlayState::Prepare);
}

void ATHGameMode::RunPlayCycle()
{
    switch (THGameState->GetGamePlayState())
    {
    case EGamePlayState::Prepare:  RunPlayCyclePrepare();  break;
    case EGamePlayState::StartUp:  RunPlayCycleStartUp();  break;
    case EGamePlayState::PreFlop:  RunPlayCyclePreFlop();  break;
    case EGamePlayState::Flop:     RunPlayCycleFlop();     break;
    case EGamePlayState::Turn:     RunPlayCycleTurn();     break;
    case EGamePlayState::River:    RunPlayCycleRiver();    break;
    case EGamePlayState::Showdown: RunPlayCycleShowdown(); break;
    case EGamePlayState::FinishUp: RunPlayCycleFinishUp(); break;
    case EGamePlayState::Betting:  RunPlayCycleBetting();  break;
    default: 
        break;
    }    
}

void ATHGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    RunPlayCycle();
}

void ATHGameMode::RunPlayCyclePrepare()
{
    // �غ���� : ��� ���� �Ͽ����� üũ
    if (IsReadyForAllPlayers())
    {
        SetGamePlayState(EGamePlayState::StartUp);
    }
}

/**
* StartUp
* 
1. ���� Ƚ�� ����
2. ����ε� ��ŸƮ ���øӴ� ����
3. ���������� ��ŸƮ �������� �÷��̾� ���� ��ġ�� ����Ʈ ����
4. ����� ���� ������ ����
5. 1,2,3 ������ Dealer, Small blind, Big blind ���� (�θ��̸� Dealer = Big Blind)
*/
void ATHGameMode::RunPlayCycleStartUp()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� Ƚ�� ����
    THGameState->IncreaseGamePlayCount();
    
    // 2. ��ŸƮ ���øӴ� ���� (10���� ������ ����)
    if (THGameState->GetGamePlayCount() % 10 == 0)
    {
        int32 BlindBettingMoney = static_cast<int32>((THGameState->GetBlindBettingMoney() * IncreaseRateForBlindBettingMoney));
        THGameState->SetBlindBettingMoney(BlindBettingMoney);        
    }
    
    // 3. ���� ������ ��ŸƮ ������������ �������� ���� ����� �÷��̾ ã��,
    //    �ش� �÷��̾ ��ŸƮ�� �ΰ��� �÷��̾� ���� ��ġ �� ���� ����� ���������� ����
    // 4. PlayerRole ����. ù ����(����������) ���� ���������� Dealer, Small blind, Big blind ����
    ExtractOrderedInGamePlayers();

    // 5. PreFlop ���� ����
    SetGamePlayState(EGamePlayState::PreFlop);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
* PreFlop
*
1. PreFlop ���� ���� ����
2. ��� �÷��̾ �ڵ�ī�� ����
3. Small blind, Big blind�� �ݾ� ���� 
4. SmallBlind�� BigBlind�� ���� �� ����(BigBlind ���� ������� ������ �����Ѵ�)
5. ù ���ö��忡���� ����ε� ������ ������� ġ�Ƿ� ���� �÷��̾���� üũ�� �� ����. 
6. BigBlind ���� ��ġ�� �÷��̾ �� �ο�
7. ���� ����
*/
void ATHGameMode::RunPlayCyclePreFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� �ʱ�ȭ
    InitBettingRound();

    TArray<ATHPlayerState*> InGameSurvivedPlayers = THGameState->GetInGameSurvivedPlayers();

    // 1. PreFlop ���ö��� ����
    THGameState->SetBettingRound(EBettingRound::PreFlop);
    
    for (ATHPlayerState* THPlayerState : InGameSurvivedPlayers)
    {
        // 2. ī����̿��� ī�� �� ���� �̾� �÷��̾� �ڵ�ī�� ���� �� ����
        TArray<FPlayingCard> HandCards;
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());

        THPlayerState->SetHandCards(HandCards);
    }

    // Get Small blind player, Big blind player
    ATHPlayerState* SmallBlindPlayer = THGameState->GetPlayerForPlayerRole(EPlayerRole::SmallBlind);
    ATHPlayerState* BigBlindPlayer   = THGameState->GetPlayerForPlayerRole(EPlayerRole::BigBlind);
    check(SmallBlindPlayer && BigBlindPlayer);

    // 3. Small blind, Big blind�� ��ŸƮ ���ñݾ� ����
    int32 BlindBettingMoney = THGameState->GetBlindBettingMoney();

    // 4. ���� ���ö��忡���� SmallBlind�� BigBlind�� ����ε� ���� �ݾ��� �̸� �ø���
    //    BigBlind�� ���� �̸� �����Ų��
    SmallBlindPlayer->AddRoundBettingMoney(BlindBettingMoney / 2);
    BigBlindPlayer->AddRoundBettingMoney(BlindBettingMoney);
    BigBlindPlayer->SetPlayerTurnState(EPlayerTurnState::Done);

    // ���̺� ���øӴ� ����
    THGameState->SetHighRoundBettingMoney(BlindBettingMoney);
    THGameState->AddTotalPotMoney(SmallBlindPlayer->GetBettingMoney() + BigBlindPlayer->GetBettingMoney());

    // 5. ù ���ö��忡���� ����ε� ������ ������� ġ�Ƿ� ���� �÷��̾���� üũ�� �� ����.
    THGameState->SetAppeardRaiseAction(true);

    // 6. BigBlind ���� ��ġ�� �÷��̾ �� �ο�
    int32 BigBlindPlayerIndex = InGameSurvivedPlayers.Find(BigBlindPlayer);
    ATHPlayerState* PlayerNextToBigBlind = InGameSurvivedPlayers[(BigBlindPlayerIndex + 1) % InGameSurvivedPlayers.Num()];    
    GiveTurnToPlayer(PlayerNextToBigBlind);

    // 7. ���� ����    
    SetGamePlayState(EGamePlayState::Betting);    

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Flop
 *
 1. ���� �ʱ�ȭ
 2. ���ö��� ����
 3. ����ī�� ���� �� ���ӽ��������� ����
 4. ��ŸƮ �÷��̾ �� �ο�
 5. ���� ����
 */
void ATHGameMode::RunPlayCycleFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� �ʱ�ȭ
    InitBettingRound();

    // 2. ���ö��� ���� 
    GamePlayManager->SetBettingRound(EBettingRound::Flop);    
    THGameState->SetBettingRound(EBettingRound::Flop);
    
    // 3. ����ī�� ���� �� ���ӽ�����Ʈ�� ����
    GamePlayManager->AddCardToCommunityCards();
    THGameState->SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 4. ��ŸƮ �÷��̾ �� �ο�    
    GiveTurnToPlayer(THGameState->GetInGameSurvivedPlayers()[0]);

    // 5. ���� ����    
    SetGamePlayState(EGamePlayState::Betting);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Turn
 *
 1. ���� �ʱ�ȭ
 2. ���ö��� ����
 3. ����ī�� ���� �� ���ӽ��������� ����
 4. ��ŸƮ �÷��̾ �� �ο�
 5. ���� ����
 */
void ATHGameMode::RunPlayCycleTurn()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� �ʱ�ȭ
    InitBettingRound();

    // 2. ���ö��� ���� 
    GamePlayManager->SetBettingRound(EBettingRound::Turn);
    THGameState->SetBettingRound(EBettingRound::Turn);

    // 3. ����ī�� ���� �� ���ӽ�����Ʈ�� ����
    GamePlayManager->AddCardToCommunityCards();
    THGameState->SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 4. ��ŸƮ �÷��̾ �� �ο�    
    GiveTurnToPlayer(THGameState->GetInGameSurvivedPlayers()[0]);

    // 5. ���� ����
    SetGamePlayState(EGamePlayState::Betting);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * River
 *
 1. ���� �ʱ�ȭ
 2. ���ö��� ����
 3. ����ī�� ���� �� ���ӽ��������� ����
 4. ��ŸƮ �÷��̾ �� �ο�
 5. ���� ����
 */
void ATHGameMode::RunPlayCycleRiver()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� �ʱ�ȭ
    InitBettingRound();

    // 2. ���ö��� ���� 
    GamePlayManager->SetBettingRound(EBettingRound::River);
    THGameState->SetBettingRound(EBettingRound::River);

    // 3. ����ī�� ���� �� ���ӽ�����Ʈ�� ����
    GamePlayManager->AddCardToCommunityCards();
    THGameState->SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 4. ��ŸƮ �÷��̾ �� �ο�    
    GiveTurnToPlayer(THGameState->GetInGameSurvivedPlayers()[0]);

    // 5. ���� ����
    SetGamePlayState(EGamePlayState::Betting);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::RunPlayCycleShowdown()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // ������� ���� �ʿ�
    WinnerPlayers = ExtractWinners();
        
    // ����
    FTimerDelegate ShowdownDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::FinishUp);
    GetWorldTimerManager().SetTimer(ShowdownTimerHandle, ShowdownDelegate, 10.0f/*ShowdownTimerDelay*/, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::RunPlayCycleFinishUp()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    for (ATHPlayerState* WinnerPlayer : WinnerPlayers)
    {
        WinnerPlayer->AddMoney(WinnerPlayer->GetRewardMoney());
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
    RestartTexasHoldem();
}

/*
* Betting
*
1. ���ö��� ���� �÷���(bIsBettingRoundEnded) üũ
2. �÷��̾ ȥ�� ����(RemainBettingPlayerCount = 1) ��Ȳ�̸� �¸� �÷��̾�� ���� ����   
3. �ƴ϶�� �������� ����
*/
void ATHGameMode::RunPlayCycleBetting()
{   
    TArray<ATHPlayerState*> InGameSurvivedPlayers = THGameState->GetInGameSurvivedPlayers();
    
    // �÷��̾ ȥ�� ���� ���¶�� 
    if (InGameSurvivedPlayers.Num() == 1)
    {
        // �ش� �÷��̾� �¸� �� ��������
        WinnerPlayers.Add(THGameState->GetCurrentTurnPlayer());
    }
    // ������ ��� �����ٸ�
    else if (bIsBettingRoundEnded)
    {
        // �������� ����
        switch (EBettingRound BettingRound = THGameState->GetBettingRound())
        {
        case EBettingRound::PreFlop: SetGamePlayState(EGamePlayState::Flop);     break;
        case EBettingRound::Flop:    SetGamePlayState(EGamePlayState::Turn);     break;
        case EBettingRound::Turn:    SetGamePlayState(EGamePlayState::River);    break;
        case EBettingRound::River:   SetGamePlayState(EGamePlayState::Showdown); break;
        }
    }
}

void ATHGameMode::GiveTurnToPlayer(ATHPlayerState* BettingPlayer)
{
    BettingPlayer->SetPlayerTurnState(EPlayerTurnState::InProgress);
    BettingPlayer->GetPlayerController()->CheckForActionActivate();
    THGameState->SetCurrentTurnPlayer(BettingPlayer);
    THGameState->SetCallMoneyForCurrentPlayer(BettingPlayer->GetRequiredMoneyForCall());    
}

void ATHGameMode::ReceiveNotifyPlayerAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney)
{
    if (!IsValid(BettingPlayer))
        return;

    switch (BettingPlayer->GetPlayerAction())
    {
    case EPlayerAction::Quarter: [[fallthrough]];
    case EPlayerAction::Half:    [[fallthrough]];
    case EPlayerAction::Full:    [[fallthrough]];
    case EPlayerAction::Raise:
    {
        // ���ö��� �ʱ�ȭ(��� �÷��̾��� �׼� ���� �� �� Wait ���·� �����) ��
        // ���� �÷��̾ ������׼� ����, GameState �� Raise �׼� true ����
        InitBettingRound(true);
        THGameState->SetAppeardRaiseAction(true);
        CalcPotMoneyForRaiseAction(BettingPlayer, CallMoney, RaiseMoney);
        break;
    }
    case EPlayerAction::Allin:
    {
        // ������Ӵϰ� �����ϸ� �������� ������ �� ���̹Ƿ� ������ ���� ����
        if (RaiseMoney > 0)
        {
            InitBettingRound(true);
            THGameState->SetAppeardRaiseAction(true);
            CalcPotMoneyForRaiseAction(BettingPlayer, CallMoney, RaiseMoney);
        }
        // ������Ӵϰ� ���ٸ� ���� �÷��̾���� ���ñݾ׿� ���� �� �������� �����ݾ� ��θ� ������ ���̹Ƿ� �� ���� ����
        else
        {
            CalcPotMoneyForCallAction(BettingPlayer, CallMoney);
        }
        break;
    }
    case EPlayerAction::Check:
    {
        CalcPotMoneyForCheckAction(BettingPlayer);
        break;
    }
    case EPlayerAction::Call:
    {
        CalcPotMoneyForCallAction(BettingPlayer, CallMoney);
        break;
    }
    case EPlayerAction::Fold:
    {
        CalcPotMoneyForFoldAction(BettingPlayer);

        // ���� ���� �÷��̾� �� ����
        THGameState->RemovePlayerInGamePlayers(BettingPlayer);
        break;
    }
    default:
        break;
    }

    if (THGameState->GetLogInGamePlayerCount() > 1)
    {        
        // ���� �÷��̾� ���� ���� 
        ATHPlayerState* NextBettingPlayer = THGameState->GetNextInGamePlayer(BettingPlayer);

        // ���� �÷��̾��� Betting State�� Done���� üũ
        if (NextBettingPlayer->GetPlayerTurnState() == EPlayerTurnState::Done)
        {
            // �߰����� Raise ���� �ѹ��� �� �����̹Ƿ� �� ����
            bIsBettingRoundEnded = true;
        }
        else
        {
            // �� �ο�
            GiveTurnToPlayer(NextBettingPlayer);
        }
    }

    // ���� �÷��̾� �� ����
    BettingPlayer->SetPlayerTurnState(EPlayerTurnState::Done);

    UE_LOG(LogTemp, Log, TEXT("[%s] Action:%s Player:%s"), 
        ANSI_TO_TCHAR(__FUNCTION__),
        *UTHGameDebugManager::GetEnumAsString(BettingPlayer->GetPlayerAction()),
        *BettingPlayer->GetPlayerNickName());
}

void ATHGameMode::CalcPotMoneyForCheckAction(ATHPlayerState* BettingPlayer)
{
}

void ATHGameMode::CalcPotMoneyForCallAction(ATHPlayerState* BettingPlayer, const int32 CallMoney)
{
    BettingPlayer->AddRoundBettingMoney(CallMoney);
    THGameState->AddTotalPotMoney(CallMoney);
}

void ATHGameMode::CalcPotMoneyForRaiseAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney)
{
    BettingPlayer->AddRoundBettingMoney(CallMoney + RaiseMoney);
    THGameState->SetHighRoundBettingMoney(BettingPlayer->GetRoundBettingMoney());
    THGameState->AddTotalPotMoney(CallMoney + RaiseMoney);
    THGameState->SetMinRaiseMoney(RaiseMoney);
}

void ATHGameMode::CalcPotMoneyForFoldAction(ATHPlayerState* BettingPlayer)
{
}

void ATHGameMode::InitBettingRound(bool bNotifyRaiseAction)
{
    InitSurvivedPlayersForBettingRound(bNotifyRaiseAction);

    if (!bNotifyRaiseAction)
    {
        THGameState->SetHighRoundBettingMoney(THGameState->GetBlindBettingMoney());
    }

    bIsBettingRoundEnded = false;
    THGameState->SetAppeardRaiseAction(false);
    THGameState->SetMinRaiseMoney(THGameState->GetBlindBettingMoney());    
}

void ATHGameMode::InitSurvivedPlayersForBettingRound(bool bNotifyRaiseAction)
{
    TArray<ATHPlayerState*> InGameSurvivedPlayers = THGameState->GetInGameSurvivedPlayers();
    for (ATHPlayerState* THPlayerState : InGameSurvivedPlayers)
    {
        // ������ �÷��̾�� ���� ������� �߰����� �׼� �� �Ͽ� ���� ������Ʈ�� ���� �ʴ´�.
        if (THPlayerState->GetPlayerAction() != EPlayerAction::Allin)
        {
            THPlayerState->SetPlayerTurnState(EPlayerTurnState::Wait);
            THPlayerState->SetPlayerAction(EPlayerAction::None);
        }

        if (!bNotifyRaiseAction)
        {
            THPlayerState->SetRoundBettingMoney(0);
        }
    }
}

// PlayerRole ����. ������ ù ����(Small Blind) ���� �ð�������� ���������� Role ����
void ATHGameMode::ExtractOrderedInGamePlayers()
{
    bIsOneOnOneMatch = false;
    TArray<ATHPlayerState*> InGamePlayers;

    // ���̺� �� ��ġ�� �÷��̾� ����
    TArray<ATHPlayerState*> PlayersForTable = THGameState->GetPlayersForTable();
    
    // ���� Dealer Position ����
    int32 PrevDealerPos = -1;
    if (ATHPlayerState* DealerPlayer = THGameState->GetPlayerForPlayerRole(EPlayerRole::Dealer))
    {
        PrevDealerPos = PlayersForTable.Find(DealerPlayer);
    }
    
    // ���� Dealer Position�� �ð�������� ���� �÷��̾ �̹� ������ �ȴ�. 
    // ��ȸ Ž���Ͽ� �÷��̾� ������Ʈ ������ ���� �� ���������� ��ȯ
    int32 CurDealerPos = (PrevDealerPos + 1) % MaxPlayerCount;
    int32 PlayerTablePos = CurDealerPos;
    do 
    {
        if (ATHPlayerState* TargetPlayer = PlayersForTable[PlayerTablePos])
        {
            InGamePlayers.Add(TargetPlayer);
        }
        PlayerTablePos = (PlayerTablePos + 1) % MaxPlayerCount;
    } while (PlayerTablePos != CurDealerPos);

    // ����� �÷��̾ ���� ���������� Dealer, SmallBlind, BigBlind Role �ο�
    EPlayerRole PlayerRole = EPlayerRole::Dealer;
    for (int32 InGamePlayerPos = 0; InGamePlayerPos < MaxRoleCount; ++InGamePlayerPos)
    {
        ATHPlayerState* TargetPlayer = InGamePlayers[InGamePlayerPos % InGamePlayers.Num()];
        SetPlayerForPlayerRole(TargetPlayer, PlayerRole);

        PlayerRole = static_cast<EPlayerRole>(static_cast<int32>(PlayerRole) + 1);
    }

    // SmallBlind�� ù��° ������ �ǵ��� �ε��� 0 �÷��̾�(Dealer(2���� �� BigBlind)) �������� ���� ���������� �־��ش�.
    ATHPlayerState* DealerPlayer = InGamePlayers[0];
    InGamePlayers.Add(DealerPlayer);
    InGamePlayers.RemoveAt(0);

    THGameState->SetInGamePlayersAll(InGamePlayers);
    THGameState->SetInGameSurvivedPlayers(InGamePlayers);
}

void ATHGameMode::SetPlayerForPlayerRole(ATHPlayerState* TargetPlayer, EPlayerRole& PlayerRole)
{
    TargetPlayer->SetPlayerRole(PlayerRole);
    THGameState->SetPlayerForPlayerRole(TargetPlayer, PlayerRole);
}

TArray<ATHPlayerState*> ATHGameMode::ExtractWinners()
{
    // �� ���� (Key:HandRank, Value:PlayerState)
    TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>> PlayersForHandRankInfo;

    // ���� �÷��̾���� �ڵ巩ũ ���� �����ϸ� �ʿ� �߰�
    for (ATHPlayerState* InGameSurvivedPlayer : THGameState->GetInGameSurvivedPlayers())
    {
        TArray<FPlayingCard> HandCards = InGameSurvivedPlayer->GetHandCards();
        FPlayerHandRankInfo HandRankInfo = GamePlayManager->GetHandRankInfo(HandCards);
        InGameSurvivedPlayer->SetPlayerHandRankInfo(HandRankInfo);
        
        if (!PlayersForHandRankInfo.Contains(HandRankInfo))
        {
            PlayersForHandRankInfo.Add(HandRankInfo);
        }
        PlayersForHandRankInfo[HandRankInfo].Add(InGameSurvivedPlayer);
    }
    
    // �ڵ巩ũ�� ���� ������ �������� ����
    PlayersForHandRankInfo.KeySort([](const FPlayerHandRankInfo& HandRankInfoA, const FPlayerHandRankInfo& HandRankInfoB) {
        return HandRankInfoA > HandRankInfoB;
    });

    // �� �Ӵ� ��� ����
    CalculatePotMoney(PlayersForHandRankInfo);

    // ���ĵ� �÷��̾� �ڵ巩ũ ���� ù��° Value ����(�ڵ巩ũ�� ���� ���� Winner Player List)
    return PlayersForHandRankInfo.CreateConstIterator()->Value;
}

void ATHGameMode::CalculatePotMoney(TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>>& PlayersForHandRankInfo)
{
    // ���� �ڵ巩ũ�� �ش��ϴ� �÷��̾������ ���ñݾ� ��ŭ ��ü �̿��� ������ �������� �Ѵ�.
    int32 PrevMaxBettingMoney = 0;
    int32 RemainTotalPot = THGameState->GetTotalPotMoney();
    for (const auto& PlayerForHandRankInfo : PlayersForHandRankInfo)
    {
        FPlayerHandRankInfo HandRankInfo = PlayerForHandRankInfo.Key;
        TArray<ATHPlayerState*> PotPlayers = PlayerForHandRankInfo.Value;

        // ����(�� ���� �ڵ巩ũ) �� �÷��̾��� ���ñݾװ� ���ų� ���ٸ� ������ �ݾ��� ���� ������ �ɷ�����.
        PotPlayers = PotPlayers.FilterByPredicate([&PrevMaxBettingMoney](const ATHPlayerState* PotPlayer) {
            return PotPlayer->GetBettingMoney() > PrevMaxBettingMoney;
            });

        // �� �Ӵϸ� ȹ���� �÷��̾ ���ٸ� Continue
        if (PotPlayers.Num() == 0)
        {
            continue;
        }

        // �� �Ӵϸ� ȹ���� �÷��̾ 1�� �̶��
        if (PotPlayers.Num() == 1)
        {
            CalculatePotMoneySingle(PotPlayers, PrevMaxBettingMoney, RemainTotalPot);
        }
        // �� �÷��̾ �� �̻��̶�� �ش� �÷��̾���� ���º��̹Ƿ� Chop(Split) ��Ȳ�̴�.
        else
        {
            CalculatePotMoneyChop(PotPlayers, PrevMaxBettingMoney, RemainTotalPot);
        }

        // �� �й� �Ϸ�
        if (RemainTotalPot == 0)
        {
            break;
        }
    }
}

void ATHGameMode::CalculatePotMoneySingle(TArray<ATHPlayerState*>& PotPlayers, int32& PrevMaxBettingMoney, int32& RemainTotalPot)
{
    ATHPlayerState* PotPlayer = PotPlayers[0];

    // ����(�� ���� �ڵ巩ũ) �� �÷��̾ ������ �ݾ��� ���ܽ�Ų ���ñݾ�.
    int32 PotPlayerBettingMoney = PotPlayer->GetBettingMoney() - PrevMaxBettingMoney;

    // ��ü �÷��̾���� ���ñݾ׿��� �� �÷��̾��� ���ñݾ׸�ŭ ������.
    int32 RewardMoney = 0;
    for (ATHPlayerState* RemainBettingPlayer : THGameState->GetInGamePlayersAll())
    {
        int32 RemainPlayerBettingMoney = RemainBettingPlayer->GetBettingMoney();

        // �ٸ� �÷��̾��� ���ñݾ��� ���ų� �Ҹ�Ǿ� �ִٸ� �ǳʶڴ�
        if (RemainPlayerBettingMoney == 0)
        {
            continue;
        }

        // �� �÷��̾��� ���ñݾ׿� ���� ����ݾ� ȹ��
        if (PotPlayerBettingMoney < RemainPlayerBettingMoney)
        {
            RewardMoney += PotPlayerBettingMoney;
            RemainPlayerBettingMoney -= PotPlayerBettingMoney;
        }
        else
        {
            RewardMoney += RemainPlayerBettingMoney;
            RemainPlayerBettingMoney = 0;
        }

        // BettingPlayer�� ���øӴϴ� Pot �÷��̾�� ���ñݾ��� ����� �������� ����
        RemainBettingPlayer->SetBettingMoney(RemainPlayerBettingMoney);
    }

    // ���� ����ݾ׸�ŭ ���� �� �Ӵ� ����
    RemainTotalPot -= RewardMoney;

    // �� �Ӵϸ� ȹ���� �÷��̾��� ����ݾ� ����
    PotPlayer->SetRewardMoney(RewardMoney);

    // �� �Ӵϸ� ȹ���� �÷��̾��� ���øӴ� ����
    PrevMaxBettingMoney = PotPlayerBettingMoney;
}

void ATHGameMode::CalculatePotMoneyChop(TArray<ATHPlayerState*>& PotPlayers, int32& PrevMaxBettingMoney, int32& RemainTotalPot)
{
    // �������� 0, ��ü ���鼭 ���������� �ش緩ũ�� �ִ� ���� ���� �� �ݾ����� �����ϸ鼭 ���̵��� ����. 
    // �ڿ����� �� �÷��̾���� ����ݾ� ���õǵ���.

    // ���º� �÷��̾� �� ���� ū ���ñݾ��� �������� ��ü �̿��� ����ݾ��� ������, 
    // ���� �ӴϿ��� ���º� �÷��̾���� ���ñݾ� ������ŭ ������ �й��Ѵ�.

    // ���ñݾ� ������ �������� ����
    PotPlayers.Sort([](const ATHPlayerState& PotPlayerA, const ATHPlayerState& PotPlayerB) {
        return PotPlayerA.GetBettingMoney() < PotPlayerB.GetBettingMoney();
    });

    // ���º� �÷��̾���� ����ݾ� ���
    int32 PrevRewardMoney = 0;
    for (int32 PotPlayerIndex = 0; PotPlayerIndex < PotPlayers.Num(); ++PotPlayerIndex)
    {
        ATHPlayerState* PotPlayer = PotPlayers[PotPlayerIndex];

        // ����(�� ���� �ڵ巩ũ) �� �÷��̾ ������ �ݾ��� ���ܽ�Ų ���ñݾ�.
        int32 PotPlayerBettingMoney = PotPlayer->GetBettingMoney() - PrevMaxBettingMoney;

        // ��ü �÷��̾���� ���ñݾ׿��� �� �÷��̾��� ���ñݾ׸�ŭ ������.
        int32 RewardMoney = 0;
        for (ATHPlayerState* RemainBettingPlayer : THGameState->GetInGamePlayersAll())
        {
            int32 RemainPlayerBettingMoney = RemainBettingPlayer->GetBettingMoney();

            // �ٸ� �÷��̾��� ���ñݾ��� ���ų� �Ҹ�Ǿ� �ִٸ� �ǳʶڴ�
            if (RemainPlayerBettingMoney == 0)
            {
                continue;
            }

            // �� �÷��̾��� ���ñݾ׿� ���� ����ݾ� ȹ��
            if (PotPlayerBettingMoney < RemainPlayerBettingMoney)
            {
                RewardMoney += PotPlayerBettingMoney;
                RemainPlayerBettingMoney -= PotPlayerBettingMoney;
            }
            else
            {
                RewardMoney += RemainPlayerBettingMoney;
                RemainPlayerBettingMoney = 0;
            }

            // BettingPlayer�� ���øӴϴ� Pot �÷��̾�� ���ñݾ��� ����� �������� ����
            RemainBettingPlayer->SetBettingMoney(RemainPlayerBettingMoney);
        }

        // ���� ����ݾ׸�ŭ ���� �� �Ӵ� ����
        RemainTotalPot -= RewardMoney;

        // ���º� �÷��̾� �� ��ŭ ���ҵ� ����ݾ�
        int32 SplittedRewardMoney = RewardMoney / (PotPlayers.Num() - PotPlayerIndex);

        // �� �Ӵϸ� ȹ���� �÷��̾��� �ɰ��� ����ݾ� ����
        PotPlayer->SetRewardMoney(PrevRewardMoney + SplittedRewardMoney);
        PrevRewardMoney += SplittedRewardMoney;

        // �� �Ӵϸ� ȹ���� �÷��̾��� ���øӴ� ����
        PrevMaxBettingMoney = PotPlayerBettingMoney;
    }
}

bool ATHGameMode::IsReadyForAllPlayers()
{
    bool bReadyForAllPlayers = false;

    // ���� ���� �ּ� �ο�(MinPlayerCount) üũ
    if (THGameState->PlayerArray.Num() >= MinPlayerCount)
    {
        bReadyForAllPlayers = true;

        // �÷��̾ ��� ���� �Ͽ����� üũ
        for (APlayerState* InGamePlayer : THGameState->PlayerArray)
        {
            if (ATHPlayerState* THPlayerState = Cast<ATHPlayerState>(InGamePlayer))
            {
                // ���� ���� �÷��̾ �ִٸ� false ����
                if (!THPlayerState->IsReady())
                {
                    bReadyForAllPlayers = false;
                    break;
                }
            }
        }
    }

    return bReadyForAllPlayers;
}

void ATHGameMode::SetGamePlayState(EGamePlayState InGamePlayState)
{
    THGameState->SetGamePlayState(InGamePlayState);
}

void ATHGameMode::AddPlayerInHoldemTable(ATHPlayerController* LoginPlayerController)
{
    // Player Login�� ���� �غ�ܰ��� �ΰ��� �÷��̾� ����Ʈ�� �߰�
    if (THGameState->GetGamePlayState() == EGamePlayState::Prepare)
    {
        TArray<ATHPlayerState*> PlayersForTableSeattingPos = THGameState->GetPlayersForTable();

        // �÷��̾� �ڸ��� �����ϱ� ���� InGamePlayers ����Ʈ�� ��ȸ�ϸ鼭 �� �ڸ��� �߰�
        int32 TableSeattingPos = 0;
        for (ATHPlayerState*& THPlayerState : PlayersForTableSeattingPos)
        {
            if (!THPlayerState)
            {
                THPlayerState = LoginPlayerController->GetPlayerState();
                THPlayerState->SetTableSeattingPos(TableSeattingPos);

                UE_LOG(LogTemp, Log, TEXT("[%s] Login Player(%s) "), ANSI_TO_TCHAR(__FUNCTION__), *THPlayerState->GetName());

                // Debug
                if (THPlayerState->GetPlayerNickName() == FString(TEXT("Anonymous")))
                {
                    THPlayerState->SetPlayerNickName(FString::FromInt(THGameState->GetLoginUserCount()));
                }
                //THPlayerState->SetBettingMoney((THGameState->GetPlayerCount() + 1) * 1000);
                //THPlayerState->SetPlayerAction(static_cast<EPlayerAction>(THGameState->GetPlayerCount() % 5) );
                //THPlayerState->SetPlayerRole(static_cast<EPlayerRole>(THGameState->GetPlayerCount() % 4));
                //
                break;
            }

            ++TableSeattingPos;
        }

        // __Debug : Log ���
        //for (const ATHPlayerState* THPlayerState : PlayersForTableSeattingPos)
        //{
        //    if (THPlayerState)
        //    {
        //        UE_LOG(LogTemp, Log, TEXT("Player : %s"), *THPlayerState->GetName());
        //    }
        //    else
        //    {
        //        UE_LOG(LogTemp, Log, TEXT("Player : NONE"));
        //    }
        //}

        // GameState�� �ڸ��� �÷��̾� ���� ����
        THGameState->SetPlayersForTable(PlayersForTableSeattingPos);
    }
}

void ATHGameMode::RemovePlayerInHoldemTable(ATHPlayerController* LogoutPlayerController)
{
    // Player Logout�� �ΰ��� �÷��̾� ����Ʈ���� ����
    if (ATHPlayerState* LogoutPlayerState = LogoutPlayerController->GetPlayerState())
    {
        TArray<ATHPlayerState*> PlayersForTableSeattingPos = THGameState->GetPlayersForTable();

        // InGamePlayers ����Ʈ �� �ش� �÷��̾� �ڸ��� nullptr�� ����� �ڸ� ������ �����Ѵ�.
        if (PlayersForTableSeattingPos.Contains(LogoutPlayerState))
        {
            PlayersForTableSeattingPos[PlayersForTableSeattingPos.Find(LogoutPlayerState)] = nullptr;
            LogoutPlayerState->SetTableSeattingPos(-1);

            UE_LOG(LogTemp, Log, TEXT("[%s] Logout Player(%s)"), ANSI_TO_TCHAR(__FUNCTION__), *LogoutPlayerState->GetName());
        }

        // __Debug : Log ���
        //for (const ATHPlayerState* THPlayerController : PlayersForTableSeattingPos)
        //{
        //    if (THPlayerController)
        //    {
        //        UE_LOG(LogTemp, Log, TEXT("Player : %s"), *THPlayerController->GetName());
        //    }
        //    else
        //    {
        //        UE_LOG(LogTemp, Log, TEXT("Player : NONE"));
        //    }
        //}

        // GameState�� �ڸ��� �÷��̾� ���� ����
        THGameState->SetPlayersForTable(PlayersForTableSeattingPos);
    }
}
