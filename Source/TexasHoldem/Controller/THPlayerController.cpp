// Copyright Epic Games, Inc. All Rights Reserved.

#include "THPlayerController.h"
#include "Player/THPlayer.h"
#include "GameMode/THGameMode.h"
#include "GameState/THGameState.h"
#include "PlayerState/THPlayerState.h"
#include "GameFramework/PlayerState.h"
#include "Manager/THGameDebugManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/THSaveGame.h"

const FName ATHPlayerController::InputActionMouseLeft = FName(TEXT("MouseLeft"));
const FName ATHPlayerController::InputActionSpaceBar  = FName(TEXT("SpaceBar"));
const FName ATHPlayerController::InputActionKeyBoard1 = FName(TEXT("KeyBoard1"));
const FName ATHPlayerController::InputActionKeyBoard2 = FName(TEXT("KeyBoard2"));
const FName ATHPlayerController::InputActionKeyBoard3 = FName(TEXT("KeyBoard3"));
const FName ATHPlayerController::InputActionKeyBoard4 = FName(TEXT("KeyBoard4"));
const FName ATHPlayerController::InputActionKeyBoard5 = FName(TEXT("KeyBoard5"));
const FName ATHPlayerController::InputActionKeyBoard6 = FName(TEXT("KeyBoard6"));
const FName ATHPlayerController::InputActionKeyReady  = FName(TEXT("Ready"));

ATHPlayerController::ATHPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATHPlayerController::BeginPlay()
{
	Super::BeginPlay();

    GamePlayMgr = NewObject<UTHHoldemPlayManager>(this);

    if (ATHPlayerState* THPlayerState = GetPlayerState())
    {
        THPlayerState->SetPlayerController(this);
    }

    SetInputMode(FInputModeGameAndUI());

    GetGameState()->OnNotifyRestartGame.AddDynamic(this, &ATHPlayerController::Init);
}

void ATHPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s][%s] Server"), ANSI_TO_TCHAR(__FUNCTION__), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s][%s] Client"), ANSI_TO_TCHAR(__FUNCTION__), *GetName());
	}
}

void ATHPlayerController::Init()
{
	PlayerActionActivateInfo = FPlayerActionActivateInfo();
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
	InputComponent->BindAction(InputActionKeyReady, IE_Pressed, this, &ATHPlayerController::ActionKeyReady);
}

void ATHPlayerController::Destroyed()
{
    Super::Destroyed();
}

void ATHPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATHPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATHPlayerController, PlayerActionActivateInfo);
}

