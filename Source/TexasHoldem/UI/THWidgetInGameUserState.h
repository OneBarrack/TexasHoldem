// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TexasHoldem.h"
#include "THWidgetInGameUserState.generated.h"

class ATHPlayerState;
class UTHWidgetInGameUserStateSub;

UCLASS()
class TEXASHOLDEM_API UTHWidgetInGameUserState : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetUserStates;
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetUserActionStates;
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetUserBettingMoneys;
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetPlayerRoles;
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetPlayerReadyStates;
};
