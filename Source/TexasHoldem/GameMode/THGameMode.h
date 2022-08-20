// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TexasHoldem.h"
#include "GameFramework/GameMode.h"
#include "Manager/THGamePlayManager.h"
#include "THGameMode.generated.h"

class ATHPlayerController;

UCLASS()
class TEXASHOLDEM_API ATHGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ATHGameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartNextBettingRound();

private:
	// ���� �÷��� �Ŵ���
    UPROPERTY()
    UTHGamePlayManager* GamePlayManager;

	// �ΰ��� �÷��̾� ����Ʈ
	UPROPERTY()
	TArray<ATHPlayerController*> InGamePlayers;

public:
	FORCEINLINE UTHGamePlayManager* GetGamePlayManager() { return GamePlayManager; }
};
