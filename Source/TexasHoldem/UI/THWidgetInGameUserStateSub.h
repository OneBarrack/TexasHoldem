// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TexasHoldem.h"
#include "THWidgetInGameUserStateSub.generated.h"

class ATHPlayerState;

UCLASS()
class TEXASHOLDEM_API UTHWidgetInGameUserStateSub : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
    ATHPlayerState* GetTHPlayerState();

    UFUNCTION(BlueprintCallable)
    void SetTHPlayerState(ATHPlayerState* InTHPlayerState);

private:
    ATHPlayerState* THPlayerState = nullptr;
};
