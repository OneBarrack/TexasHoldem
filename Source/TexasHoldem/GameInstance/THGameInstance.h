// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TexasHoldem.h"
#include "Engine/GameInstance.h"
#include "THGameInstance.generated.h"

UCLASS()
class TEXASHOLDEM_API UTHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTHGameInstance();

public:
	virtual void Init() override;

public:
    UFUNCTION(BlueprintPure)
    bool IsEntryFailedFromHoldemTableMap();

    UFUNCTION(BlueprintCallable)
    void SetEntryFailedFromHoldemTableMap(const bool bIsEntryFailed);

public:
    UFUNCTION()
    void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

    // Connection Error Event Test
    UFUNCTION(BlueprintImplementableEvent)
    void BP_NotifyEntryFailureFromHoldemTableMap();

    // Client
    UFUNCTION(Client, Reliable)
    void Client_SendNotifyEntryFailure();
    void Client_SendNotifyEntryFailure_Implementation();
    bool Client_SendNotifyEntryFailure_Validate() { return true; }

public:
    bool bIsEntryFailedFromHoldemTableMap = false;

private:
    FDelegateHandle NetworkFailureDelegateHandle;
};
