// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/THPlayer.h"
#include "THPlayerController.h"
#include "Common/THStruct.h"
#include "Chaos/Pair.h"
#include "Manager/THGameDebugManager.h"

const FName ATHPlayerController::InputActionMouseLeft = FName(TEXT("MouseLeft"));
const FName ATHPlayerController::InputActionSpaceBar  = FName(TEXT("SpaceBar"));
const FName ATHPlayerController::InputActionKeyBoard1 = FName(TEXT("KeyBoard1"));
const FName ATHPlayerController::InputActionKeyBoard2 = FName(TEXT("KeyBoard2"));
const FName ATHPlayerController::InputActionKeyBoard3 = FName(TEXT("KeyBoard3"));
const FName ATHPlayerController::InputActionKeyBoard4 = FName(TEXT("KeyBoard4"));
const FName ATHPlayerController::InputActionKeyBoard5 = FName(TEXT("KeyBoard5"));
const FName ATHPlayerController::InputActionKeyBoard6 = FName(TEXT("KeyBoard6"));

ATHPlayerController::ATHPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATHPlayerController::BeginPlay()
{
	GamePlayMgr = NewObject<UTHGamePlayManager>(this);
}

void ATHPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Server - %s::PostInitializeComponents"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Client - %s::PostInitializeComponents"), *GetName());
	}
}

void ATHPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	PossessedPlayer = Cast<ATHPlayer>(aPawn);
}

void ATHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Key Binding
	InputComponent->BindAction(InputActionSpaceBar, IE_Pressed, this, &ATHPlayerController::ActionSpaceBar);
	InputComponent->BindAction(InputActionKeyBoard1, IE_Pressed, this, &ATHPlayerController::ActionKeyBoard1);
	InputComponent->BindAction(InputActionKeyBoard2, IE_Pressed, this, &ATHPlayerController::ActionKeyBoard2);
	InputComponent->BindAction(InputActionKeyBoard3, IE_Pressed, this, &ATHPlayerController::ActionKeyBoard3);
	InputComponent->BindAction(InputActionKeyBoard4, IE_Pressed, this, &ATHPlayerController::ActionKeyBoard4);
	InputComponent->BindAction(InputActionKeyBoard5, IE_Pressed, this, &ATHPlayerController::ActionKeyBoard5);
	InputComponent->BindAction(InputActionKeyBoard6, IE_Pressed, this, &ATHPlayerController::ActionKeyBoard6);
}

void ATHPlayerController::Tick(float DeltaSeconds)
{
}

void ATHPlayerController::ActionSpaceBar()
{
	FPlayingCard Card = GamePlayMgr->GetCardFromCardDeck();
	UE_LOG(LogTemp, Log, TEXT("Get Card! Shape:%s Name:%s, Current card deck count : %d"),
		*UTHGameDebugManager::GetEnumAsString(Card.Shape), *UTHGameDebugManager::GetEnumAsString(Card.Name), GamePlayMgr->GetCurrentCardDeckCount());
}

void ATHPlayerController::ActionKeyBoard1()
{
	GamePlayMgr->SetBettingRoundNext();
	UE_LOG(LogTemp, Log, TEXT("Current Betting Round : %s"), *UTHGameDebugManager::GetEnumAsString(GamePlayMgr->GetBettingRound()));
	
	UE_LOG(LogTemp, Log, TEXT("Current Community Card :"));
	TArray<FPlayingCard> CommunityCard = GamePlayMgr->GetCommunityCards();
	for (auto& Card : CommunityCard)
	{
		UE_LOG(LogTemp, Log, TEXT("Shape:%s, Name:%s"), *UTHGameDebugManager::GetEnumAsString(Card.Shape), *UTHGameDebugManager::GetEnumAsString(Card.Name));
	}
}

void ATHPlayerController::ActionKeyBoard2()
{
	// Debug

	TArray<FPlayingCard> TempCards;
	TempCards.Add(FPlayingCard{ EPlayingCardShape::Heart,  EPlayingCardName::King});
	TempCards.Add(FPlayingCard{ EPlayingCardShape::Clover, EPlayingCardName::Ace});
	TempCards.Add(FPlayingCard{ EPlayingCardShape::Spade,  EPlayingCardName::Ace});
	TempCards.Add(FPlayingCard{ EPlayingCardShape::Spade,  EPlayingCardName::King});
	TempCards.Add(FPlayingCard{ EPlayingCardShape::Spade,  EPlayingCardName::Ten});
	//TempCards.Add(FPlayingCard{ EPlayingCardShape::Spade,  EPlayingCardName::Queen});
	//TempCards.Add(FPlayingCard{ EPlayingCardShape::Spade,  EPlayingCardName::Jack});
	TempCards.Add(FPlayingCard{ EPlayingCardShape::Diamond,  EPlayingCardName::Ace });
	TempCards.Add(FPlayingCard{ EPlayingCardShape::Heart,  EPlayingCardName::Jack });

	// RoyalFlush
	//UE_LOG(LogTemp, Log, TEXT("HandRanking:%s"), 
	//	*UTHGameDebugManager::GetEnumAsString(GamePlayMgr->DebugGetHandRanking(TempCards, EHandRanking::RoyalFlush)));

    // StraightFlush
    //UE_LOG(LogTemp, Log, TEXT("HandRanking:%s"), 
	//	*UTHGameDebugManager::GetEnumAsString(GamePlayMgr->DebugGetHandRanking(TempCards, EHandRanking::StraightFlush)));

	// FourOfAKind
    //UE_LOG(LogTemp, Log, TEXT("HandRanking:%s"),
    //    *UTHGameDebugManager::GetEnumAsString(GamePlayMgr->DebugGetHandRanking(TempCards, EHandRanking::FourOfAKind)));

    // FullHouse
    UE_LOG(LogTemp, Log, TEXT("HandRanking:%s"),
        *UTHGameDebugManager::GetEnumAsString(GamePlayMgr->DebugGetHandRanking(TempCards, EHandRanking::FullHouse)));
}

void ATHPlayerController::ActionKeyBoard3()
{
}

void ATHPlayerController::ActionKeyBoard4()
{
}

void ATHPlayerController::ActionKeyBoard5()
{
}

void ATHPlayerController::ActionKeyBoard6()
{
}

//void ATHPlayerController::ActionSpaceBar_Implementation()
//{
//	if (HasAuthority())
//	{
//		UE_LOG(LogTemp, Log, TEXT("Server Hello~~"));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Log, TEXT("Client Hello~~"));
//	}
//	
//	MultiActionSpaceBar();
//}
//
//void ATHPlayerController::MultiActionSpaceBar_Implementation()
//{
//	UE_LOG(LogTemp, Log, TEXT("MultiCast Hello~~"));
//}
