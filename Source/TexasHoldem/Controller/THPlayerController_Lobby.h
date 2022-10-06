// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TexasHoldem.h"
#include "GameFramework/PlayerController.h"
#include "THPlayerController_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class TEXASHOLDEM_API ATHPlayerController_Lobby : public APlayerController
{
	GENERATED_BODY()
	
public:
    ATHPlayerController_Lobby();

public:
    virtual void BeginPlay() override;
    virtual void Destroyed() override;

};
