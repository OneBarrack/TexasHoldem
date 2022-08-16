// Copyright Epic Games, Inc. All Rights Reserved.

#include "THPlayerController.h"

ATHPlayerController::ATHPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATHPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Server - %s::PostInitializeComponents"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Client - %s::PostInitializeComponents"), *GetName());
	}
}

void ATHPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}
