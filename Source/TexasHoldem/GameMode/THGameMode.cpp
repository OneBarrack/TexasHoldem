// Fill out your copyright notice in the Description page of Project Settings.


#include "THGameMode.h"
#include "GameState/THGameState.h"
#include "PlayerState/THPlayerState.h"
#include "Player/THPlayer.h"
#include "Controller/THPlayerController.h"
#include "UI/THWidgetInGameUserStateSub.h"
#include "Manager/THGameDebugManager.h"
#include "Algo/MaxElement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameSession.h"

ATHGameMode::ATHGameMode()
{
    DefaultPawnClass = ATHPlayer::StaticClass();
    PlayerControllerClass = ATHPlayerController::StaticClass();
    GameStateClass = ATHGameState::StaticClass();
    PlayerStateClass = ATHPlayerState::StaticClass();

    // �ش� ��� ������ ���̺� Ž��
    ConstructorHelpers::FObjectFinder<UDataTable> UserInfoDataDataFinder(TEXT("DataTable'/Game/DataTable/UserInfo.UserInfo'"));

    if (UserInfoDataDataFinder.Succeeded())
    {
        UserInfoDataTable = UserInfoDataDataFinder.Object;
    }
}

void ATHGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    THGameState = Cast<ATHGameState>(GameState);
}

void ATHGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    APlayerController* PlayerController = GetPlayerControllerFromNetId(GetWorld(), *UniqueId);

    // �÷��̾ ���� �� �ִٸ� �α��� �ź�
    if (GetLoginPlayerCount() >= MaxPlayerCount)
    {
        ErrorMessage = FString("There are no empty seats in the table.");
    }
    
    UE_LOG(LogTemp, Log, TEXT("[%s] End. Options(%s) Address(%s) UniqueId(%s) ErrorMessage(%s)"), 
        ANSI_TO_TCHAR(__FUNCTION__), *Options, *Address, *UniqueId.ToString(), *ErrorMessage);
}

APlayerController* ATHGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{    
    return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
    UE_LOG(LogTemp, Log, TEXT("[%s] "), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::PostLogin(APlayerController* NewPlayer)
{    
    Super::PostLogin(NewPlayer);
    UE_LOG(LogTemp, Log, TEXT("[%s] Start. Player Count(%d)"), ANSI_TO_TCHAR(__FUNCTION__), GetLoginPlayerCount());

    if (ATHPlayerController* LoginPlayerController = Cast<ATHPlayerController>(NewPlayer))
    {
        // Ȧ�� ���̺� ����Ʈ�� �÷��̾� ���� ����
        AddPlayerInHoldemTable(LoginPlayerController);
    }
    
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    if (ATHPlayerController* LogoutPlayerController = Cast<ATHPlayerController>(Exiting))
    {
        // Ȧ�� ���̺� ����Ʈ���� �÷��̾� ���� ����
        RemovePlayerInHoldemTable(LogoutPlayerController);
    }    

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));
 
    /// <summary>
    //FName PlayerNickName = FName(TEXT("jw"));
    //if (UserInfoDataTable->GetRowNames().Contains(PlayerNickName))
    //{
    //    int aaaa = 5;
    //}
    //else
    //{
    //    FTHUserInfoTableRow TempRowBase;
    //    TempRowBase.Money = 1000;
    //    TempRowBase.RecentLoginDateTime = "2022-10-13 17:15";
    //    UserInfoDataTable->AddRow(PlayerNickName, TempRowBase);
    //}
    
    /// </summary>

    GamePlayManager = NewObject<UTHHoldemPlayManager>(this);
    SetBlindBettingMoney(FirstBlindBettingMoney);
    RestartTexasHoldem();

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::StartPlay()
{
    Super::StartPlay();
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::RestartTexasHoldem()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // ���� �ʱ�ȭ �� ��ŸƮ
    bIsOneOnOneMatch = false;
    bIsBettingRoundEnded = false;
    GamePlayManager->Init();

    // Broadcast restart delegate 
    THGameState->NotifyRestartGame();

    // Start �� �ʱ�ȭ ���ø�����Ʈ�� ���õǴ� ���� �����ϱ� ���� Prepare �� Start Ÿ���� �����ð� �����ϵ��� Ÿ�̸� ����
    FTimerDelegate CycleRestartDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::Prepare);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleRestartDelegate, 1.0f, false);
    
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    RunPlayCycle();
}

void ATHGameMode::RunPlayCycle()
{
    switch (GetGamePlayState())
    {
    case EGamePlayState::Prepare:        RunPlayCyclePrepare();  break;
    case EGamePlayState::StartUp:        RunPlayCycleStartUp();  break;
    case EGamePlayState::PreFlop:        RunPlayCyclePreFlop();  break;
    case EGamePlayState::Flop:           RunPlayCycleFlop();     break;
    case EGamePlayState::Turn:           RunPlayCycleTurn();     break;
    case EGamePlayState::River:          RunPlayCycleRiver();    break;
    case EGamePlayState::Showdown:       RunPlayCycleShowdown(); break;
    case EGamePlayState::FinishUp:       RunPlayCycleFinishUp(); break;
    case EGamePlayState::PreFlopBetting: [[fallthrough]];
    case EGamePlayState::FlopBetting:    [[fallthrough]];
    case EGamePlayState::TurnBetting:    [[fallthrough]];
    case EGamePlayState::RiverBetting:   RunPlayCycleBetting();  break;
    default:
        break;
    }
}

void ATHGameMode::RunPlayCyclePrepare()
{
    // 1�ʸ��� ���� ��ŸƮ�� �ʿ��� �÷��̾� ���� �����Ǵ��� üũ
    if (!GetWorldTimerManager().IsTimerActive(CycleTimerHandle))
    {
        FTimerDelegate CyclePrepareDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::CheckLoginPlayerCountForStartUp);
        GetWorldTimerManager().SetTimer(CycleTimerHandle, CyclePrepareDelegate, 1.0f, true);
    }
}

/**
* StartUp
* 
1. ���� Ƚ�� ����
2. ����ε� ��ŸƮ ���øӴ� ����
3. ���������� ��ŸƮ �������� �÷��̾� ���� ��ġ�� ����Ʈ ����
4. ����� ���� ������ ����
5. ����ī�� ���� �� ���ӽ�����Ʈ�� ����
6. ��� �÷��̾ �ڵ�ī�� ����
7. 1,2,3 ������ Dealer, Small blind, Big blind ���� (�θ��̸� Dealer = Big Blind)
*/
void ATHGameMode::RunPlayCycleStartUp()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� Ƚ�� ����
    IncreaseGamePlayCount();
    
    // 2. ��ŸƮ ���øӴ� ���� (10���� ������ ����)
    if (GetGamePlayCount() % 10 == 0)
    {
        int32 BlindBettingMoney = static_cast<int32>((GetBlindBettingMoney() * IncreaseRateForBlindBettingMoney));
        SetBlindBettingMoney(BlindBettingMoney);        
    }
    
    // 3. ���� ������ ��ŸƮ ������������ �������� ���� ����� �÷��̾ ã��,
    //    �ش� �÷��̾ ��ŸƮ�� �ΰ��� �÷��̾� ���� ��ġ �� ���� ����� ���������� ����
    // 4. PlayerRole ����. ù ����(����������) ���� ���������� Dealer, Small blind, Big blind ����
    ExtractOrderedInGamePlayers();

    // 5. ����ī�� ���� �� ���ӽ�����Ʈ�� ����
    GamePlayManager->AddCardToCommunityCards();
    SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 6. ��� �÷��̾ �ڵ�ī�� ����
    TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
    for (ATHPlayerState* TargetPlayer : InGameSurvivedPlayers)
    {
        // 2. ī����̿��� ī�� �� ���� �̾� �÷��̾� �ڵ�ī�� ���� �� ����
        TArray<FPlayingCard> HandCards;
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());

        SetPlayerHandCards(TargetPlayer, HandCards);
    }

    // 7. PreFlop ���� ����
    FTimerDelegate CycleStartUpDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::PreFlop);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleStartUpDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
