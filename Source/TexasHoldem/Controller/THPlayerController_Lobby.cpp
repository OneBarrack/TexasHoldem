// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/THPlayerController_Lobby.h"
#include "Player/THLocalPlayer.h"
#include "GameInstance/THGameInstance.h"

ATHPlayerController_Lobby::ATHPlayerController_Lobby()
{

}

void ATHPlayerController_Lobby::BeginPlay()
{
    Super::BeginPlay();
    
    if (UTHGameInstance* THGameInstance = Cast<UTHGameInstance>(GetGameInstance()))
    {
        if (THGameInstance->IsEntryFailedFromHoldemTableMap())
        {
            BP_NotifyEntryFailureFromHoldemTableMap();
            THGameInstance->SetEntryFailedFromHoldemTableMap(false);
        }
    }
}

void ATHPlayerController_Lobby::Destroyed()
{
    Super::Destroyed();

}
