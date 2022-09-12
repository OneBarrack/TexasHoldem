// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TexasHoldem.h"
#include "THPlayer.generated.h"

class ATHPlayerState;

UCLASS()
class TEXASHOLDEM_API ATHPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
    ATHPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    // Replicated
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    UFUNCTION(BlueprintPure)
    ATHPlayerState* GetPlayerState() const;

    UFUNCTION(BlueprintPure)
    FString GetPlayerNickName();

    UFUNCTION(BlueprintPure)
    EPlayerRole GetPlayerRole();

    UFUNCTION(BlueprintPure)
    int32 GetMoney();

private:
    // 이름
    UPROPERTY(replicated)
    FString PlayerNickName = FString(TEXT("Anonymous"));

    // 포지션
    UPROPERTY(replicated)
    EPlayerRole PlayerRole = EPlayerRole::None;

    // 보유 금액
    UPROPERTY(replicated)
    int32 Money = 5000;
};