* PreFlop
*
1. PreFlop ���� ���� ����
2. Small blind, Big blind �÷��̾� üũ
3. Small blind, Big blind ��ŸƮ ���ñݾ� ����
4. SmallBlind�� BigBlind�� ���� �� ����(BigBlind ���� ������� ������ �����Ѵ�)
5. ù ���ö��忡���� ����ε� ������ ������� ġ�Ƿ� ���� �÷��̾���� üũ�� �� ����. 
6. BigBlind ���� ��ġ�� �÷��̾ �� �ο�
7. ���� ����
*/
void ATHGameMode::RunPlayCyclePreFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // ���� �ʱ�ȭ
    InitBettingRound();

    // 1. PreFlop ���ö��� ����
    SetBettingRound(EBettingRound::PreFlop);

    // 2. Get Small blind player, Big blind player
    ATHPlayerState* SmallBlindPlayer = GetPlayerForPlayerRole(EPlayerRole::SmallBlind);
    ATHPlayerState* BigBlindPlayer   = GetPlayerForPlayerRole(EPlayerRole::BigBlind);
    check(SmallBlindPlayer && BigBlindPlayer);

    // 3. Small blind, Big blind�� ��ŸƮ ���ñݾ� ����
    int32 BlindBettingMoney = GetBlindBettingMoney();

    // 4. ���� ���ö��忡���� SmallBlind�� BigBlind�� ����ε� ���� �ݾ��� �̸� �ø���
    //    BigBlind�� ���� �̸� �����Ų��
    AddPlayerRoundBettingMoney(SmallBlindPlayer, BlindBettingMoney / 2);
    AddPlayerRoundBettingMoney(BigBlindPlayer, BlindBettingMoney);
    SetPlayerTurnState(BigBlindPlayer, EPlayerTurnState::Done);

    // ���̺� ���øӴ� ����
    SetHighRoundBettingMoney(BlindBettingMoney);
    AddTotalPotMoney(GetPlayerBettingMoney(SmallBlindPlayer) + GetPlayerBettingMoney(BigBlindPlayer));

    // 5. ù ���ö��忡���� ����ε� ������ ������� ġ�Ƿ� ���� �÷��̾���� üũ�� �� ����.
    SetAppeardRaiseAction(true);

    // 6. BigBlind ���� ��ġ�� �÷��̾ �� �ο�
    TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
    int32 BigBlindPlayerIndex = InGameSurvivedPlayers.Find(BigBlindPlayer);
    ATHPlayerState* PlayerNextToBigBlind = InGameSurvivedPlayers[(BigBlindPlayerIndex + 1) % InGameSurvivedPlayers.Num()];    
    GiveTurnToPlayer(PlayerNextToBigBlind);

    // 7. ���� ����
    FTimerDelegate CyclePreFlopDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::PreFlopBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CyclePreFlopDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Flop
 *
 1. ���� �ʱ�ȭ
 2. ���ö��� ����
 3. ��ŸƮ �÷��̾ �� �ο�
 4. ���� ����
 */
void ATHGameMode::RunPlayCycleFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� �ʱ�ȭ
    InitBettingRound();

    // 2. ���ö��� ���� 
    SetBettingRound(EBettingRound::Flop);
    
    // 3. ��ŸƮ �÷��̾ �� �ο�    
    GiveTurnToPlayer(GetInGameSurvivedPlayers()[0]);

    // 4. ���� ����    
    FTimerDelegate CycleFlopDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::FlopBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleFlopDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Turn
 *
 1. ���� �ʱ�ȭ
 2. ���ö��� ����
 3. ��ŸƮ �÷��̾ �� �ο�
 4. ���� ����
 */
void ATHGameMode::RunPlayCycleTurn()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� �ʱ�ȭ
    InitBettingRound();

    // 2. ���ö��� ���� 
    SetBettingRound(EBettingRound::Turn);

    // 3. ��ŸƮ �÷��̾ �� �ο�    
    GiveTurnToPlayer(GetInGameSurvivedPlayers()[0]);

    // 4. ���� ����
    FTimerDelegate CycleTurnDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::TurnBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleTurnDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * River
 *
 1. ���� �ʱ�ȭ
 2. ���ö��� ����
 3. ��ŸƮ �÷��̾ �� �ο�
 4. ���� ����
 */
void ATHGameMode::RunPlayCycleRiver()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. ���� �ʱ�ȭ
    InitBettingRound();

    // 2. ���ö��� ���� 
    SetBettingRound(EBettingRound::River);

    // 3. ��ŸƮ �÷��̾ �� �ο�    
    GiveTurnToPlayer(GetInGameSurvivedPlayers()[0]);

    // 4. ���� ����
    FTimerDelegate CycleRiverDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::RiverBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleRiverDelegate, 1.0f, false);
    //SetGamePlayState(EGamePlayState::RiverBetting);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Showdown
 // ������ ���� ���� ���Ŀ� �� �� �̻��� �÷��̾ �����ִ� ���,
 // ���� �÷��̾���� �ڵ带 �����ϰ� ���� ������ ���Ͽ� ���ڸ� �����ϴ� ���� ���մϴ�.
 *
 1. ��ٿ� ����
 2. FinishUp ����
 * 
 */
