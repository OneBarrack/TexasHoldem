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
	virtual void BeginDestroy() override;

private:
	UFUNCTION()
	void SetTHPlayerStateForSubWidgets(const TArray<ATHPlayerState*>& PlayersForTableSeattingPos);

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetUserStates;

	UPROPERTY(BlueprintReadOnly)
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetUserActionStates;

	UPROPERTY(BlueprintReadOnly)
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetUserBettingMoneys;

	UPROPERTY(BlueprintReadOnly)
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetPlayerRoles;

	UPROPERTY(BlueprintReadOnly)
	TArray<UTHWidgetInGameUserStateSub*> SubWidgetPlayerReadyStates;
    
	UPROPERTY(BlueprintReadOnly)
    TArray<UTHWidgetInGameUserStateSub*> SubWidgetRemainBettingTimers;

private:
	bool bNeedUpdatePlayerStateForSubWidget = false;
};
