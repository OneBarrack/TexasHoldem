// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TexasHoldem.h"
#include "THWidgetPlayerAction.generated.h"

class UButton;

UCLASS()
class TEXASHOLDEM_API UTHWidgetPlayerAction : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

public:
    UPROPERTY()
    UButton* ActionQuarterButton;
    
    UPROPERTY()
    UButton* ActionHalfButton;
    
    UPROPERTY()
    UButton* ActionFullButton;
    
    UPROPERTY()
    UButton* ActionRaiseButton;
    
    UPROPERTY()
    UButton* ActionCheckButton;

    UPROPERTY()
    UButton* ActionCallButton;

    UPROPERTY()
    UButton* ActionFoldButton;

    UPROPERTY()
    UButton* ActionAllinButton;
};