void ATHGameMode::RunPlayCycleShowdown()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));
        
    // Showdown ����
    ProceedShowDown();

    SetBettingRound(EBettingRound::End);
    SetCurrentTurnPlayer(nullptr);

    FTimerDelegate CycleShowdownDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::FinishUp);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleShowdownDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::RunPlayCycleFinishUp()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // �÷��̾ Profit Money ����
    for (ATHPlayerState* SurvivedPlayer : GetInGameSurvivedPlayers())
    {
        AddPlayerMoney(SurvivedPlayer, GetPlayerProfitMoney(SurvivedPlayer));

        // DebugLog
        UE_LOG(LogTemp, Log, TEXT("[%s] PlayerName(%s) %s"), 
            ANSI_TO_TCHAR(__FUNCTION__), 
            *GetPlayerNickName(SurvivedPlayer),
            *UTHGameDebugManager::GetPlayerHandRankInfoAsString(GetPlayerHandRankInfo(SurvivedPlayer)));
    }

    // FinishUp ȭ���� ��ȯ�Ǳ� 1�� �� ������ ����� �÷��̾� �� �����ݾ��� ����ε� ���ñݾ׺��� ���� �÷��̾�� ������ ���� üũ����
    FTimerDelegate CycleFinishUpDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::CheckExitPlayer);
    GetWorldTimerManager().SetTimer(CheckExitTimerHandle, CycleFinishUpDelegate, FinishDelegateTimerDelay - 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/*
* Betting
*
1. ���ö��� ���� �÷���(bIsBettingRoundEnded) üũ
2. �÷��̾ ȥ�� ����(InGameSurvivedPlayers count = 1) ��Ȳ�̸� �¸� �÷��̾�� ���� ����   
3. �ƴ϶�� �������� ����
*/
void ATHGameMode::RunPlayCycleBetting()
{   
    TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
    
    // �÷��̾ ȥ�� ���� ���¶�� 
    if (InGameSurvivedPlayers.Num() == 1)
    {
        // �ش� �÷��̾� �¸� �� ��������
        SetWinnerPlayers(TArray<ATHPlayerState*>{ GetCurrentTurnPlayer() });
        SetBettingRound(EBettingRound::End);
        SetCurrentTurnPlayer(nullptr);

        SetGamePlayState(EGamePlayState::FinishUp);
    }
    // ������ ��� �����ٸ�
    else if (bIsBettingRoundEnded)
    {
        // �������� ����
        switch (EBettingRound BettingRound = GetBettingRound())
        {
        case EBettingRound::PreFlop: SetGamePlayState(EGamePlayState::Flop);     break;
        case EBettingRound::Flop:    SetGamePlayState(EGamePlayState::Turn);     break;
        case EBettingRound::Turn:    SetGamePlayState(EGamePlayState::River);    break;
        case EBettingRound::River:   SetGamePlayState(EGamePlayState::Showdown); break;
        default:
            break;
        }
    }
}

void ATHGameMode::GiveTurnToPlayer(ATHPlayerState* BettingPlayer)
{
    // �����ݾ��� 0���� �÷��̾�� �ǳʶڴ� (����)
    while (GetPlayerTurnState(BettingPlayer) == EPlayerTurnState::Wait && GetPlayerMoney(BettingPlayer) == 0)
    {
        SetPlayerTurnState(BettingPlayer, EPlayerTurnState::Done);
        BettingPlayer = GetNextInGamePlayer(BettingPlayer);
    }

    // ���� ���ѽð� Ÿ�̸�
    FTimerHandle& RemainBettingTimerHandle = GetRemainBettingTimerHandle();

    // BettingPlayer�� Turn State�� Done�̶��
    if (GetPlayerTurnState(BettingPlayer) == EPlayerTurnState::Done)
    {
        // �߰����� Raise ���� �ѹ��� �� �����̹Ƿ� �� ����
        SetCurrentTurnPlayer(nullptr);
        bIsBettingRoundEnded = true;

        // ���� ���ѽð� Ÿ�̸Ӱ� �������̶�� Ÿ�̸Ӹ� ���� ���ش�.
        if (GetWorldTimerManager().IsTimerActive(RemainBettingTimerHandle))
        {
            GetWorldTimerManager().ClearTimer(RemainBettingTimerHandle);
        }
    }
    else
    {
        // ���� �Ͽ� �ʿ��� �۾� ����
        SetPlayerTurnState(BettingPlayer, EPlayerTurnState::InProgress);
        GetPlayerController(BettingPlayer)->CheckForActionActivate();
        SetCurrentTurnPlayer(BettingPlayer);
        SetCallMoneyForCurrentPlayer(GetPlayerRequiredMoneyForCall(BettingPlayer));

        // ���� ���ѽð� Ÿ�̸� ����
        FTimerDelegate RemainBettingTimerDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::ProceedPlayersTurnDone, BettingPlayer, true);
        GetWorldTimerManager().SetTimer(RemainBettingTimerHandle, RemainBettingTimerDelegate, RemainBettingTimerDelay, false);
    }
}

