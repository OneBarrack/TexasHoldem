// Copyright Epic Games, Inc. All Rights Reserved.

#include "THPlayerController.h"

ATHPlayerController::ATHPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
