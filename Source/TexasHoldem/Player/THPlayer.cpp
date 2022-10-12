// Fill out your copyright notice in the Description page of Project Settings.

#include "THPlayer.h"
#include "PlayerState/THPlayerState.h"
#include "Controller/THPlayerController.h"

// Sets default values
ATHPlayer::ATHPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;	
}

// Called when the game starts or when spawned
void ATHPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ATHPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATHPlayer, PlayerNickName);
	DOREPLIFETIME(ATHPlayer, PlayerRole);
	DOREPLIFETIME(ATHPlayer, Money);
}

// Called every frame
void ATHPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Log, TEXT("% s::PostInitializeComponents"), *GetName());
}

void ATHPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void ATHPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ATHPlayerState* ATHPlayer::GetPlayerState() const
{
	if (ATHPlayerController* THController = Cast<ATHPlayerController>(GetController()))
	{
		return THController->GetPlayerState();
	}

	return nullptr;
}

FString ATHPlayer::GetPlayerNickName()
{
	return PlayerNickName;
}

EPlayerRole ATHPlayer::GetPlayerRole()
{
	return PlayerRole;
}

int32 ATHPlayer::GetMoney()
{
	return Money;
}