void ATHGameMode::ReceiveNotifyPlayerAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney)
{
    if (!IsValid(BettingPlayer))
        return;

    UE_LOG(LogTemp, Log, TEXT("[%s] Action:%s Player:%s"),
        ANSI_TO_TCHAR(__FUNCTION__),
        *UTHGameDebugManager::GetEnumAsString(GetPlayerAction(BettingPlayer)),
        *GetPlayerNickName(BettingPlayer));

    switch (GetPlayerAction(BettingPlayer))
    {
    case EPlayerAction::Quarter: [[fallthrough]];
    case EPlayerAction::Half:    [[fallthrough]];
    case EPlayerAction::Full:    [[fallthrough]];
    case EPlayerAction::Raise:
    {
        // ���ö��� �ʱ�ȭ(��� �÷��̾��� �׼� ���� �� �� Wait ���·� �����) ��
        // ���� �÷��̾ ������׼� ����, GameState �� Raise �׼� true ����
        InitBettingRound(true, BettingPlayer);
        CalcPotMoneyForRaiseAction(BettingPlayer, CallMoney, RaiseMoney);
        break;
    }
    case EPlayerAction::Allin:
    {
        // ������Ӵϰ� �����ϸ� �������� ������ �� ���̹Ƿ� ������ ���� ����
        if (RaiseMoney > 0)
        {
            InitBettingRound(true, BettingPlayer);
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
        break;
    }
    default:
        break;
    }

    // �� ���� ���� ����
    ProceedPlayersTurnDone(BettingPlayer);
}

void ATHGameMode::ProceedPlayersTurnDone(ATHPlayerState* BettingPlayer, bool bTimeOut)
{
    // ���� ���� �÷��̾� �� ����
    SetPlayerTurnState(BettingPlayer, EPlayerTurnState::Done);

    // ���ýð� �ʰ��� ���� ���� �� ���̶��
    if (bTimeOut)
    {
        if (ATHPlayerController* BettingPlayerController = BettingPlayer->GetPlayerController())
        {
            // ���� ������ �÷��̾ ����(üũ�� ������) ���¶�� üũ ��ư�� ���� ������ ó���Ѵ�.
            if (!IsAppeardRaiseAction())
            {
                BettingPlayerController->ActionCheck();
            }
            // ���� üũ�� �Ұ����� ���¶�� ���� �� ������ ó���Ѵ�.
            else
            {
                BettingPlayerController->ActionFold();
            }
        }
    }

    // �׼����� �÷��̾ ���� ���� ���� �÷��̾ �´��� 
    // (���� ���� �ƴ� �÷��̾ ���� ���� ������ ���� ����ó�� �Ǵ� ��� �� ������ ���̴� ���� ����)
    if (BettingPlayer == GetCurrentTurnPlayer())
    {
        // ���� ���� �÷��̾� ���� ����
        GiveTurnToPlayer(GetNextInGamePlayer(BettingPlayer));
    }

    // ���� ���� �÷��̾��� �׼��� Fold��� SurvivedPlayer ����Ʈ���� ����
    if (GetPlayerAction(BettingPlayer) == EPlayerAction::Fold)
    {
        // ���� ���� �÷��̾� �� ����
        RemoveInGameSurvivedPlayer(BettingPlayer);
    }

    // ��� Fold�Ͽ� �÷��̾ �Ѹ� ���� ���¶��
    if (GetInGameSurvivedPlayers().Num() == 1)
    {
        // �¸� �÷��̾�� ���� �� ���� Finish
        FinishGameForFoldAll();
    }
}

void ATHGameMode::CalcPotMoneyForCheckAction(ATHPlayerState* BettingPlayer)
{
}

void ATHGameMode::CalcPotMoneyForCallAction(ATHPlayerState* BettingPlayer, const int32 CallMoney)
{
    AddPlayerRoundBettingMoney(BettingPlayer, CallMoney);
    AddTotalPotMoney(CallMoney);
}

void ATHGameMode::CalcPotMoneyForRaiseAction(ATHPlayerState* BettingPlayer, const int32 CallMoney, const int32 RaiseMoney)
{
    AddPlayerRoundBettingMoney(BettingPlayer, CallMoney + RaiseMoney);
    SetHighRoundBettingMoney(GetPlayerRoundBettingMoney(BettingPlayer));
    AddTotalPotMoney(CallMoney + RaiseMoney);
    SetMinRaiseMoney(RaiseMoney);
}

void ATHGameMode::CalcPotMoneyForFoldAction(ATHPlayerState* BettingPlayer)
{
}

void ATHGameMode::InitBettingRound(const bool bAppearedRaiseAction, ATHPlayerState* RaisePlayer)
{
    SetAppeardRaiseAction(bAppearedRaiseAction);
    InitSurvivedPlayersForBettingRound(RaisePlayer);

    if (!IsAppeardRaiseAction())
    {
        SetHighRoundBettingMoney(0);
    }

    bIsBettingRoundEnded = false;    
    SetMinRaiseMoney(GetBlindBettingMoney());
}

void ATHGameMode::InitSurvivedPlayersForBettingRound(ATHPlayerState* RaisePlayer)
{
    TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
    for (ATHPlayerState* SurvivedPlayer : InGameSurvivedPlayers)
    {
        if (!IsAppeardRaiseAction())
        {
            SetPlayerRoundBettingMoney(SurvivedPlayer, 0);
        }

        // ������ �÷��̾�� �׼� �� �Ͽ� ���� �ʱ�ȭ�� ���� �ʴ´�.(���� �÷��̾� ����)
        if (SurvivedPlayer == RaisePlayer)
        {
            // ������� �����ݾ��� ��� ������ �÷��̾�� �Ͽ� ���� �ʱ�ȭ�� �����Ͽ�
            // ���� �÷��̾�� ���� �ѱ� �� �ֵ��� �Ѵ�.
            if (GetPlayerMoney(SurvivedPlayer) == 0)
            {
                SetPlayerTurnState(SurvivedPlayer, EPlayerTurnState::Wait);
            }
        }
        else
        {
            SetPlayerTurnState(SurvivedPlayer, EPlayerTurnState::Wait);
            SetPlayerAction(SurvivedPlayer, EPlayerAction::None);
        }
    }
}

void ATHGameMode::CheckLoginPlayerCountForStartUp()
{
    // �÷��̾� ���� MinPlayerCount �̻��� ��� Game Start
    if (GetLoginPlayerCount() >= MinPlayerCount)
    {
        SetGamePlayState(EGamePlayState::StartUp);
        GetWorldTimerManager().ClearTimer(CycleTimerHandle);
    }
}

// PlayerRole ����. ������ ù ����(Small Blind) ���� �ð�������� ���������� Role ����
void ATHGameMode::ExtractOrderedInGamePlayers()
{
    bIsOneOnOneMatch = false;
    TArray<ATHPlayerState*> PlayersForTablePos = GetPlayersForTableSeattingPos();
    TArray<ATHPlayerState*> InGamePlayers;

    // ���� Dealer Position�� �ð�������� ���� �÷��̾ �̹� ������ �ȴ�. 
    // ��ȸ Ž���Ͽ� �÷��̾� ������Ʈ ������ ���� �� ���������� ��ȯ
    int32 StartPosForFindPlayer = (DealerPosForTable + 1) % MaxPlayerCount;
    int32 PlayerTablePos = StartPosForFindPlayer;
    do 
    {
        if (ATHPlayerState* TargetPlayer = PlayersForTablePos[PlayerTablePos])
        {
            // ó�� Ž���Ǵ� �÷��̾ ���� ���������� ����
            if (InGamePlayers.Num() == 0)
            {
                DealerPosForTable = PlayerTablePos;
            }
            InGamePlayers.Add(TargetPlayer);
        }
        PlayerTablePos = (PlayerTablePos + 1) % MaxPlayerCount;
    } while (PlayerTablePos != StartPosForFindPlayer);

    // ����� �÷��̾ ���� ���������� Dealer, SmallBlind, BigBlind Role �ο�
    EPlayerRole PlayerRole = EPlayerRole::Dealer;
    for (int32 InGamePlayerPos = 0; InGamePlayerPos < MaxRoleCount; ++InGamePlayerPos)
    {
        ATHPlayerState* TargetPlayer = InGamePlayers[InGamePlayerPos % InGamePlayers.Num()];
        SetPlayerRole(TargetPlayer, PlayerRole);

        PlayerRole = static_cast<EPlayerRole>(static_cast<int32>(PlayerRole) + 1);
    }

    // SmallBlind�� ù��° ������ �ǵ��� �ε��� 0 �÷��̾�(Dealer(2���� �� BigBlind)) �������� ���� ���������� �־��ش�.
    ATHPlayerState* DealerPlayer = InGamePlayers[0];
    InGamePlayers.Add(DealerPlayer);
    InGamePlayers.RemoveAt(0);

    SetInGamePlayersAll(InGamePlayers);
    SetInGameSurvivedPlayers(InGamePlayers);
}

void ATHGameMode::FinishGameForFoldAll()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Begin"), ANSI_TO_TCHAR(__FUNCTION__));

    ATHPlayerState* Winner = *GetInGameSurvivedPlayers().CreateConstIterator();
    SetPlayerTurnState(Winner, EPlayerTurnState::Done);

    int32 RewardMoney = GetTotalPotMoney();
    SetPlayerProfitMoney(Winner, RewardMoney);
    SetWinnerPlayers(TArray<ATHPlayerState*>{ Winner });

    SetBettingRound(EBettingRound::End);
    SetCurrentTurnPlayer(nullptr);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
    SetGamePlayState(EGamePlayState::FinishUp);
}

