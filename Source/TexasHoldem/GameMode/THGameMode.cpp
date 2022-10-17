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

    // 해당 경로 데이터 테이블 탐색
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

    // 플레이어가 가득 차 있다면 로그인 거부
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
        // 홀덤 테이블 리스트에 플레이어 정보 적재
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
        // 홀덤 테이블 리스트에서 플레이어 정보 삭제
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

    // 게임 초기화 및 스타트
    bIsOneOnOneMatch = false;
    bIsBettingRoundEnded = false;
    GamePlayManager->Init();

    // Broadcast restart delegate 
    THGameState->NotifyRestartGame();

    // Start 시 초기화 리플리케이트가 무시되는 것을 방지하기 위해 Prepare 전 Start 타임을 일정시간 유지하도록 타이머 설정
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
    // 1초마다 게임 스타트에 필요한 플레이어 수가 충족되는지 체크
    if (!GetWorldTimerManager().IsTimerActive(CycleTimerHandle))
    {
        FTimerDelegate CyclePrepareDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::CheckLoginPlayerCountForStartUp);
        GetWorldTimerManager().SetTimer(CycleTimerHandle, CyclePrepareDelegate, 1.0f, true);
    }
}

/**
* StartUp
* 
1. 게임 횟수 증가
2. 블라인드 스타트 베팅머니 설정
3. 딜러포지션 스타트 기준으로 플레이어 순서 배치한 리스트 생성
4. 추출된 딜러 포지션 적재
5. 공유카드 생성 및 게임스테이트에 적재
6. 모든 플레이어에 핸드카드 적재
7. 1,2,3 순서에 Dealer, Small blind, Big blind 배정 (두명이면 Dealer = Big Blind)
*/
void ATHGameMode::RunPlayCycleStartUp()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 게임 횟수 증가
    IncreaseGamePlayCount();
    
    // 2. 스타트 베팅머니 설정 (10게임 단위로 증가)
    if (GetGamePlayCount() % 10 == 0)
    {
        int32 BlindBettingMoney = static_cast<int32>((GetBlindBettingMoney() * IncreaseRateForBlindBettingMoney));
        SetBlindBettingMoney(BlindBettingMoney);        
    }
    
    // 3. 현재 게임의 스타트 딜러포지션을 기준으로 가장 가까운 플레이어를 찾고,
    //    해당 플레이어를 스타트로 인게임 플레이어 순서 배치 후 새로 추출된 딜러포지션 적재
    // 4. PlayerRole 배정. 첫 인자(딜러포지션) 기준 순차적으로 Dealer, Small blind, Big blind 배정
    ExtractOrderedInGamePlayers();

    // 5. 공유카드 생성 및 게임스테이트에 적재
    GamePlayManager->AddCardToCommunityCards();
    SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 6. 모든 플레이어에 핸드카드 적재
    TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
    for (ATHPlayerState* TargetPlayer : InGameSurvivedPlayers)
    {
        // 2. 카드더미에서 카드 두 장을 뽑아 플레이어 핸드카드 생성 및 적재
        TArray<FPlayingCard> HandCards;
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());

        SetPlayerHandCards(TargetPlayer, HandCards);
    }

    // 7. PreFlop 라운드 진행
    FTimerDelegate CycleStartUpDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::PreFlop);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleStartUpDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