ATHGameMode* ATHPlayerController::GetGameMode() const
{
	return GetWorld() ? Cast<ATHGameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ATHGameState* ATHPlayerController::GetGameState() const
{
	return GetWorld() ? Cast<ATHGameState>(GetWorld()->GetGameState()) : nullptr;
}

ATHPlayerState* ATHPlayerController::GetPlayerState() const
{
	return Cast<ATHPlayerState>(PlayerState);
}

ATHPlayer* ATHPlayerController::GetPlayerPawn() const
{
	return Cast<ATHPlayer>(GetPawn());
}

void ATHPlayerController::ExitGame()
{
	Client_SendNotifyExitGame();
}

void ATHPlayerController::SetPlayerSaveData(const FPlayerSaveData& InPlayerSaveData)
{
	Server_SetPlayerSaveData(InPlayerSaveData);
}

const FPlayerActionActivateInfo ATHPlayerController::GetPlayerActionActivateInfo()
{
	return PlayerActionActivateInfo;
}

void ATHPlayerController::ToggleReservedToExitState()
{
	Server_ToggleReservedToExitState();
}

void ATHPlayerController::ActionQuarter()
{
	Server_SendNotifyPlayerAction(
		EPlayerAction::Quarter, 
		PlayerActionActivateInfo.RequiredMoneyForCall,
		PlayerActionActivateInfo.RequiredMoneyForQuarter);
}

void ATHPlayerController::ActionHalf()
{
	Server_SendNotifyPlayerAction(
		EPlayerAction::Half, 
		PlayerActionActivateInfo.RequiredMoneyForCall,
		PlayerActionActivateInfo.RequiredMoneyForHalf);
}

void ATHPlayerController::ActionFull()
{
	Server_SendNotifyPlayerAction(
		EPlayerAction::Full, 
		PlayerActionActivateInfo.RequiredMoneyForCall,
		PlayerActionActivateInfo.RequiredMoneyForFull);
}

void ATHPlayerController::ActionRaise(const int32 RaiseMoney)
{
	Server_SendNotifyPlayerAction(
		EPlayerAction::Raise,
		PlayerActionActivateInfo.RequiredMoneyForCall,
		RaiseMoney);
}

void ATHPlayerController::ActionAllin()
{
	int32 CallMoney = 0;
	int32 RaiseMoney = 0;

    ATHPlayerState* THPlayerState = GetPlayerState();
    ATHGameState* THGameState = GetGameState();
	if (IsValid(THGameState) && IsValid(THPlayerState))
	{
		int32 PlayerMoney = THPlayerState->GetMoney(); // �÷��̾� �Ӵ�
		int32 MinRaiseMoney = THGameState->GetMinRaiseMoney();
		int32 RequiredMoneyForCall = PlayerActionActivateInfo.RequiredMoneyForCall;

		// �� + �ּ� ������ �ݾ��� �Ѵ� �ݾ��� �����̶�� ������ ���� ����
		if (MinRaiseMoney + RequiredMoneyForCall < PlayerMoney)
		{
			CallMoney = RequiredMoneyForCall;
			RaiseMoney = PlayerMoney - CallMoney;
		}
		// �� + �ּ� ������ �ݾ��� ���� ���ϴ� �����̶�� �� ���� ����
		else
		{
			CallMoney = PlayerMoney;
		}
	}

    Server_SendNotifyPlayerAction(EPlayerAction::Allin, CallMoney, RaiseMoney);
}

void ATHPlayerController::ActionCheck()
{
    Server_SendNotifyPlayerAction(EPlayerAction::Check);
}

void ATHPlayerController::ActionCall()
{
    Server_SendNotifyPlayerAction(EPlayerAction::Call, PlayerActionActivateInfo.RequiredMoneyForCall);
}

void ATHPlayerController::ActionFold()
{
	Server_SendNotifyPlayerAction(EPlayerAction::Fold);
}

void ATHPlayerController::CheckForActionActivate()
{
    ATHPlayerState* THPlayerState = GetPlayerState();
    ATHGameState* THGameState = GetGameState();
    if (IsValid(THGameState) && IsValid(THPlayerState))
    {
        int32 TotalPotMoney = THGameState->GetTotalPotMoney(); // ��ü �� �Ӵ�
		int32 MinRaiseMoney = THGameState->GetMinRaiseMoney();
        int32 HighRoundBettingMoney = THGameState->GetHighRoundBettingMoney(); // ���� ���� �� ���� ���� ���� �Ӵ�
        int32 PlayerRoundBettingMoney = THPlayerState->GetRoundBettingMoney(); // ���� �÷��̾��� ���� �Ӵ�        
        int32 PlayerMoney = THPlayerState->GetMoney(); // �÷��̾� �Ӵ�

        // Call
		int32 CallMoney = HighRoundBettingMoney - PlayerRoundBettingMoney; // ���� �ϱ����� �ʿ� �Ӵ�
		// �÷��̾� �����ݾ��� ���� �ϱ⿡ �����ϴٸ� �� �׼��� ���� �� ����.
		if (PlayerMoney < CallMoney)
        {
            PlayerActionActivateInfo.bEnabledCall = false;
        }
        else
        {
            PlayerActionActivateInfo.bEnabledCall = true;
        }
        PlayerActionActivateInfo.RequiredMoneyForCall = CallMoney;
        // ȭ�� �߾ӿ� ������ �ݿ� �ʿ��� �Ӵϴ� �����Ǿ�� �ϹǷ� PlayerState�� �����Ͽ� GameState���� ���� �� �ֵ��� �Ѵ�.
        THPlayerState->SetRequiredMoneyForCall(CallMoney);

		// Raise
		int32 RaiseMoney = MinRaiseMoney;
		// �÷��̾� �����ݾ��� �� + ����� �ϱ⿡ �����ϴٸ� ������ �׼��� ���� �� ����.
		if (PlayerMoney < CallMoney + RaiseMoney)
		{			
			PlayerActionActivateInfo.bEnabledRaise = false;
		}
		else
		{
			PlayerActionActivateInfo.bEnabledRaise = true;
		}

        // Full
        int32 FullMoney = TotalPotMoney + CallMoney;
		// �÷��̾� �����ݾ��� �� + Ǯ�� �ϱ⿡ �����ϰų� �����ݾ��� �ּ� ������ �ݾ׺��� ���ٸ� Ǯ �׼��� ���� �� ����.
        if (PlayerMoney < CallMoney + FullMoney || FullMoney < MinRaiseMoney)
        {			
            PlayerActionActivateInfo.bEnabledFull = false;
        }
        else
        {
            PlayerActionActivateInfo.bEnabledFull = true;
        }
        PlayerActionActivateInfo.RequiredMoneyForFull = FullMoney;

        // Half
        int32 HalfMoney = (TotalPotMoney + CallMoney) / 2;
		// �÷��̾� �����ݾ��� �� + ������ �ϱ⿡ �����ϰų� �����ݾ��� �ּ� ������ �ݾ׺��� ���ٸ� ���� �׼��� ���� �� ����.
        if (PlayerMoney < CallMoney + HalfMoney || HalfMoney < MinRaiseMoney)
        {
            PlayerActionActivateInfo.bEnabledHalf = false;
        }
        else
        {
            PlayerActionActivateInfo.bEnabledHalf = true;
        }
        PlayerActionActivateInfo.RequiredMoneyForHalf = HalfMoney;

        // Quarter
        int32 QuarterMoney = (TotalPotMoney + CallMoney) / 4;
		// �÷��̾� �����ݾ��� �� + ���͸� �ϱ⿡ �����ϰų� �����ݾ��� �ּ� ������ �ݾ׺��� ���ٸ� ���� �׼��� ���� �� ����.
        if (PlayerMoney < CallMoney + QuarterMoney || QuarterMoney < MinRaiseMoney)
        {
            PlayerActionActivateInfo.bEnabledQuarter = false;
        }
        else
        {
            PlayerActionActivateInfo.bEnabledQuarter = true;
        }
        PlayerActionActivateInfo.RequiredMoneyForQuarter = QuarterMoney;

		// ALL-IN
		// �÷��̾� �����ݾ��� 0���̸� ALL-IN �׼��� ���� �� ����.
		if (PlayerMoney == 0)
		{
			PlayerActionActivateInfo.bEnabledAllin = false;
		}
		else
		{
			PlayerActionActivateInfo.bEnabledAllin = true;
		}

        UE_LOG(LogTemp, Log, TEXT("[%s] TotalPotMoney(%d) MinRaiseMoney(%d) HighRoundBettingMoney(%d) PlayerRoundBettingMoney(%d) PlayerMoney(%d) Call(%d) Quarter(%d) Half(%d) Full(%d) Player:%s"), 
			ANSI_TO_TCHAR(__FUNCTION__), 
			TotalPotMoney, MinRaiseMoney, HighRoundBettingMoney, PlayerRoundBettingMoney, PlayerMoney, CallMoney, QuarterMoney, HalfMoney, FullMoney, *THPlayerState->GetPlayerNickName());
    }
}

void ATHPlayerController::ActionKeyReady()
{
	ToggleReservedToExitState();
    UE_LOG(LogTemp, Log, TEXT("Ready"));
}

void ATHPlayerController::ChangeHUDWidget(TSubclassOf<UUserWidget> NewHUDWidgetClass)
{
    if (CurrentHUDWidget != nullptr)
    {
		CurrentHUDWidget->RemoveFromViewport();
		CurrentHUDWidget = nullptr;
    }
    if (NewHUDWidgetClass != nullptr)
    {
		CurrentHUDWidget = CreateWidget<UUserWidget>(GetWorld(), NewHUDWidgetClass);
        if (CurrentHUDWidget != nullptr)
        {
			CurrentHUDWidget->AddToViewport();
        }
    }
}

void ATHPlayerController::Server_ToggleReservedToExitState_Implementation()
{
    if (!HasAuthority())
        return;

    if (ATHPlayerState* THPlayerState = GetPlayerState())
    {
        THPlayerState->SetReservedToExitState(THPlayerState->IsReservedToExit() ^ true);
    }
}

void ATHPlayerController::Server_SendNotifyPlayerAction_Implementation(const EPlayerAction& InPlayerAction, int32 CallMoney, int32 RaiseMoney)
{
    if (!HasAuthority())
        return;

	ATHGameMode* THGameMode = GetGameMode();
	ATHPlayerState* THPlayerState = GetPlayerState();
    if (IsValid(THGameMode) && IsValid(THPlayerState))
    {
		THPlayerState->SetPlayerAction(InPlayerAction);
        THGameMode->ReceiveNotifyPlayerAction(THPlayerState, CallMoney, RaiseMoney);
    }
}

void ATHPlayerController::Server_SetPlayerSaveData_Implementation(const FPlayerSaveData& InPlayerSaveData)
{
	if (!HasAuthority())
		return;

	if (ATHPlayerState* THPlayerState = GetPlayerState())
	{
		GetPlayerState()->SetPlayerImageIndex(InPlayerSaveData.PlayerImageIndex);
		GetPlayerState()->SetPlayerNickName(InPlayerSaveData.PlayerNickName);
	}
    UE_LOG(LogTemp, Log, TEXT("[%s] ImageIndex:%d NickName:%s"), ANSI_TO_TCHAR(__FUNCTION__), 
		InPlayerSaveData.PlayerImageIndex, *InPlayerSaveData.PlayerNickName);
}

void ATHPlayerController::Server_SetGamePause_Implementation(const bool bPaused)
{
    if (!HasAuthority())
        return;

	UGameplayStatics::SetGamePaused(GetWorld(), bPaused);
}

void ATHPlayerController::Client_SendNotifyExitGame_Implementation()
{
	BP_ExitGame();
}

void ATHPlayerController::ActionSpaceBar()
{
	static bool bPaused = false;
	bPaused ^= true;
	Server_SetGamePause(bPaused);	
}

void ATHPlayerController::ActionKeyBoard1()
{
    FPlayingCard Card = GamePlayMgr->GetCardFromCardDeck();
    UE_LOG(LogTemp, Log, TEXT("[%s] Get Card! Suit:%s Value:%s, Current card deck count : %d"),
        *UTHGameDebugManager::GetEnumAsString(Card.Suit), *UTHGameDebugManager::GetEnumAsString(Card.Value), GamePlayMgr->GetCurrentCardDeckCount());
}

void ATHPlayerController::ActionKeyBoard2()
{
	// Debug

	TArray<FPlayingCard> HandCards;
	TArray<FPlayingCard>& CommunityCards = GamePlayMgr->DebugGetCommunityCards();
	CommunityCards.Empty();

	HandCards.Add(FPlayingCard{ EPlayingCardSuit::Spades,  EPlayingCardValue::Ace });
	HandCards.Add(FPlayingCard{ EPlayingCardSuit::Clubs, EPlayingCardValue::Nine });
	CommunityCards.Add(FPlayingCard{ EPlayingCardSuit::Spades,  EPlayingCardValue::Two });
	CommunityCards.Add(FPlayingCard{ EPlayingCardSuit::Hearts,  EPlayingCardValue::Seven });
	CommunityCards.Add(FPlayingCard{ EPlayingCardSuit::Spades,  EPlayingCardValue::Three });
	CommunityCards.Add(FPlayingCard{ EPlayingCardSuit::Diamonds,  EPlayingCardValue::Jack });
	CommunityCards.Add(FPlayingCard{ EPlayingCardSuit::Spades,  EPlayingCardValue::Queen });

	FPlayerHandRankInfo PlayerHandRankInfo = GamePlayMgr->GetHandRankInfo(HandCards);

	
	UE_LOG(LogTemp, Log, TEXT("HandRank:%s"), *UTHGameDebugManager::GetEnumAsString(PlayerHandRankInfo.HandRank));
	if (PlayerHandRankInfo.HighValuesOfHandRank.Num() > 0)
	{
		FString TempStr("");
		for (EPlayingCardValue& HighValueOfHandRank : PlayerHandRankInfo.HighValuesOfHandRank)
		{
			TempStr += *UTHGameDebugManager::GetEnumAsString(HighValueOfHandRank) + FString(", ");
		}

		UE_LOG(LogTemp, Log, TEXT("HighValuesOfHandRank:%s"), *TempStr);
	}
	if (PlayerHandRankInfo.Kickers.Num() > 0)
	{
        FString TempStr("");
        for (FPlayingCard& Kicker : PlayerHandRankInfo.Kickers)
        {
			TempStr += FString("[") +
				*UTHGameDebugManager::GetEnumAsString(Kicker.Suit) + FString("_") +
				*UTHGameDebugManager::GetEnumAsString(Kicker.Value) + FString("], ");
        }
		UE_LOG(LogTemp, Log, TEXT("KickerList:%s"), *TempStr);
	}
}

void ATHPlayerController::ActionKeyBoard3()
{
	//THPlayerState->Server_ToggleReady();
	UE_LOG(LogTemp, Log, TEXT("Player Ready :%d "), GetPlayerState()->IsReservedToExit());

    auto THGameState = Cast<ATHGameState>(GetWorld()->GetGameState());
    TArray<FPlayingCard> CommunityCards = THGameState->GetCommunityCards();
    UE_LOG(LogTemp, Log, TEXT("Community Card Count:%d"), CommunityCards.Num());
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
