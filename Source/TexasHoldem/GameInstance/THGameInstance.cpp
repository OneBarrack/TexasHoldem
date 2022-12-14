// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/THGameInstance.h"

UTHGameInstance::UTHGameInstance()
{
}

void UTHGameInstance::Init()
{
    Super::Init();

    //UGameViewportClient* ddddd = GEngine->GameViewport;
    //ULocalPlayer* LocalPlayer = GEngine->GetLocalPlayerFromControllerId(GEngine->GameViewport, 0);
    //TArray<ULocalPlayer*> TestArray = GetLocalPlayers();

    NetworkFailureDelegateHandle = GEngine->OnNetworkFailure().AddUObject(this, &UTHGameInstance::HandleNetworkFailure);
}

bool UTHGameInstance::IsEntryFailedFromHoldemTableMap()
{
    return bIsEntryFailedFromHoldemTableMap;
}

void UTHGameInstance::SetEntryFailedFromHoldemTableMap(const bool bIsEntryFailed)
{
    bIsEntryFailedFromHoldemTableMap = bIsEntryFailed;
}

void UTHGameInstance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
    if (FailureType == ENetworkFailure::PendingConnectionFailure)
    {
        if (ErrorString.Equals(FString("There are no empty seats in the table.")))
        {
            Client_SendNotifyEntryFailure();
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[%s] %s FailureType:%d playerControllerNum:%d this:%s"),
        ANSI_TO_TCHAR(__FUNCTION__), *ErrorString, FailureType, GetWorld()->GetNumPlayerControllers(), *GetName());
}

void UTHGameInstance::Client_SendNotifyEntryFailure_Implementation()
{
    BP_NotifyEntryFailureFromHoldemTableMap();

    FString PlayerString = GetFirstLocalPlayerController() ? GetFirstLocalPlayerController()->GetName() : FString("None");
    UE_LOG(LogTemp, Log, TEXT("[%s] Player:%s"),
        ANSI_TO_TCHAR(__FUNCTION__), *PlayerString);
}
