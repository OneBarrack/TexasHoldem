// Copyright Epic Games, Inc. All Rights Reserved.

#include "THGameMode.h"
#include "THPlayerController.h"
#include "THPawn.h"

ATHGameMode::ATHGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATHPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATHPlayerController::StaticClass();
}
