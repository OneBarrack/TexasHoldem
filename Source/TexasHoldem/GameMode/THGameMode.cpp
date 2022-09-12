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
    // 게임 초기화 및 스타트
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
    // 준비상태 : 모두 레디 하였는지 체크
    if (IsReadyForAllPlayers())
    {
        SetGamePlayState(EGamePlayState::StartUp);
    }
}

/**
* StartUp
* 
1. 게임 횟수 증가
2. 블라인드 스타트 베팅머니 설정
3. 딜러포지션 스타트 기준으로 플레이어 순서 배치한 리스트 생성
4. 추출된 딜러 포지션 적재
5. 1,2,3 순서에 Dealer, Small blind, Big blind 배정 (두명이면 Dealer = Big Blind)
*/
void ATHGameMode::RunPlayCycleStartUp()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 게임 횟수 증가
    THGameState->IncreaseGamePlayCount();
    
    // 2. 스타트 베팅머니 설정 (10게임 단위로 증가)
    if (THGameState->GetGamePlayCount() % 10 == 0)
    {
        int32 BlindBettingMoney = static_cast<int32>((THGameState->GetBlindBettingMoney() * IncreaseRateForBlindBettingMoney));
        THGameState->SetBlindBettingMoney(BlindBettingMoney);        
    }
    
    // 3. 현재 게임의 스타트 딜러포지션을 기준으로 가장 가까운 플레이어를 찾고,
    //    해당 플레이어를 스타트로 인게임 플레이어 순서 배치 후 새로 추출된 딜러포지션 적재
    // 4. PlayerRole 배정. 첫 인자(딜러포지션) 기준 순차적으로 Dealer, Small blind, Big blind 배정
    ExtractOrderedInGamePlayers();

    // 5. PreFlop 라운드 진행
    SetGamePlayState(EGamePlayState::PreFlop);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
* PreFlop
*
1. PreFlop 베팅 라운드 설정
2. 모든 플레이어에 핸드카드 적재
3. Small blind, Big blind의 금액 베팅 
4. SmallBlind와 BigBlind의 조기 턴 종료(BigBlind 다음 사람부터 베팅을 시작한다)
5. 첫 베팅라운드에서는 블라인드 베팅을 레이즈로 치므로 이후 플레이어들은 체크할 수 없다. 
6. BigBlind 다음 위치의 플레이어에 턴 부여
7. 베팅 진행
*/
void ATHGameMode::RunPlayCyclePreFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 베팅 초기화
    InitBettingRound();

    TArray<ATHPlayerState*> InGameSurvivedPlayers = THGameState->GetInGameSurvivedPlayers();

    // 1. PreFlop 베팅라운드 설정
    THGameState->SetBettingRound(EBettingRound::PreFlop);
    
    for (ATHPlayerState* THPlayerState : InGameSurvivedPlayers)
    {
        // 2. 카드더미에서 카드 두 장을 뽑아 플레이어 핸드카드 생성 및 적재
        TArray<FPlayingCard> HandCards;
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());
        HandCards.Add(GamePlayManager->GetCardFromCardDeck());

        THPlayerState->SetHandCards(HandCards);
    }

    // Get Small blind player, Big blind player
    ATHPlayerState* SmallBlindPlayer = THGameState->GetPlayerForPlayerRole(EPlayerRole::SmallBlind);
    ATHPlayerState* BigBlindPlayer   = THGameState->GetPlayerForPlayerRole(EPlayerRole::BigBlind);
    check(SmallBlindPlayer && BigBlindPlayer);

    // 3. Small blind, Big blind에 스타트 베팅금액 적용
    int32 BlindBettingMoney = THGameState->GetBlindBettingMoney();

    // 4. 최초 베팅라운드에서는 SmallBlind와 BigBlind의 블라인드 베팅 금액을 미리 올리고
    //    BigBlind의 턴은 미리 종료시킨다
    SmallBlindPlayer->AddRoundBettingMoney(BlindBettingMoney / 2);
    BigBlindPlayer->AddRoundBettingMoney(BlindBettingMoney);
    BigBlindPlayer->SetPlayerTurnState(EPlayerTurnState::Done);

    // 테이블 베팅머니 설정
    THGameState->SetHighRoundBettingMoney(BlindBettingMoney);
    THGameState->AddTotalPotMoney(SmallBlindPlayer->GetBettingMoney() + BigBlindPlayer->GetBettingMoney());

    // 5. 첫 베팅라운드에서는 블라인드 베팅을 레이즈로 치므로 이후 플레이어들은 체크할 수 없다.
    THGameState->SetAppeardRaiseAction(true);

    // 6. BigBlind 다음 위치의 플레이어에 턴 부여
    int32 BigBlindPlayerIndex = InGameSurvivedPlayers.Find(BigBlindPlayer);
    ATHPlayerState* PlayerNextToBigBlind = InGameSurvivedPlayers[(BigBlindPlayerIndex + 1) % InGameSurvivedPlayers.Num()];    
    GiveTurnToPlayer(PlayerNextToBigBlind);

    // 7. 베팅 진행    
    SetGamePlayState(EGamePlayState::Betting);    

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Flop
 *
 1. 베팅 초기화
 2. 베팅라운드 설정
 3. 공유카드 생성 및 게임스테이지에 적재
 4. 스타트 플레이어에 턴 부여
 5. 베팅 진행
 */