* PreFlop
*
1. PreFlop 베팅 라운드 설정
2. Small blind, Big blind 플레이어 체크
3. Small blind, Big blind 스타트 베팅금액 적용
4. SmallBlind와 BigBlind의 조기 턴 종료(BigBlind 다음 사람부터 베팅을 시작한다)
5. 첫 베팅라운드에서는 블라인드 베팅을 레이즈로 치므로 이후 플레이어들은 체크할 수 없다. 
6. BigBlind 다음 위치의 플레이어에 턴 부여
7. 베팅 진행
*/
void ATHGameMode::RunPlayCyclePreFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 베팅 초기화
    InitBettingRound();

    // 1. PreFlop 베팅라운드 설정
    SetBettingRound(EBettingRound::PreFlop);

    // 2. Get Small blind player, Big blind player
    ATHPlayerState* SmallBlindPlayer = GetPlayerForPlayerRole(EPlayerRole::SmallBlind);
    ATHPlayerState* BigBlindPlayer   = GetPlayerForPlayerRole(EPlayerRole::BigBlind);
    check(SmallBlindPlayer && BigBlindPlayer);

    // 3. Small blind, Big blind에 스타트 베팅금액 적용
    int32 BlindBettingMoney = GetBlindBettingMoney();

    // 4. 최초 베팅라운드에서는 SmallBlind와 BigBlind의 블라인드 베팅 금액을 미리 올리고
    //    BigBlind의 턴은 미리 종료시킨다
    AddPlayerRoundBettingMoney(SmallBlindPlayer, BlindBettingMoney / 2);
    AddPlayerRoundBettingMoney(BigBlindPlayer, BlindBettingMoney);
    SetPlayerTurnState(BigBlindPlayer, EPlayerTurnState::Done);

    // 테이블 베팅머니 설정
    SetHighRoundBettingMoney(BlindBettingMoney);
    AddTotalPotMoney(GetPlayerBettingMoney(SmallBlindPlayer) + GetPlayerBettingMoney(BigBlindPlayer));

    // 5. 첫 베팅라운드에서는 블라인드 베팅을 레이즈로 치므로 이후 플레이어들은 체크할 수 없다.
    SetAppeardRaiseAction(true);

    // 6. BigBlind 다음 위치의 플레이어에 턴 부여
    TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
    int32 BigBlindPlayerIndex = InGameSurvivedPlayers.Find(BigBlindPlayer);
    ATHPlayerState* PlayerNextToBigBlind = InGameSurvivedPlayers[(BigBlindPlayerIndex + 1) % InGameSurvivedPlayers.Num()];    
    GiveTurnToPlayer(PlayerNextToBigBlind);

    // 7. 베팅 진행
    FTimerDelegate CyclePreFlopDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::PreFlopBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CyclePreFlopDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Flop
 *
 1. 베팅 초기화
 2. 베팅라운드 설정
 3. 스타트 플레이어에 턴 부여
 4. 베팅 진행
 */
void ATHGameMode::RunPlayCycleFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 베팅 초기화
    InitBettingRound();

    // 2. 베팅라운드 설정 
    SetBettingRound(EBettingRound::Flop);
    
    // 3. 스타트 플레이어에 턴 부여    
    GiveTurnToPlayer(GetInGameSurvivedPlayers()[0]);

    // 4. 베팅 진행    
    FTimerDelegate CycleFlopDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::FlopBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleFlopDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Turn
 *
 1. 베팅 초기화
 2. 베팅라운드 설정
 3. 스타트 플레이어에 턴 부여
 4. 베팅 진행
 */
void ATHGameMode::RunPlayCycleTurn()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 베팅 초기화
    InitBettingRound();

    // 2. 베팅라운드 설정 
    SetBettingRound(EBettingRound::Turn);

    // 3. 스타트 플레이어에 턴 부여    
    GiveTurnToPlayer(GetInGameSurvivedPlayers()[0]);

    // 4. 베팅 진행
    FTimerDelegate CycleTurnDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::TurnBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleTurnDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * River
 *
 1. 베팅 초기화
 2. 베팅라운드 설정
 3. 스타트 플레이어에 턴 부여
 4. 베팅 진행
 */
