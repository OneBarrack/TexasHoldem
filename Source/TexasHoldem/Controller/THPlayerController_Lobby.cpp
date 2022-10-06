// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/THPlayerController_Lobby.h"

ATHPlayerController_Lobby::ATHPlayerController_Lobby()
{

}

void ATHPlayerController_Lobby::BeginPlay()
{
    Super::BeginPlay();
}

void ATHPlayerController_Lobby::Destroyed()
{
    Super::Destroyed();

    //GEngine->OnNetworkFailure().Remove(NetworkFailureDelegateHandle);
}

//void ATHPlayerController_Lobby::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
//{
//    if (FailureType == ENetworkFailure::PendingConnectionFailure)
//    {
//        if (ErrorString.Equals(FString("There are no empty seats in the table.")))
//        {
//            Client_SendNotifyEntryFailure();
//        }
//    }
//
//    UE_LOG(LogTemp, Log, TEXT("[%s] %s FailureType:%d Authority:%d this:%s"),
//        ANSI_TO_TCHAR(__FUNCTION__), *ErrorString, FailureType, HasAuthority(), *GetName());
//}
//
//void ATHPlayerController_Lobby::Client_SendNotifyEntryFailure_Implementation()
//{
//    BP_NotifyEntryFailure();
//}