void ATHGameMode::RunPlayCycleFlop()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 베팅 초기화
    InitBettingRound();

    // 2. 베팅라운드 설정 
    GamePlayManager->SetBettingRound(EBettingRound::Flop);    
    THGameState->SetBettingRound(EBettingRound::Flop);
    
    // 3. 공유카드 생성 및 게임스테이트에 적재
    GamePlayManager->AddCardToCommunityCards();
    THGameState->SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 4. 스타트 플레이어에 턴 부여    
    GiveTurnToPlayer(THGameState->GetInGameSurvivedPlayers()[0]);

    // 5. 베팅 진행    
    SetGamePlayState(EGamePlayState::Betting);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * Turn
 *
 1. 베팅 초기화
 2. 베팅라운드 설정
 3. 공유카드 생성 및 게임스테이지에 적재
 4. 스타트 플레이어에 턴 부여
 5. 베팅 진행
 */
void ATHGameMode::RunPlayCycleTurn()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 베팅 초기화
    InitBettingRound();

    // 2. 베팅라운드 설정 
    GamePlayManager->SetBettingRound(EBettingRound::Turn);
    THGameState->SetBettingRound(EBettingRound::Turn);

    // 3. 공유카드 생성 및 게임스테이트에 적재
    GamePlayManager->AddCardToCommunityCards();
    THGameState->SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 4. 스타트 플레이어에 턴 부여    
    GiveTurnToPlayer(THGameState->GetInGameSurvivedPlayers()[0]);

    // 5. 베팅 진행
    SetGamePlayState(EGamePlayState::Betting);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

/**
 * River
 *
 1. 베팅 초기화
 2. 베팅라운드 설정
 3. 공유카드 생성 및 게임스테이지에 적재
 4. 스타트 플레이어에 턴 부여
 5. 베팅 진행
 */
void ATHGameMode::RunPlayCycleRiver()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 1. 베팅 초기화
    InitBettingRound();

    // 2. 베팅라운드 설정 
    GamePlayManager->SetBettingRound(EBettingRound::River);
    THGameState->SetBettingRound(EBettingRound::River);

    // 3. 공유카드 생성 및 게임스테이트에 적재
    GamePlayManager->AddCardToCommunityCards();
    THGameState->SetCommunityCards(GamePlayManager->GetCommunityCards());

    // 4. 스타트 플레이어에 턴 부여    
    GiveTurnToPlayer(THGameState->GetInGameSurvivedPlayers()[0]);

    // 5. 베팅 진행
    SetGamePlayState(EGamePlayState::Betting);

    UE_LOG(LogTemp, Log, TEXT("[%s] End"), ANSI_TO_TCHAR(__FUNCTION__));
}

