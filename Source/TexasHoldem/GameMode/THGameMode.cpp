// Copyright Epic Games, Inc. All Rights Reserved.

#include "THGameMode.h"
#include "Controller/THPlayerController.h"
#include "Player/THPlayer.h"

ATHGameMode::ATHGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATHPlayer::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATHPlayerController::StaticClass();
}

void ATHGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("PostLogin End"));
}
