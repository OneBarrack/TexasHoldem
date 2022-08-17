// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/THPlayer.h"
#include "THPlayerController.h"
#include "Common/THStruct.h"
#include "Chaos/Pair.h"

const FName ATHPlayerController::InputActionMouseLeft = FName(TEXT("MouseLeft"));
const FName ATHPlayerController::InputActionSpaceBar = FName(TEXT("SpaceBar"));

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
	PossessedPlayer = Cast<ATHPlayer>(aPawn);
}

void ATHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Key Binding
	//InputComponent->BindAction(InputActionSpaceBar, IE_Pressed, this, &ATHPlayerController::ActionSpaceBar);
}

//void ATHPlayerController::ActionSpaceBar_Implementation()
//{
//	if (HasAuthority())
//	{
//		UE_LOG(LogTemp, Log, TEXT("Server Hello~~"));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Log, TEXT("Client Hello~~"));
//	}
//	
//	MultiActionSpaceBar();
//}
//
//void ATHPlayerController::MultiActionSpaceBar_Implementation()
//{
//	UE_LOG(LogTemp, Log, TEXT("MultiCast Hello~~"));
//}
