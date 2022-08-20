// Fill out your copyright notice in the Description page of Project Settings.


#include "THGameMode.h"
#include "GameState/THGameState.h"
#include "PlayerState/THPlayerState.h"
#include "Player/THPlayer.h"
#include "Controller/THPlayerController.h"


ATHGameMode::ATHGameMode()
{
    DefaultPawnClass = ATHPlayer::StaticClass();
    PlayerControllerClass = ATHPlayerController::StaticClass();
    GameStateClass = ATHGameState::StaticClass();
    PlayerStateClass = ATHPlayerState::StaticClass();

    InGamePlayers.Reserve(MaxPlayerCount);
}

void ATHGameMode::PostLogin(APlayerController* NewPlayer)
{
    UE_LOG(LogTemp, Log, TEXT("PostLogin Begin"));
    Super::PostLogin(NewPlayer);
    UE_LOG(LogTemp, Log, TEXT("PostLogin End"));

    // Player Login시 인게임 플레이어 리스트에 추가
    if (ATHPlayerController* LoginPlayerController = Cast<ATHPlayerController>(NewPlayer))
    {
        if (!InGamePlayers.Contains(LoginPlayerController))
        {
            InGamePlayers.Add(LoginPlayerController);
        }

        UE_LOG(LogTemp, Log, TEXT("Player Login. Player Count:%d"), InGamePlayers.Num());
    }
    //if (GameState)
    //{
    //    UE_LOG(LogTemp, Log, TEXT("Player Count:%d"), GameState->PlayerArray.Num());
    //}
}

void ATHGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

    // Player Logout시 인게임 플레이어 리스트에서 제거
    if (ATHPlayerController* LogoutPlayerController = Cast<ATHPlayerController>(Exiting))
    {
        if (InGamePlayers.Contains(LogoutPlayerController))
        {
            InGamePlayers.Remove(LogoutPlayerController);
        }

        UE_LOG(LogTemp, Log, TEXT("Player Logout. Player Count:%d"), InGamePlayers.Num());
    }
}

void ATHGameMode::StartPlay()
{
    GamePlayManager = NewObject<UTHGamePlayManager>(this);

    Super::StartPlay();
}

void ATHGameMode::BeginPlay()
{
    UE_LOG(LogTemp, Log, TEXT("BeginPlay Start"));
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("BeginPlay End"));
}

void ATHGameMode::StartNextBettingRound()
{
    GamePlayManager->SetNextBettingRound();
    //Cast<ATHGameState>(GameState)->Multicast_SetBettingRound(GamePlayManager->GetBettingRound());
    Cast<ATHGameState>(GameState)->SetBettingRound(GamePlayManager->GetBettingRound());
}