void ATHGameMode::RunPlayCycleRiver()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 베팅 초기화
    InitBettingRound();

    // 2. 베팅라운드 설정 
    SetBettingRound(EBettingRound::River);

    // 3. 스타트 플레이어에 턴 부여    
    GiveTurnToPlayer(GetInGameSurvivedPlayers()[0]);

    // 4. 베팅 진행
    FTimerDelegate CycleRiverDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::SetGamePlayState, EGamePlayState::RiverBetting);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, CycleRiverDelegate, 1.0f, false);
    //SetGamePlayState(EGamePlayState::RiverBetting);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Showdown
 // 마지막 베팅 라운드 이후에 두 명 이상의 플레이어가 남아있는 경우,
 // 남은 플레이어들의 핸드를 오픈하고 서로 족보를 비교하여 승자를 결정하는 것을 말합니다.
 *
 1. 쇼다운 진행
 2. FinishUp 진입
 * 
 */
void ATHGameMode::RunPlayCycleShowdown()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));
        
    // Showdown 진행
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

    // 플레이어별 Profit Money 적재
    for (ATHPlayerState* SurvivedPlayer : GetInGameSurvivedPlayers())
    {
        AddPlayerMoney(SurvivedPlayer, GetPlayerProfitMoney(SurvivedPlayer));

        // DebugLog
        UE_LOG(LogTemp, Log, TEXT("[%s] PlayerName(%s) %s"), 
            ANSI_TO_TCHAR(__FUNCTION__), 
            *GetPlayerNickName(SurvivedPlayer),
            *UTHGameDebugManager::GetPlayerHandRankInfoAsString(GetPlayerHandRankInfo(SurvivedPlayer)));
    }

    // FinishUp 화면이 전환되기 1초 전 나가기 예약된 플레이어 및 보유금액이 블라인드 베팅금액보다 낮은 플레이어들 퇴장을 위한 체크진행
    FTimerDelegate CycleFinishUpDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::CheckExitPlayer);
    GetWorldTimerManager().SetTimer(CheckExitTimerHandle, CycleFinishUpDelegate, FinishDelegateTimerDelay - 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/*
* Betting
*
1. 베팅라운드 종료 플래그(bIsBettingRoundEnded) 체크
2. 플레이어가 혼자 남은(InGameSurvivedPlayers count = 1) 상황이면 승리 플레이어로 게임 종료   
3. 아니라면 다음라운드 진행
*/
void ATHGameMode::RunPlayCycleBetting()
{   
    TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
    
    // 플레이어가 혼자 남은 상태라면 
    if (InGameSurvivedPlayers.Num() == 1)
    {
        // 해당 플레이어 승리 및 게임종료
        SetWinnerPlayers(TArray<ATHPlayerState*>{ GetCurrentTurnPlayer() });
        SetBettingRound(EBettingRound::End);
        SetCurrentTurnPlayer(nullptr);

        SetGamePlayState(EGamePlayState::FinishUp);
    }
    // 베팅이 모두 끝났다면
    else if (bIsBettingRoundEnded)
    {
        // 다음라운드 설정
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
    // 보유금액이 0원인 플레이어는 건너뛴다 (올인)
    while (GetPlayerTurnState(BettingPlayer) == EPlayerTurnState::Wait && GetPlayerMoney(BettingPlayer) == 0)
    {
        SetPlayerTurnState(BettingPlayer, EPlayerTurnState::Done);
        BettingPlayer = GetNextInGamePlayer(BettingPlayer);
    }

    // 베팅 제한시간 타이머
    FTimerHandle& RemainBettingTimerHandle = GetRemainBettingTimerHandle();

    // BettingPlayer의 Turn State가 Done이라면
    if (GetPlayerTurnState(BettingPlayer) == EPlayerTurnState::Done)
    {
        // 추가적인 Raise 없이 한바퀴 다 돈것이므로 턴 종료
        SetCurrentTurnPlayer(nullptr);
        bIsBettingRoundEnded = true;

        // 베팅 제한시간 타이머가 동작중이라면 타이머를 제거 해준다.
        if (GetWorldTimerManager().IsTimerActive(RemainBettingTimerHandle))
        {
            GetWorldTimerManager().ClearTimer(RemainBettingTimerHandle);
        }
    }
    else
    {
        // 베팅 턴에 필요한 작업 수행
        SetPlayerTurnState(BettingPlayer, EPlayerTurnState::InProgress);
        GetPlayerController(BettingPlayer)->CheckForActionActivate();
        SetCurrentTurnPlayer(BettingPlayer);
        SetCallMoneyForCurrentPlayer(GetPlayerRequiredMoneyForCall(BettingPlayer));

        // 베팅 제한시간 타이머 실행
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
        // 베팅라운드 초기화(모든 플레이어의 액션 제거 및 턴 Wait 상태로 만든다) 후
        // 현재 플레이어만 레이즈액션 적용, GameState 내 Raise 액션 true 세팅
        InitBettingRound(true, BettingPlayer);
        CalcPotMoneyForRaiseAction(BettingPlayer, CallMoney, RaiseMoney);
        break;
    }
    case EPlayerAction::Allin:
    {
        // 레이즈머니가 존재하면 올인으로 레이즈 된 것이므로 레이즈 로직 진행
        if (RaiseMoney > 0)
        {
            InitBettingRound(true, BettingPlayer);
            CalcPotMoneyForRaiseAction(BettingPlayer, CallMoney, RaiseMoney);
        }
        // 레이즈머니가 없다면 이전 플레이어들의 베팅금액에 대해 콜 형식으로 보유금액 모두를 올인한 것이므로 콜 로직 진행
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

    // 턴 종료 로직 진행
    ProceedPlayersTurnDone(BettingPlayer);
}

void ATHGameMode::ProceedPlayersTurnDone(ATHPlayerState* BettingPlayer, bool bTimeOut)
{
    // 현재 베팅 플레이어 턴 종료
    SetPlayerTurnState(BettingPlayer, EPlayerTurnState::Done);

    // 베팅시간 초과로 턴이 종료 된 것이라면
    if (bTimeOut)
    {
        if (ATHPlayerController* BettingPlayerController = BettingPlayer->GetPlayerController())
        {
            // 현재 레이즈 플레이어가 없는(체크가 가능한) 상태라면 체크 버튼을 누른 것으로 처리한다.
            if (!IsAppeardRaiseAction())
            {
                BettingPlayerController->ActionCheck();
            }
            // 현재 체크가 불가능한 상태라면 폴드 한 것으로 처리한다.
            else
            {
                BettingPlayerController->ActionFold();
            }
        }
    }

    // 액션중인 플레이어가 현재 턴의 베팅 플레이어가 맞는지 
    // (현재 턴이 아닌 플레이어가 강제 종료 등으로 인해 폴드처리 되는 경우 턴 순서가 꼬이는 것을 방지)
    if (BettingPlayer == GetCurrentTurnPlayer())
    {
        // 다음 베팅 플레이어 정보 적재
        GiveTurnToPlayer(GetNextInGamePlayer(BettingPlayer));
    }

    // 현재 베팅 플레이어의 액션이 Fold라면 SurvivedPlayer 리스트에서 제거
    if (GetPlayerAction(BettingPlayer) == EPlayerAction::Fold)
    {
        // 남은 베팅 플레이어 수 감소
        RemoveInGameSurvivedPlayer(BettingPlayer);
    }

    // 모두 Fold하여 플레이어가 한명 남은 상태라면
    if (GetInGameSurvivedPlayers().Num() == 1)
    {
        // 승리 플레이어로 설정 후 게임 Finish
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

        // 레이즈 플레이어는 액션 및 턴에 대한 초기화를 하지 않는다.(올인 플레이어 예외)
        if (SurvivedPlayer == RaisePlayer)
        {
            // 레이즈라도 보유금액을 모두 올인한 플레이어는 턴에 대한 초기화를 진행하여
            // 다음 플레이어에게 턴을 넘길 수 있도록 한다.
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
    // 플레이어 수가 MinPlayerCount 이상일 경우 Game Start
    if (GetLoginPlayerCount() >= MinPlayerCount)
    {
        SetGamePlayState(EGamePlayState::StartUp);
        GetWorldTimerManager().ClearTimer(CycleTimerHandle);
    }
}

// PlayerRole 배정. 배팅의 첫 순서(Small Blind) 기준 시계방향으로 순차적으로 Role 배정
void ATHGameMode::ExtractOrderedInGamePlayers()
{
    bIsOneOnOneMatch = false;
    TArray<ATHPlayerState*> PlayersForTablePos = GetPlayersForTableSeattingPos();
    TArray<ATHPlayerState*> InGamePlayers;

    // 이전 Dealer Position의 시계방향으로 다음 플레이어가 이번 딜러가 된다. 
    // 순회 탐색하여 플레이어 스테이트 데이터 적재 및 딜러포지션 반환
    int32 StartPosForFindPlayer = (DealerPosForTable + 1) % MaxPlayerCount;
    int32 PlayerTablePos = StartPosForFindPlayer;
    do 
    {
        if (ATHPlayerState* TargetPlayer = PlayersForTablePos[PlayerTablePos])
        {
            // 처음 탐색되는 플레이어를 딜러 포지션으로 적재
            if (InGamePlayers.Num() == 0)
            {
                DealerPosForTable = PlayerTablePos;
            }
            InGamePlayers.Add(TargetPlayer);
        }
        PlayerTablePos = (PlayerTablePos + 1) % MaxPlayerCount;
    } while (PlayerTablePos != StartPosForFindPlayer);

    // 추출된 플레이어에 대해 순차적으로 Dealer, SmallBlind, BigBlind Role 부여
    EPlayerRole PlayerRole = EPlayerRole::Dealer;
    for (int32 InGamePlayerPos = 0; InGamePlayerPos < MaxRoleCount; ++InGamePlayerPos)
    {
        ATHPlayerState* TargetPlayer = InGamePlayers[InGamePlayerPos % InGamePlayers.Num()];
        SetPlayerRole(TargetPlayer, PlayerRole);

        PlayerRole = static_cast<EPlayerRole>(static_cast<int32>(PlayerRole) + 1);
    }

    // SmallBlind가 첫번째 순서가 되도록 인덱스 0 플레이어(Dealer(2인일 시 BigBlind)) 포지션을 가장 마지막으로 넣어준다.
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
    // 맵 생성 (Key:HandRank, Value:PlayerState)
    TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>> PlayersForHandRankInfo;

    // 모든 플레이어들의 핸드랭크 정보 추출
    for (ATHPlayerState* InGamePlayer : GetInGamePlayersAll())
    {
        TArray<FPlayingCard> HandCards = GetPlayerHandCards(InGamePlayer);
        FPlayerHandRankInfo HandRankInfo = GamePlayManager->GetHandRankInfo(HandCards);
        SetPlayerHandRankInfo(InGamePlayer, HandRankInfo);
    }

    // 생존 플레이어들의 핸드랭크 정보를 맵에 추가
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
    
    // 핸드랭크가 높은 순으로 내림차순 정렬
    PlayersForHandRankInfo.KeySort([](const FPlayerHandRankInfo& HandRankInfoA, const FPlayerHandRankInfo& HandRankInfoB) {
        return HandRankInfoA > HandRankInfoB;
    });

    // 정렬된 플레이어 핸드랭크 맵의 첫번째 Value 추출(핸드랭크가 가장 높은 Winner Player List)    
    TArray<ATHPlayerState*> Winners = PlayersForHandRankInfo.CreateConstIterator()->Value;
    SetWinnerPlayers(Winners);

    // 최종 베스트 카드 5장에 대한 마킹
    MarkingForLastBest5Cards(Winners);
    
    // 팟 머니 계산 진행
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
        
    // Best5Card로 마킹할 커뮤니티 카드와 플레이어 핸드카드
    TArray<FPlayingCard> CommunityCardsWithBestCardMarked = GetCommunityCards();
    TArray<TArray<FPlayingCard>> HandCardsWithBestCardMarkedForWinners;
    for (ATHPlayerState* Winner : Winners)
    {
        HandCardsWithBestCardMarkedForWinners.Add(GetPlayerHandCards(Winner));
    }

    // 단독승리 : 커뮤니티 카드와 핸드카드에서 최종 베스트 카드 5장에 해당되는 카드를 찾고 IsOneOfTheLastBest5Cards 마킹을 해준다
    if (Winners.Num() == 1)
    {
        // 최종 베스트 카드 5장
        TArray<FPlayingCard> LastBest5Cards;
        LastBest5Cards.Append(GetPlayerHandRankInfo(Winners[0]).CardsForHandRank);
        LastBest5Cards.Append(GetPlayerHandRankInfo(Winners[0]).Kickers);

        for (FPlayingCard& OneOfTheBest5Cards : LastBest5Cards)
        {
            int32 CardIndex = INDEX_NONE;

            // 커뮤니티 카드 탐색 및 마킹 (찾았다면 플레이어 카드와 중복 마킹되지 않도록 Continue 시켜준다)
            if (CommunityCardsWithBestCardMarked.Find(OneOfTheBest5Cards, CardIndex))
            {
                CommunityCardsWithBestCardMarked[CardIndex].IsOneOfTheLastBest5Cards = true;
                continue;
            }

            // 플레이어 핸드카드 탐색 및 마킹
            for (TArray<FPlayingCard>& HandCardsWithBestCardMarked : HandCardsWithBestCardMarkedForWinners)
            {
                if (HandCardsWithBestCardMarked.Find(OneOfTheBest5Cards, CardIndex))
                {
                    HandCardsWithBestCardMarked[CardIndex].IsOneOfTheLastBest5Cards = true;
                }
            }
        }
    }
    // 찹(Split) : 커뮤니티 카드와 승리 플레이어의 핸드 모두 IsOneOfTheLastBest5Cards 마킹을 해준다
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

    // 베스트 카드들이 마킹된 커뮤니티 카드와 핸드카드 적재
    SetCommunityCards(CommunityCardsWithBestCardMarked);
    for (int32 WinnerIndex = 0; WinnerIndex < Winners.Num(); ++WinnerIndex)
    {
        SetPlayerHandCards(Winners[WinnerIndex], HandCardsWithBestCardMarkedForWinners[WinnerIndex]);
    }
}

void ATHGameMode::CalculatePotMoney(TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>>& PlayersForHandRankInfo)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 높은 핸드랭크에 해당하는 플레이어순으로 베팅금액 만큼 전체 팟에서 나누어 가지도록 한다.    
    int32 RemainTotalPot = GetTotalPotMoney();
    for (const auto& PlayerForHandRankInfo : PlayersForHandRankInfo)
    {
        FPlayerHandRankInfo HandRankInfo = PlayerForHandRankInfo.Key;
        TArray<ATHPlayerState*> PotPlayers = PlayerForHandRankInfo.Value;

        // 이전(더 높은 핸드랭크) 팟 플레이어의 베팅금액과 같거나 적다면 가져갈 금액은 없기 때문에 걸러낸다.
        PotPlayers = PotPlayers.FilterByPredicate([](const ATHPlayerState* PotPlayer) {
            return PotPlayer->GetBettingMoney() > 0;
            });

        // 팟 머니를 획득할 플레이어가 없다면 Continue
        if (PotPlayers.Num() == 0)
        {
            continue;
        }

        // 팟 머니를 획득할 플레이어가 1명 이라면
        if (PotPlayers.Num() == 1)
        {
            CalculatePotMoneySingle(PotPlayers, RemainTotalPot);
        }
        // 팟 플레이어가 둘 이상이라면 해당 플레이어들은 무승부이므로 Chop(Split) 상황이다.
        else
        {
            CalculatePotMoneyChop(PotPlayers, RemainTotalPot);
        }

        // 팟 분배 완료
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

    // 이전(더 높은 핸드랭크) 팟 플레이어가 가져간 금액을 제외시킨 베팅금액.
    int32 PotPlayerBettingMoney = GetPlayerBettingMoney(PotPlayer);

    // 전체 플레이어들의 베팅금액에서 팟 플레이어의 베팅금액만큼 빼낸다.
    int32 ProfitMoney = 0;
    for (ATHPlayerState* RemainBettingPlayer : GetInGamePlayersAll())
    {
        int32 RemainPlayerBettingMoney = GetPlayerBettingMoney(RemainBettingPlayer);

        // 다른 플레이어의 베팅금액이 없거나 소멸되어 있다면 건너뛴다
        if (RemainPlayerBettingMoney == 0)
        {
            continue;
        }

        // 팟 플레이어의 베팅금액에 따른 보상금액 획득
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

        // BettingPlayer의 베팅머니는 Pot 플레이어에게 베팅금액을 배분한 나머지를 적재
        SetPlayerBettingMoney(RemainBettingPlayer, RemainPlayerBettingMoney);
    }

    // 강제종료 플레이어가 있었다면 해당 플레이어들의 베팅금액들도 팟 계산에 추가한다
    for (int32& ForceLogoutPlayerBetMoney : GetForceLogoutPlayersBetMoneyList())
    {
        if (ForceLogoutPlayerBetMoney == 0)
        {
            continue;
        }

        // 팟 플레이어의 베팅금액에 따른 보상금액 획득
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

    // 현재 보상금액만큼 최종 팟 머니 감소
    RemainTotalPot -= ProfitMoney;

    // 팟 머니를 획득한 플레이어의 보상금액 세팅
    SetPlayerProfitMoney(PotPlayer, ProfitMoney);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::CalculatePotMoneyChop(TArray<ATHPlayerState*>& PotPlayers, int32& RemainTotalPot)
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 최초팟은 0, 전체 돌면서 순차적으로 해당랭크의 최대 팟을 이전 팟 금액으로 설정하면서 사이드팟 진행. 
    // 자연스레 팟 플레이어들의 보상금액 세팅되도록.

    // 무승부 플레이어 중 가장 큰 베팅금액을 기준으로 전체 팟에서 보상금액을 빼내고, 
    // 빼낸 머니에서 무승부 플레이어들의 베팅금액 비율만큼 나누어 분배한다.

    // 베팅금액 순으로 오름차순 정렬
    PotPlayers.Sort([](const ATHPlayerState& PotPlayerA, const ATHPlayerState& PotPlayerB) {
        return PotPlayerA.GetBettingMoney() < PotPlayerB.GetBettingMoney();
    });

    // 무승부 플레이어들의 보상금액 배분
    int32 PrevProfitMoney = 0;
    for (int32 PotPlayerIndex = 0; PotPlayerIndex < PotPlayers.Num(); ++PotPlayerIndex)
    {
        ATHPlayerState* PotPlayer = PotPlayers[PotPlayerIndex];

        // 이전(더 높은 핸드랭크) 팟 플레이어가 가져간 금액을 제외시킨 베팅금액.
        int32 PotPlayerBettingMoney = GetPlayerBettingMoney(PotPlayer);

        // 전체 플레이어들의 베팅금액에서 팟 플레이어의 베팅금액만큼 빼낸다.
        int32 ProfitMoney = 0;
        for (ATHPlayerState* RemainBettingPlayer : GetInGamePlayersAll())
        {
            int32 RemainPlayerBettingMoney = GetPlayerBettingMoney(RemainBettingPlayer);

            // 다른 플레이어의 베팅금액이 없거나 소멸되어 있다면 건너뛴다
            if (RemainPlayerBettingMoney == 0)
            {
                continue;
            }

            // 팟 플레이어의 베팅금액에 따른 보상금액 획득
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

            // BettingPlayer의 베팅머니는 Pot 플레이어에게 베팅금액을 배분한 나머지를 적재
            SetPlayerBettingMoney(RemainBettingPlayer, RemainPlayerBettingMoney);
        }

        // 강제종료 플레이어가 있었다면 해당 플레이어들의 베팅금액들도 팟 계산에 추가한다
        for (int32& ForceLogoutPlayerBetMoney : GetForceLogoutPlayersBetMoneyList())
        {
            if (ForceLogoutPlayerBetMoney == 0)
            {
                continue;
            }

            // 팟 플레이어의 베팅금액에 따른 보상금액 획득
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

        // 현재 보상금액만큼 최종 팟 머니 감소
        RemainTotalPot -= ProfitMoney;

        // 무승부 플레이어 수 만큼 분할된 보상금액
        int32 SplittedRewardMoney = ProfitMoney / (PotPlayers.Num() - PotPlayerIndex);

        // 팟 머니를 획득한 플레이어의 쪼개진 보상금액 세팅
        SetPlayerProfitMoney(PotPlayer, PrevProfitMoney + SplittedRewardMoney);
        PrevProfitMoney += SplittedRewardMoney;
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::CheckExitPlayer()
{
    for (ATHPlayerState* TargetPlayer : THGameState->GetInGamePlayersAll())
    {
        // 플레이어가 나가기 예약 상태이거나 보유금액이 블라인드 베팅금액보다 낮을경우 퇴장시킨다.
        if (GetPlayerReservedToExit(TargetPlayer) || GetPlayerMoney(TargetPlayer) < GetBlindBettingMoney())
        {
            TargetPlayer->GetPlayerController()->ExitGame();
        }
    }

    // 이후 Restart 진행
    FTimerDelegate FinishUpDelegate = FTimerDelegate::CreateUObject(this, &ATHGameMode::RestartTexasHoldem);
    GetWorldTimerManager().SetTimer(CycleTimerHandle, FinishUpDelegate, 1.0f, false);

    SetGamePlayState(EGamePlayState::Wait);
}

void ATHGameMode::AddPlayerInHoldemTable(ATHPlayerController* LoginPlayerController)
{
    // 플레이어 자리를 고정하기 위해 테이블 자리별 플레이어 리스트를 순회하면서 빈 자리에 추가
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

    // GameState에 자리별 플레이어 정보 전달
    SetPlayersForTableSeattingPos(PlayersForTableSeattingPos);
}

void ATHGameMode::RemovePlayerInHoldemTable(ATHPlayerController* LogoutPlayerController)
{
    // Player Logout시 GameState 내 해당 플레이어 스테이트 정보 제거
    if (ATHPlayerState* LogoutPlayerState = LogoutPlayerController->GetPlayerState())
    {
        TArray<ATHPlayerState*> PlayersForTableSeattingPos = GetPlayersForTableSeattingPos();
        TArray<ATHPlayerState*> InGamePlayersAll = GetInGamePlayersAll();
        TArray<ATHPlayerState*> InGameSurvivedPlayers = GetInGameSurvivedPlayers();
        
        PlayersForTableSeattingPos[GetPlayerTableSeattingPos(LogoutPlayerState)] = nullptr;
        InGamePlayersAll.RemoveSingle(LogoutPlayerState);

        SetPlayersForTableSeattingPos(PlayersForTableSeattingPos);
        SetInGamePlayersAll(InGamePlayersAll);

        // 현재 베팅 라운드가 진행 중인지 체크
        switch (GetBettingRound())
        {
        case EBettingRound::PreFlop: [[fallthrough]];
        case EBettingRound::Flop: [[fallthrough]];
        case EBettingRound::Turn: [[fallthrough]];
        case EBettingRound::River:
            // 플레이어가 인게임 베팅 도중 나간 것이라면
            if (InGameSurvivedPlayers.Contains(LogoutPlayerState))
            {
                // 해당 플레이어는 Fold 액션을 취한 것으로 간주한다.
                LogoutPlayerController->ActionFold();

                // 해당 플레이어의 베팅 머니는 그대로 팟에 적용될 수 있도록 강제종료 플레이어의 베팅 머니 리스트에 적재시킨다.
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
