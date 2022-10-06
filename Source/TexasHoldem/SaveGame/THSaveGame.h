// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "THSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TEXASHOLDEM_API UTHSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    // Save game data file name
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
    FString SaveSlotName = FString("THSaveGame");

    // Save game data file index
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
    int32 SaveIndex = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
    int32 PlayerImageIndex = -1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
    FString PlayerNickName = FString("Anonymous");
};