void ATHGameMode::RunPlayCycleShowdown()
{
    UE_LOG(LogTemp, Log, TEXT("[%s] Start"), ANSI_TO_TCHAR(__FUNCTION__));

    // 점수계산 로직 필요
    WinnerPlayers = ExtractWinners();
        
    // 델리
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
1. 베팅라운드 종료 플래그(bIsBettingRoundEnded) 체크
2. 플레이어가 혼자 남은(RemainBettingPlayerCount = 1) 상황이면 승리 플레이어로 게임 종료   
3. 아니라면 다음라운드 진행
*/
void ATHGameMode::RunPlayCycleBetting()
{   
    TArray<ATHPlayerState*> InGameSurvivedPlayers = THGameState->GetInGameSurvivedPlayers();
    
    // 플레이어가 혼자 남은 상태라면 
    if (InGameSurvivedPlayers.Num() == 1)
    {
        // 해당 플레이어 승리 및 게임종료
        WinnerPlayers.Add(THGameState->GetCurrentTurnPlayer());
    }
    // 베팅이 모두 끝났다면
    else if (bIsBettingRoundEnded)
    {
        // 다음라운드 설정
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
        // 베팅라운드 초기화(모든 플레이어의 액션 제거 및 턴 Wait 상태로 만든다) 후
        // 현재 플레이어만 레이즈액션 적용, GameState 내 Raise 액션 true 세팅
        InitBettingRound(true);
        THGameState->SetAppeardRaiseAction(true);
        CalcPotMoneyForRaiseAction(BettingPlayer, CallMoney, RaiseMoney);
        break;
    }
    case EPlayerAction::Allin:
    {
        // 레이즈머니가 존재하면 올인으로 레이즈 된 것이므로 레이즈 로직 진행
        if (RaiseMoney > 0)
        {
            InitBettingRound(true);
            THGameState->SetAppeardRaiseAction(true);
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

        // 남은 베팅 플레이어 수 감소
        THGameState->RemovePlayerInGamePlayers(BettingPlayer);
        break;
    }
    default:
        break;
    }

    if (THGameState->GetLogInGamePlayerCount() > 1)
    {        
        // 다음 플레이어 정보 적재 
        ATHPlayerState* NextBettingPlayer = THGameState->GetNextInGamePlayer(BettingPlayer);

        // 다음 플레이어의 Betting State가 Done인지 체크
        if (NextBettingPlayer->GetPlayerTurnState() == EPlayerTurnState::Done)
        {
            // 추가적인 Raise 없이 한바퀴 다 돈것이므로 턴 종료
            bIsBettingRoundEnded = true;
        }
        else
        {
            // 턴 부여
            GiveTurnToPlayer(NextBettingPlayer);
        }
    }

    // 현재 플레이어 턴 종료
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
        // 올인한 플레이어는 게임 종료까지 추가적인 액션 및 턴에 대한 업데이트를 하지 않는다.
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

// PlayerRole 배정. 배팅의 첫 순서(Small Blind) 기준 시계방향으로 순차적으로 Role 배정
void ATHGameMode::ExtractOrderedInGamePlayers()
{
    bIsOneOnOneMatch = false;
    TArray<ATHPlayerState*> InGamePlayers;

    // 테이블 내 위치한 플레이어 정보
    TArray<ATHPlayerState*> PlayersForTable = THGameState->GetPlayersForTable();
    
    // 이전 Dealer Position 추출
    int32 PrevDealerPos = -1;
    if (ATHPlayerState* DealerPlayer = THGameState->GetPlayerForPlayerRole(EPlayerRole::Dealer))
    {
        PrevDealerPos = PlayersForTable.Find(DealerPlayer);
    }
    
    // 이전 Dealer Position의 시계방향으로 다음 플레이어가 이번 딜러가 된다. 
    // 순회 탐색하여 플레이어 스테이트 데이터 적재 및 딜러포지션 반환
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

    // 추출된 플레이어에 대해 순차적으로 Dealer, SmallBlind, BigBlind Role 부여
    EPlayerRole PlayerRole = EPlayerRole::Dealer;
    for (int32 InGamePlayerPos = 0; InGamePlayerPos < MaxRoleCount; ++InGamePlayerPos)
    {
        ATHPlayerState* TargetPlayer = InGamePlayers[InGamePlayerPos % InGamePlayers.Num()];
        SetPlayerForPlayerRole(TargetPlayer, PlayerRole);

        PlayerRole = static_cast<EPlayerRole>(static_cast<int32>(PlayerRole) + 1);
    }

    // SmallBlind가 첫번째 순서가 되도록 인덱스 0 플레이어(Dealer(2인일 시 BigBlind)) 포지션을 가장 마지막으로 넣어준다.
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
    // 맵 생성 (Key:HandRank, Value:PlayerState)
    TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>> PlayersForHandRankInfo;

    // 생존 플레이어들의 핸드랭크 정보 추출하며 맵에 추가
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
    
    // 핸드랭크가 높은 순으로 내림차순 정렬
    PlayersForHandRankInfo.KeySort([](const FPlayerHandRankInfo& HandRankInfoA, const FPlayerHandRankInfo& HandRankInfoB) {
        return HandRankInfoA > HandRankInfoB;
    });

    // 팟 머니 계산 진행
    CalculatePotMoney(PlayersForHandRankInfo);

    // 정렬된 플레이어 핸드랭크 맵의 첫번째 Value 추출(핸드랭크가 가장 높은 Winner Player List)
    return PlayersForHandRankInfo.CreateConstIterator()->Value;
}

void ATHGameMode::CalculatePotMoney(TMap<FPlayerHandRankInfo, TArray<ATHPlayerState*>>& PlayersForHandRankInfo)
{
    // 높은 핸드랭크에 해당하는 플레이어순으로 베팅금액 만큼 전체 팟에서 나누어 가지도록 한다.
    int32 PrevMaxBettingMoney = 0;
    int32 RemainTotalPot = THGameState->GetTotalPotMoney();
    for (const auto& PlayerForHandRankInfo : PlayersForHandRankInfo)
    {
        FPlayerHandRankInfo HandRankInfo = PlayerForHandRankInfo.Key;
        TArray<ATHPlayerState*> PotPlayers = PlayerForHandRankInfo.Value;

        // 이전(더 높은 핸드랭크) 팟 플레이어의 베팅금액과 같거나 적다면 가져갈 금액은 없기 때문에 걸러낸다.
        PotPlayers = PotPlayers.FilterByPredicate([&PrevMaxBettingMoney](const ATHPlayerState* PotPlayer) {
            return PotPlayer->GetBettingMoney() > PrevMaxBettingMoney;
            });

        // 팟 머니를 획득할 플레이어가 없다면 Continue
        if (PotPlayers.Num() == 0)
        {
            continue;
        }

        // 팟 머니를 획득할 플레이어가 1명 이라면
        if (PotPlayers.Num() == 1)
        {
            CalculatePotMoneySingle(PotPlayers, PrevMaxBettingMoney, RemainTotalPot);
        }
        // 팟 플레이어가 둘 이상이라면 해당 플레이어들은 무승부이므로 Chop(Split) 상황이다.
        else
        {
            CalculatePotMoneyChop(PotPlayers, PrevMaxBettingMoney, RemainTotalPot);
        }

        // 팟 분배 완료
        if (RemainTotalPot == 0)
        {
            break;
        }
    }
}

void ATHGameMode::CalculatePotMoneySingle(TArray<ATHPlayerState*>& PotPlayers, int32& PrevMaxBettingMoney, int32& RemainTotalPot)
{
    ATHPlayerState* PotPlayer = PotPlayers[0];

    // 이전(더 높은 핸드랭크) 팟 플레이어가 가져간 금액을 제외시킨 베팅금액.
    int32 PotPlayerBettingMoney = PotPlayer->GetBettingMoney() - PrevMaxBettingMoney;

    // 전체 플레이어들의 베팅금액에서 팟 플레이어의 베팅금액만큼 빼낸다.
    int32 RewardMoney = 0;
    for (ATHPlayerState* RemainBettingPlayer : THGameState->GetInGamePlayersAll())
    {
        int32 RemainPlayerBettingMoney = RemainBettingPlayer->GetBettingMoney();

        // 다른 플레이어의 베팅금액이 없거나 소멸되어 있다면 건너뛴다
        if (RemainPlayerBettingMoney == 0)
        {
            continue;
        }

        // 팟 플레이어의 베팅금액에 따른 보상금액 획득
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

        // BettingPlayer의 베팅머니는 Pot 플레이어에게 베팅금액을 배분한 나머지를 적재
        RemainBettingPlayer->SetBettingMoney(RemainPlayerBettingMoney);
    }

    // 현재 보상금액만큼 최종 팟 머니 감소
    RemainTotalPot -= RewardMoney;

    // 팟 머니를 획득한 플레이어의 보상금액 세팅
    PotPlayer->SetRewardMoney(RewardMoney);

    // 팟 머니를 획득한 플레이어의 베팅머니 적재
    PrevMaxBettingMoney = PotPlayerBettingMoney;
}

void ATHGameMode::CalculatePotMoneyChop(TArray<ATHPlayerState*>& PotPlayers, int32& PrevMaxBettingMoney, int32& RemainTotalPot)
{
    // 최초팟은 0, 전체 돌면서 순차적으로 해당랭크의 최대 팟을 이전 팟 금액으로 설정하면서 사이드팟 진행. 
    // 자연스레 팟 플레이어들의 보상금액 세팅되도록.

    // 무승부 플레이어 중 가장 큰 베팅금액을 기준으로 전체 팟에서 보상금액을 빼내고, 
    // 빼낸 머니에서 무승부 플레이어들의 베팅금액 비율만큼 나누어 분배한다.

    // 베팅금액 순으로 오름차순 정렬
    PotPlayers.Sort([](const ATHPlayerState& PotPlayerA, const ATHPlayerState& PotPlayerB) {
        return PotPlayerA.GetBettingMoney() < PotPlayerB.GetBettingMoney();
    });

    // 무승부 플레이어들의 보상금액 배분
    int32 PrevRewardMoney = 0;
    for (int32 PotPlayerIndex = 0; PotPlayerIndex < PotPlayers.Num(); ++PotPlayerIndex)
    {
        ATHPlayerState* PotPlayer = PotPlayers[PotPlayerIndex];

        // 이전(더 높은 핸드랭크) 팟 플레이어가 가져간 금액을 제외시킨 베팅금액.
        int32 PotPlayerBettingMoney = PotPlayer->GetBettingMoney() - PrevMaxBettingMoney;

        // 전체 플레이어들의 베팅금액에서 팟 플레이어의 베팅금액만큼 빼낸다.
        int32 RewardMoney = 0;
        for (ATHPlayerState* RemainBettingPlayer : THGameState->GetInGamePlayersAll())
        {
            int32 RemainPlayerBettingMoney = RemainBettingPlayer->GetBettingMoney();

            // 다른 플레이어의 베팅금액이 없거나 소멸되어 있다면 건너뛴다
            if (RemainPlayerBettingMoney == 0)
            {
                continue;
            }

            // 팟 플레이어의 베팅금액에 따른 보상금액 획득
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

            // BettingPlayer의 베팅머니는 Pot 플레이어에게 베팅금액을 배분한 나머지를 적재
            RemainBettingPlayer->SetBettingMoney(RemainPlayerBettingMoney);
        }

        // 현재 보상금액만큼 최종 팟 머니 감소
        RemainTotalPot -= RewardMoney;

        // 무승부 플레이어 수 만큼 분할된 보상금액
        int32 SplittedRewardMoney = RewardMoney / (PotPlayers.Num() - PotPlayerIndex);

        // 팟 머니를 획득한 플레이어의 쪼개진 보상금액 세팅
        PotPlayer->SetRewardMoney(PrevRewardMoney + SplittedRewardMoney);
        PrevRewardMoney += SplittedRewardMoney;

        // 팟 머니를 획득한 플레이어의 베팅머니 적재
        PrevMaxBettingMoney = PotPlayerBettingMoney;
    }
}

bool ATHGameMode::IsReadyForAllPlayers()
{
    bool bReadyForAllPlayers = false;

    // 게임 시작 최소 인원(MinPlayerCount) 체크
    if (THGameState->PlayerArray.Num() >= MinPlayerCount)
    {
        bReadyForAllPlayers = true;

        // 플레이어가 모두 레디 하였는지 체크
        for (APlayerState* InGamePlayer : THGameState->PlayerArray)
        {
            if (ATHPlayerState* THPlayerState = Cast<ATHPlayerState>(InGamePlayer))
            {
                // 레디 안한 플레이어가 있다면 false 리턴
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
    // Player Login시 게임 준비단계라면 인게임 플레이어 리스트에 추가
    if (THGameState->GetGamePlayState() == EGamePlayState::Prepare)
    {
        TArray<ATHPlayerState*> PlayersForTableSeattingPos = THGameState->GetPlayersForTable();

        // 플레이어 자리를 고정하기 위해 InGamePlayers 리스트를 순회하면서 빈 자리에 추가
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

        // __Debug : Log 출력
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

        // GameState에 자리별 플레이어 정보 전달
        THGameState->SetPlayersForTable(PlayersForTableSeattingPos);
    }
}

void ATHGameMode::RemovePlayerInHoldemTable(ATHPlayerController* LogoutPlayerController)
{
    // Player Logout시 인게임 플레이어 리스트에서 제거
    if (ATHPlayerState* LogoutPlayerState = LogoutPlayerController->GetPlayerState())
    {
        TArray<ATHPlayerState*> PlayersForTableSeattingPos = THGameState->GetPlayersForTable();

        // InGamePlayers 리스트 내 해당 플레이어 자리를 nullptr로 만들며 자리 공간은 보존한다.
        if (PlayersForTableSeattingPos.Contains(LogoutPlayerState))
        {
            PlayersForTableSeattingPos[PlayersForTableSeattingPos.Find(LogoutPlayerState)] = nullptr;
            LogoutPlayerState->SetTableSeattingPos(-1);

            UE_LOG(LogTemp, Log, TEXT("[%s] Logout Player(%s)"), ANSI_TO_TCHAR(__FUNCTION__), *LogoutPlayerState->GetName());
        }

        // __Debug : Log 출력
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

        // GameState에 자리별 플레이어 정보 전달
        THGameState->SetPlayersForTable(PlayersForTableSeattingPos);
    }
}