void ATHGameMode::ProceedShowDown()
{
    // �� ���� (Key:HandRank, Value:PlayerState)
    TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>> PlayersForHandRankInfo;

    // ��� �÷��̾���� �ڵ巩ũ ���� ����
    for (ATHPlayerState* InGamePlayer : GetInGamePlayersAll())
    {
        TArray<FPlayingCard> HandCards = GetPlayerHandCards(InGamePlayer);
        FPlayerHandRankInfo HandRankInfo = GamePlayManager->GetHandRankInfo(HandCards);
        SetPlayerHandRankInfo(InGamePlayer, HandRankInfo);
    }

    // ���� �÷��̾���� �ڵ巩ũ ������ �ʿ� �߰�
    for (ATHPlayerState* InGameSurvivedPlayer : GetInGameSurvivedPlayers())
    {
        FPlayerHandRankInfo HandRankInfo = GetPlayerHandRankInfo(InGameSurvivedPlayer);
        if (PlayersForHandRankInfo.Contains(HandRankInfo))
        {
            PlayersForHandRankInfo[HandRankInfo].Add(InGameSurvivedPlayer);            
        }
        else
        {
            PlayersForHandRankInfo.Add(HandRankInfo, TArray<ATHPlayerState*> { InGameSurvivedPlayer });
        }        
    }
    
    // �ڵ巩ũ�� ���� ������ �������� ����
    PlayersForHandRankInfo.KeySort([](const FPlayerHandRankInfo& HandRankInfoA, const FPlayerHandRankInfo& HandRankInfoB) {
        return HandRankInfoA > HandRankInfoB;
    });

    // ���ĵ� �÷��̾� �ڵ巩ũ ���� ù��° Value ����(�ڵ巩ũ�� ���� ���� Winner Player List)    
    TArray<ATHPlayerState*> Winners = PlayersForHandRankInfo.CreateConstIterator()->Value;
    SetWinnerPlayers(Winners);

    // ���� ����Ʈ ī�� 5�忡 ���� ��ŷ
    MarkingForLastBest5Cards(Winners);
    
    // �� �Ӵ� ��� ����
    CalculatePotMoney(PlayersForHandRankInfo);

    // Log
    {
        FPlayerHandRankInfo WinnerHandRankInfo = PlayersForHandRankInfo.CreateConstIterator()->Key;
        FString LogStrCardsForWinnerHandRank("");
        
        // WinnerCount
        LogStrCardsForWinnerHandRank += FString("WinnerCount:");
        LogStrCardsForWinnerHandRank += FString::FromInt(PlayersForHandRankInfo.CreateConstIterator()->Value.Num());

        // HandRank
        LogStrCardsForWinnerHandRank += FString(" HandRank:");
        LogStrCardsForWinnerHandRank += *UTHGameDebugManager::GetEnumAsString(PlayersForHandRankInfo.CreateConstIterator()->Key.HandRank);

        // HandRank Cards
        LogStrCardsForWinnerHandRank += FString(" HandRankCards:");
        for (FPlayingCard& Card : WinnerHandRankInfo.CardsForHandRank)
        {
            LogStrCardsForWinnerHandRank += FString(" (") + *UTHGameDebugManager::GetEnumAsString(Card.Suit) + FString(", ");
            LogStrCardsForWinnerHandRank += *UTHGameDebugManager::GetEnumAsString(Card.Value) + FString(")");
        }

        // Kickers
        LogStrCardsForWinnerHandRank += FString(" Kickers:");
        for (FPlayingCard& Card : WinnerHandRankInfo.Kickers)
        {
            LogStrCardsForWinnerHandRank += FString(" (") + *UTHGameDebugManager::GetEnumAsString(Card.Suit) + FString(", ");
            LogStrCardsForWinnerHandRank += *UTHGameDebugManager::GetEnumAsString(Card.Value) + FString(")");
        }

        UE_LOG(LogTemp, Log, TEXT("[%s] %s"), ANSI_TO_TCHAR(__FUNCTION__), *LogStrCardsForWinnerHandRank);
    }
}

void ATHGameMode::MarkingForLastBest5Cards(TArray<ATHPlayerState*>& Winners)
{
    if (Winners.Num() == 0)
        return;
        
    // Best5Card�� ��ŷ�� Ŀ�´�Ƽ ī��� �÷��̾� �ڵ�ī��
    TArray<FPlayingCard> CommunityCardsWithBestCardMarked = GetCommunityCards();
    TArray<TArray<FPlayingCard>> HandCardsWithBestCardMarkedForWinners;
    for (ATHPlayerState* Winner : Winners)
    {
        HandCardsWithBestCardMarkedForWinners.Add(GetPlayerHandCards(Winner));
    }

    // �ܵ��¸� : Ŀ�´�Ƽ ī��� �ڵ�ī�忡�� ���� ����Ʈ ī�� 5�忡 �ش�Ǵ� ī�带 ã�� IsOneOfTheLastBest5Cards ��ŷ�� ���ش�
    if (Winners.Num() == 1)
    {
        // ���� ����Ʈ ī�� 5��
        TArray<FPlayingCard> LastBest5Cards;
        LastBest5Cards.Append(GetPlayerHandRankInfo(Winners[0]).CardsForHandRank);
        LastBest5Cards.Append(GetPlayerHandRankInfo(Winners[0]).Kickers);

        for (FPlayingCard& OneOfTheBest5Cards : LastBest5Cards)
        {
            int32 CardIndex = INDEX_NONE;

            // Ŀ�´�Ƽ ī�� Ž�� �� ��ŷ (ã�Ҵٸ� �÷��̾� ī��� �ߺ� ��ŷ���� �ʵ��� Continue �����ش�)
            if (CommunityCardsWithBestCardMarked.Find(OneOfTheBest5Cards, CardIndex))
            {
                CommunityCardsWithBestCardMarked[CardIndex].IsOneOfTheLastBest5Cards = true;
                continue;
            }

            // �÷��̾� �ڵ�ī�� Ž�� �� ��ŷ
            for (TArray<FPlayingCard>& HandCardsWithBestCardMarked : HandCardsWithBestCardMarkedForWinners)
            {
                if (HandCardsWithBestCardMarked.Find(OneOfTheBest5Cards, CardIndex))
                {
                    HandCardsWithBestCardMarked[CardIndex].IsOneOfTheLastBest5Cards = true;
                }
            }
        }
    }
    // ��(Split) : Ŀ�´�Ƽ ī��� �¸� �÷��̾��� �ڵ� ��� IsOneOfTheLastBest5Cards ��ŷ�� ���ش�
    else
    {
        for (FPlayingCard& CommunityCard : CommunityCardsWithBestCardMarked)
        {
            CommunityCard.IsOneOfTheLastBest5Cards = true;
        }
        for (TArray<FPlayingCard>& HandCards : HandCardsWithBestCardMarkedForWinners)
        {
            HandCards[0].IsOneOfTheLastBest5Cards = true;
            HandCards[1].IsOneOfTheLastBest5Cards = true;
        }
    }

    // ����Ʈ ī����� ��ŷ�� Ŀ�´�Ƽ ī��� �ڵ�ī�� ����
    SetCommunityCards(CommunityCardsWithBestCardMarked);
    for (int32 WinnerIndex = 0; WinnerIndex < Winners.Num(); ++WinnerIndex)
    {
        SetPlayerHandCards(Winners[WinnerIndex], HandCardsWithBestCardMarkedForWinners[WinnerIndex]);
    }
}

