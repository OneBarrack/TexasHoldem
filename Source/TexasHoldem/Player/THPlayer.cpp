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
	
	// HandCard의 Shape 타입과 숫자 추출
	//const TCHAR* PlayingCardTypeEnumClassName = TEXT("EPlayingCardShape");
	//const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, PlayingCardTypeEnumClassName, true);

	//const FString FirstHandCardTypeName = EnumPtr->GetNameStringByValue((int32)HandCards[0].Shape);
	//UE_LOG(LogTemp, Log, TEXT("Card1 Shape:%s, Number:%d"), *FirstHandCardTypeName, HandCards[0].Number)

	//const FString SecondHandCardTypeName = EnumPtr->GetNameStringByValue((int32)HandCards[1].Shape);
 //   UE_LOG(LogTemp, Log, TEXT("Card1 Shape:%s, Number:%d"), *SecondHandCardTypeName, HandCards[1].Number)
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
