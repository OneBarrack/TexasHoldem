// Fill out your copyright notice in the Description page of Project Settings.

#include "THPlayer.h"

// Sets default values
ATHPlayer::ATHPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATHPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// HandCard�� Shape Ÿ�԰� ���� ����
	const TCHAR* PlayingCardTypeEnumClassName = TEXT("EPlayingCardShape");
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, PlayingCardTypeEnumClassName, true);

	const FString FirstHandCardTypeName = EnumPtr->GetNameStringByValue((int32)HandCards.First.Shape);
	UE_LOG(LogTemp, Log, TEXT("Card1 Shape:%s, Number:%d"), *FirstHandCardTypeName, HandCards.First.Number)

	const FString SecondHandCardTypeName = EnumPtr->GetNameStringByValue((int32)HandCards.Second.Shape);
    UE_LOG(LogTemp, Log, TEXT("Card1 Shape:%s, Number:%d"), *SecondHandCardTypeName, HandCards.Second.Number)
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