void ATHGameMode::CalculatePotMoney(TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>>& PlayersForHandRankInfo)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // ���� �ڵ巩ũ�� �ش��ϴ� �÷��̾������ ���ñݾ� ��ŭ ��ü �̿��� ������ �������� �Ѵ�.    
    int32 RemainTotalPot = GetTotalPotMoney();
    for (const auto& PlayerForHandRankInfo : PlayersForHandRankInfo)
    {
        FPlayerHandRankInfo HandRankInfo = PlayerForHandRankInfo.Key;
        TArray<ATHPlayerState*> PotPlayers = PlayerForHandRankInfo.Value;

        // ����(�� ���� �ڵ巩ũ) �� �÷��̾��� ���ñݾװ� ���ų� ���ٸ� ������ �ݾ��� ���� ������ �ɷ�����.
        PotPlayers = PotPlayers.FilterByPredicate([](const ATHPlayerState* PotPlayer) {
            return PotPlayer->GetBettingMoney() > 0;
            });

        // �� �Ӵϸ� ȹ���� �÷��̾ ���ٸ� Continue
        if (PotPlayers.Num() == 0)
        {
            continue;
        }

        // �� �Ӵϸ� ȹ���� �÷��̾ 1�� �̶��
        if (PotPlayers.Num() == 1)
        {
            CalculatePotMoneySingle(PotPlayers, RemainTotalPot);
        }
        // �� �÷��̾ �� �̻��̶�� �ش� �÷��̾���� ���º��̹Ƿ� Chop(Split) ��Ȳ�̴�.
        else
        {
            CalculatePotMoneyChop(PotPlayers, RemainTotalPot);
        }

        // �� �й� �Ϸ�
        if (RemainTotalPot == 0)
        {
            break;
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::CalculatePotMoneySingle(TArray<ATHPlayerState*>& PotPlayers, int32& RemainTotalPot)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    ATHPlayerState* PotPlayer = PotPlayers[0];

    // ����(�� ���� �ڵ巩ũ) �� �÷��̾ ������ �ݾ��� ���ܽ�Ų ���ñݾ�.
    int32 PotPlayerBettingMoney = GetPlayerBettingMoney(PotPlayer);

    // ��ü �÷��̾���� ���ñݾ׿��� �� �÷��̾��� ���ñݾ׸�ŭ ������.
    int32 ProfitMoney = 0;
    for (ATHPlayerState* RemainBettingPlayer : GetInGamePlayersAll())
    {
        int32 RemainPlayerBettingMoney = GetPlayerBettingMoney(RemainBettingPlayer);

        // �ٸ� �÷��̾��� ���ñݾ��� ���ų� �Ҹ�Ǿ� �ִٸ� �ǳʶڴ�
        if (RemainPlayerBettingMoney == 0)
        {
            continue;
        }

        // �� �÷��̾��� ���ñݾ׿� ���� ����ݾ� ȹ��
        if (PotPlayerBettingMoney < RemainPlayerBettingMoney)
        {
            ProfitMoney += PotPlayerBettingMoney;
            RemainPlayerBettingMoney -= PotPlayerBettingMoney;
        }
        else
        {
            ProfitMoney += RemainPlayerBettingMoney;
            RemainPlayerBettingMoney = 0;
        }

        // BettingPlayer�� ���øӴϴ� Pot �÷��̾�� ���ñݾ��� ����� �������� ����
        SetPlayerBettingMoney(RemainBettingPlayer, RemainPlayerBettingMoney);
    }

    // �������� �÷��̾ �־��ٸ� �ش� �÷��̾���� ���ñݾ׵鵵 �� ��꿡 �߰��Ѵ�
    for (int32& ForceLogoutPlayerBetMoney : GetForceLogoutPlayersBetMoneyList())
    {
        if (ForceLogoutPlayerBetMoney == 0)
        {
            continue;
        }

        // �� �÷��̾��� ���ñݾ׿� ���� ����ݾ� ȹ��
        if (PotPlayerBettingMoney < ForceLogoutPlayerBetMoney)
        {
            ProfitMoney += PotPlayerBettingMoney;
            ForceLogoutPlayerBetMoney -= PotPlayerBettingMoney;
        }
        else
        {
            ProfitMoney += ForceLogoutPlayerBetMoney;
            ForceLogoutPlayerBetMoney = 0;
        }
    }

    // ���� ����ݾ׸�ŭ ���� �� �Ӵ� ����
    RemainTotalPot -= ProfitMoney;

    // �� �Ӵϸ� ȹ���� �÷��̾��� ����ݾ� ����
    SetPlayerProfitMoney(PotPlayer, ProfitMoney);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::CalculatePotMoneyChop(TArray<ATHPlayerState*>& PotPlayers, int32& RemainTotalPot)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // �������� 0, ��ü ���鼭 ���������� �ش緩ũ�� �ִ� ���� ���� �� �ݾ����� �����ϸ鼭 ���̵��� ����. 
    // �ڿ����� �� �÷��̾���� ����ݾ� ���õǵ���.

    // ���º� �÷��̾� �� ���� ū ���ñݾ��� �������� ��ü �̿��� ����ݾ��� ������, 
    // ���� �ӴϿ��� ���º� �÷��̾���� ���ñݾ� ������ŭ ������ �й��Ѵ�.

    // ���ñݾ� ������ �������� ����
    PotPlayers.Sort([](const ATHPlayerState& PotPlayerA, const ATHPlayerState& PotPlayerB) {
        return PotPlayerA.GetBettingMoney() < PotPlayerB.GetBettingMoney();
    });

    // ���º� �÷��̾���� ����ݾ� ���
    int32 PrevProfitMoney = 0;
    for (int32 PotPlayerIndex = 0; PotPlayerIndex < PotPlayers.Num(); ++PotPlayerIndex)
    {
        ATHPlayerState* PotPlayer = PotPlayers[PotPlayerIndex];

        // ����(�� ���� �ڵ巩ũ) �� �÷��̾ ������ �ݾ��� ���ܽ�Ų ���ñݾ�.
        int32 PotPlayerBettingMoney = GetPlayerBettingMoney(PotPlayer);

        // ��ü �÷��̾���� ���ñݾ׿��� �� �÷��̾��� ���ñݾ׸�ŭ ������.
        int32 ProfitMoney = 0;
        for (ATHPlayerState* RemainBettingPlayer : GetInGamePlayersAll())
        {
            int32 RemainPlayerBettingMoney = GetPlayerBettingMoney(RemainBettingPlayer);

            // �ٸ� �÷��̾��� ���ñݾ��� ���ų� �Ҹ�Ǿ� �ִٸ� �ǳʶڴ�
            if (RemainPlayerBettingMoney == 0)
            {
                continue;
            }

            // �� �÷��̾��� ���ñݾ׿� ���� ����ݾ� ȹ��
            if (PotPlayerBettingMoney < RemainPlayerBettingMoney)
            {
                ProfitMoney += PotPlayerBettingMoney;
                RemainPlayerBettingMoney -= PotPlayerBettingMoney;
            }
            else
            {
                ProfitMoney += RemainPlayerBettingMoney;
                RemainPlayerBettingMoney = 0;
            }

            // BettingPlayer�� ���øӴϴ� Pot �÷��̾�� ���ñݾ��� ����� �������� ����
            SetPlayerBettingMoney(RemainBettingPlayer, RemainPlayerBettingMoney);
        }

        // �������� �÷��̾ �־��ٸ� �ش� �÷��̾���� ���ñݾ׵鵵 �� ��꿡 �߰��Ѵ�
        for (int32& ForceLogoutPlayerBetMoney : GetForceLogoutPlayersBetMoneyList())
        {
            if (ForceLogoutPlayerBetMoney == 0)
            {
                continue;
            }

            // �� �÷��̾��� ���ñݾ׿� ���� ����ݾ� ȹ��
            if (PotPlayerBettingMoney < ForceLogoutPlayerBetMoney)
            {
                ProfitMoney += PotPlayerBettingMoney;
                ForceLogoutPlayerBetMoney -= PotPlayerBettingMoney;
            }
            else
            {
                ProfitMoney += ForceLogoutPlayerBetMoney;
                ForceLogoutPlayerBetMoney = 0;
            }
        }

        // ���� ����ݾ׸�ŭ ���� �� �Ӵ� ����
        RemainTotalPot -= ProfitMoney;

        // ���º� �÷��̾� �� ��ŭ ���ҵ� ����ݾ�
        int32 SplittedRewardMoney = ProfitMoney / (PotPlayers.Num() - PotPlayerIndex);

        // �� �Ӵϸ� ȹ���� �÷��̾��� �ɰ��� ����ݾ� ����
        SetPlayerProfitMoney(PotPlayer, PrevProfitMoney + SplittedRewardMoney);
        PrevProfitMoney += SplittedRewardMoney;
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::CheckExitPlayer()
{
    for (ATHPlayerState* TargetPlayer : THGameState->GetInGamePlayersAll())
    {
        // �÷��̾ ������ ���� �����̰ų� �����ݾ��� ����ε� ���ñݾ׺��� ������� �����Ų��.
        if (GetPlayerReservedToExit(TargetPlayer) || GetPlayerMoney(TargetPlayer) < GetBlindBettingMoney())
        {
            TargetPlayer->GetPlayerController()->ExitGame();
        }
    }

    // ���� Restart ����
    FTimerDelegate FinishUpDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::RestartTexasHoldem);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, FinishUpDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
}

void ATHGameMode::AddPlayerInHoldemTable(ATHPlayerController* LoginPlayerController)
{
    // �÷��̾� �ڸ��� �����ϱ� ���� ���̺� �ڸ��� �÷��̾� ����Ʈ�� ��ȸ�ϸ鼭 �� �ڸ��� �߰�
    TArray<ATHPlayerState*> PlayersForTableSeattingPos = GetPlayersForTableSeattingPos();
    for (int32 TableSeattingPos = 0; TableSeattingPos < PlayersForTableSeattingPos.Num(); ++TableSeattingPos)
    {
        if (!PlayersForTableSeattingPos[TableSeattingPos])
        {
            ATHPlayerState* TargetPlayerState = LoginPlayerController->GetPlayerState();
            LoginPlayerController->Init();
            TargetPlayerState->Init();

            SetPlayerTableSeattingPos(TargetPlayerState, TableSeattingPos);
            SetPlayerMoney(TargetPlayerState, 10000);

            PlayersForTableSeattingPos[TableSeattingPos] = TargetPlayerState;
            TargetPlayerState->SetPlayerController(LoginPlayerController);
            
            UE_LOG(LogTemp, Log, TEXT("[%s] Login Player(%s) "), ANSI_TO_TCHAR(__FUNCTION__), *TargetPlayerState->GetName());

            // Debug
            if (0)
            {
                if (GetPlayerNickName(TargetPlayerState) == FString(TEXT("Anonymous")))
                {
                    SetPlayerNickName(TargetPlayerState, FString::FromInt(TableSeattingPos));
                }

                if (TableSeattingPos == 0)
                {
                    SetPlayerMoney(TargetPlayerState, 3000 + 100 * (TableSeattingPos + 5));
                }
                else if (TableSeattingPos == 1)
                {
                    SetPlayerMoney(TargetPlayerState, 3000 + 100 * (TableSeattingPos + 1));
                }
                else
                {
                    SetPlayerMoney(TargetPlayerState, 3000 + 100 * (TableSeattingPos + 4));
                }
                //SetPlayerMoney(TargetPlayerState, 3000 + 100 * (TableSeattingPos + 1));
                //SetPlayerBettingMoney(THPlayerState, (THGameState->GetPlayerCount() + 1) * 1000);
                //SetPlayerAction(THPlayerState, static_cast<EPlayerAction>(THGameState->GetPlayerCount() % 5) );
                //THPlayerState->SetPlayerRole(static_cast<EPlayerRole>(THGameState->GetPlayerCount() % 4));
                //
            }
            break;
        }
    }

    // GameState�� �ڸ��� �÷��̾� ���� ����
    SetPlayersForTableSeattingPos(PlayersForTableSeattingPos);
}

void ATHGameMode::RemovePlayerInHoldemTable(ATHPlayerController* LogoutPlayerController)
{
    // Player Logout�� GameState �� �ش� �÷��̾� ������Ʈ ���� ����
    if (ATHPlayerState* LogoutPlayerState = LogoutPlayerController->GetPlayerState())
    {
        TArray<ATHPlayerState*> PlayersForTableSeattingPos = GetPlayersForTableSeattingPos();
        TArray<ATHPlayerState*> InGamePlayersAll = GetInGamePlayersAll();
        TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
        
        PlayersForTableSeattingPos[GetPlayerTableSeattingPos(LogoutPlayerState)] = nullptr;
        InGamePlayersAll.RemoveSingle(LogoutPlayerState);

        SetPlayersForTableSeattingPos(PlayersForTableSeattingPos);
        SetInGamePlayersAll(InGamePlayersAll);

        // ���� ���� ���尡 ���� ������ üũ
        switch (GetBettingRound())
        {
        case EBettingRound::PreFlop: [[fallthrough]];
        case EBettingRound::Flop: [[fallthrough]];
        case EBettingRound::Turn: [[fallthrough]];
        case EBettingRound::River:
            // �÷��̾ �ΰ��� ���� ���� ���� ���̶��
            if (InGameSurvivedPlayers.Contains(LogoutPlayerState))
            {
                // �ش� �÷��̾�� Fold �׼��� ���� ������ �����Ѵ�.
                LogoutPlayerController->ActionFold();

                // �ش� �÷��̾��� ���� �Ӵϴ� �״�� �̿� ����� �� �ֵ��� �������� �÷��̾��� ���� �Ӵ� ����Ʈ�� �����Ų��.
                AddForceLogoutPlayersBetMoneyList(LogoutPlayerState->GetBettingMoney());
            }
        default:
            break;
        }

        UE_LOG(LogTemp, Log, TEXT("[%s] LogoutPlayer NickName:%s"), ANSI_TO_TCHAR(__FUNCTION__), *GetPlayerNickName(LogoutPlayerState));
    }
}

const int32 ATHGameMode::GetLoginPlayerCount()
{
    return THGameState->GetLoginPlayerCount();
}

const int32 ATHGameMode::GetGamePlayCount()
{
    return THGameState->GetGamePlayCount();
}

const int32 ATHGameMode::GetBlindBettingMoney()
{
    return THGameState->GetBlindBettingMoney();
}

const int32 ATHGameMode::GetTotalPotMoney()
{
    return THGameState->GetTotalPotMoney();
}

ATHPlayerState* ATHGameMode::GetPlayerForPlayerRole(const EPlayerRole InPlayerRole)
{
    return THGameState->GetPlayerForPlayerRole(InPlayerRole);
}

TArray<ATHPlayerState*> ATHGameMode::GetWinnerPlayers()
{
    return THGameState->GetWinnerPlayers();
}

void ATHGameMode::SetGamePlayState(EGamePlayState InGamePlayState)
{
    THGameState->SetGamePlayState(InGamePlayState);
}

void ATHGameMode::SetBlindBettingMoney(const int32 InBlindBettingMoney)
{
    THGameState->SetBlindBettingMoney(InBlindBettingMoney);
}

const bool ATHGameMode::GetPlayerReservedToExit(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->IsReservedToExit();
}

const int32 ATHGameMode::GetPlayerMoney(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetMoney();
}

const int32 ATHGameMode::GetPlayerBettingMoney(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetBettingMoney();
}

const int32 ATHGameMode::GetPlayerProfitMoney(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetProfitMoney();
}

const int32 ATHGameMode::GetPlayerRequiredMoneyForCall(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetRequiredMoneyForCall();
}

const int32 ATHGameMode::GetPlayerRoundBettingMoney(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetRoundBettingMoney();
}

const int32 ATHGameMode::GetPlayerTableSeattingPos(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetTableSeattingPos();
}

ATHPlayerController* ATHGameMode::GetPlayerController(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetPlayerController();
}

const EPlayerAction ATHGameMode::GetPlayerAction(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetPlayerAction();
}

const EPlayerTurnState ATHGameMode::GetPlayerTurnState(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetPlayerTurnState();
}

const FString ATHGameMode::GetPlayerNickName(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetPlayerNickName();
}

const FPlayerHandRankInfo ATHGameMode::GetPlayerHandRankInfo(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetPlayerHandRankInfo();
}

TArray<FPlayingCard> ATHGameMode::GetPlayerHandCards(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->GetHandCards();
}

void ATHGameMode::SetPlayerRole(ATHPlayerState* TargetPlayer, EPlayerRole& PlayerRole)
{
    TargetPlayer->SetPlayerRole(PlayerRole);
}

TArray<ATHPlayerState*> ATHGameMode::GetPlayersForTableSeattingPos()
{
    return THGameState->GetPlayersForTableSeattingPos();
}

TArray<ATHPlayerState*> ATHGameMode::GetInGamePlayersAll()
{
    return THGameState->GetInGamePlayersAll();
}

TArray<ATHPlayerState*> ATHGameMode::GetInGameSurvivedPlayers()
{
    return THGameState->GetInGameSurvivedPlayers();
}

TArray<int32> ATHGameMode::GetForceLogoutPlayersBetMoneyList()
{
    return THGameState->GetForceLogoutPlayersBetMoneyList();
}

ATHPlayerState* ATHGameMode::GetCurrentTurnPlayer()
{
    return THGameState->GetCurrentTurnPlayer();
}

const EBettingRound ATHGameMode::GetBettingRound()
{
    return THGameState->GetBettingRound();
}

const EGamePlayState ATHGameMode::GetGamePlayState()
{
    return THGameState->GetGamePlayState();
}

const bool ATHGameMode::IsAppeardRaiseAction()
{
    return THGameState->IsAppeardRaiseAction();
}

ATHPlayerState* ATHGameMode::GetNextInGamePlayer(ATHPlayerState* TargetPlayer)
{
    return THGameState->GetNextInGamePlayer(TargetPlayer);
}

TArray<FPlayingCard> ATHGameMode::GetCommunityCards()
{
    return THGameState->GetCommunityCards();
}

FTimerHandle& ATHGameMode::GetRemainBettingTimerHandle()
{
    return THGameState->RemainBettingTimerHandle;
}

void ATHGameMode::IncreaseGamePlayCount()
{
    THGameState->IncreaseGamePlayCount();
}

void ATHGameMode::SetBettingRound(const EBettingRound& InBettingRound)
{
    GamePlayManager->SetBettingRound(InBettingRound);
    THGameState->SetBettingRound(InBettingRound);
}

void ATHGameMode::SetCommunityCards(const TArray<FPlayingCard>& InCommunityCards)
{
    THGameState->SetCommunityCards(InCommunityCards);
}

void ATHGameMode::SetPlayerHandCards(ATHPlayerState* TargetPlayer, const TArray<FPlayingCard>& InHandCards)
{
    TargetPlayer->SetHandCards(InHandCards);
}

void ATHGameMode::AddPlayerRoundBettingMoney(ATHPlayerState* TargetPlayer, const int32 InRoundBettingMoney)
{
    TargetPlayer->AddRoundBettingMoney(InRoundBettingMoney);
}

void ATHGameMode::SetPlayerBettingMoney(ATHPlayerState* TargetPlayer, const int32 InRoundBettingMoney)
{
    TargetPlayer->SetBettingMoney(InRoundBettingMoney);
}

void ATHGameMode::SetPlayerRoundBettingMoney(ATHPlayerState* TargetPlayer, const int32 InRoundBettingMoney)
{
    TargetPlayer->SetRoundBettingMoney(InRoundBettingMoney);
}

void ATHGameMode::SetPlayerTurnState(ATHPlayerState* TargetPlayer, const EPlayerTurnState& InPlayerTurnState)
{
    TargetPlayer->SetPlayerTurnState(InPlayerTurnState);
}

void ATHGameMode::AddPlayerMoney(ATHPlayerState* TargetPlayer, const int32 InMoney)
{
    TargetPlayer->AddMoney(InMoney);
}

void ATHGameMode::SetPlayerMoney(ATHPlayerState* TargetPlayer, const int32 InMoney)
{
    TargetPlayer->SetMoney(InMoney);
}

void ATHGameMode::SetPlayerNickName(ATHPlayerState* TargetPlayer, const FString InName)
{
    TargetPlayer->SetPlayerNickName(InName);
}

void ATHGameMode::SetPlayerAction(ATHPlayerState* TargetPlayer, const EPlayerAction& InPlayerAction)
{
    TargetPlayer->SetPlayerAction(InPlayerAction);
}

void ATHGameMode::SetPlayerProfitMoney(ATHPlayerState* TargetPlayer, const int32 InProfitMoney)
{
    TargetPlayer->SetProfitMoney(InProfitMoney);
}

void ATHGameMode::SetPlayerHandRankInfo(ATHPlayerState* TargetPlayer, const FPlayerHandRankInfo& InHandRankInfo)
{
    TargetPlayer->SetPlayerHandRankInfo(InHandRankInfo);
}

void ATHGameMode::SetPlayerTableSeattingPos(ATHPlayerState* TargetPlayer, const int32 InTableSeattingPos)
{
    TargetPlayer->SetTableSeattingPos(InTableSeattingPos);
}

bool ATHGameMode::IsPlayerReady(ATHPlayerState* TargetPlayer)
{
    return TargetPlayer->IsReservedToExit();
}

void ATHGameMode::SetHighRoundBettingMoney(const int32& InHighRoundBettingMoney)
{
    THGameState->SetHighRoundBettingMoney(InHighRoundBettingMoney);
}

void ATHGameMode::AddTotalPotMoney(const int32& InTotalPotMoney)
{
    THGameState->AddTotalPotMoney(InTotalPotMoney);
}

void ATHGameMode::SetMinRaiseMoney(const int32& InMinRaiseMoney)
{
    THGameState->SetMinRaiseMoney(InMinRaiseMoney);
}

void ATHGameMode::SetAppeardRaiseAction(const bool& bInAppeardRaseAction)
{
    THGameState->SetAppeardRaiseAction(bInAppeardRaseAction);
}

void ATHGameMode::SetCurrentTurnPlayer(ATHPlayerState* InCurrentTurnPlayer)
{
    THGameState->SetCurrentTurnPlayer(InCurrentTurnPlayer);
}

void ATHGameMode::SetWinnerPlayers(const TArray<ATHPlayerState*>& InWinnerPlayers)
{
    THGameState->SetWinnerPlayers(InWinnerPlayers);
}

void ATHGameMode::SetCallMoneyForCurrentPlayer(const int32& InCallMoneyForCurrentPlayer)
{
    THGameState->SetCallMoneyForCurrentPlayer(InCallMoneyForCurrentPlayer);
}

void ATHGameMode::RemoveInGameSurvivedPlayer(ATHPlayerState* InTargetPlayer)
{
    THGameState->RemoveInGameSurvivedPlayer(InTargetPlayer);
}

void ATHGameMode::AddForceLogoutPlayersBetMoneyList(const int32& InForceLogoutPlayersBetMoney)
{
    THGameState->AddForceLogoutPlayersBetMoney(InForceLogoutPlayersBetMoney);
}

void ATHGameMode::SetInGamePlayersAll(const TArray<ATHPlayerState*>& InInGamePlayers)
{
    THGameState->SetInGamePlayersAll(InInGamePlayers);
}

void ATHGameMode::SetInGameSurvivedPlayers(const TArray<ATHPlayerState*>& InInGamePlayers)
{
    THGameState->SetInGameSurvivedPlayers(InInGamePlayers);
}

void ATHGameMode::SetPlayersForTableSeattingPos(const TArray<ATHPlayerState*>& InPlayersForTableSeattingPos)
{
    THGameState->SetPlayersForTableSeattingPos(InPlayersForTableSeattingPos);
}
