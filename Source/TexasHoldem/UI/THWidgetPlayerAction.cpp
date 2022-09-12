// Fill out your copyright notice in the Description page of Project Settings.

#include "THWidgetPlayerAction.h"
#include "Components/Button.h"
#include "Controller/THPlayerController.h"

bool UTHWidgetPlayerAction::Initialize()
{
    Super::Initialize();

    //ActionQuarterButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Quarter")));
    //ActionHalfButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Half")));
    //ActionFullButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Full")));
    //ActionRaiseButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Raise")));
    //ActionAllinButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Allin")));
    //ActionCheckButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Check")));
    //ActionCallButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Call")));    
    //ActionFoldButton = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Action_Fold")));

    //if (ATHPlayerController* THPlayerController = Cast<ATHPlayerController>(GetOwningPlayer()))
    //{
    //    ActionQuarterButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionQuarter);
    //    ActionHalfButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionHalf);
    //    ActionFullButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionFull);
    //    ActionRaiseButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionRaise);
    //    ActionAllinButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionAllin);
    //    ActionCheckButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionCheck);
    //    ActionCallButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionCall);
    //    ActionFoldButton->OnClicked.AddDynamic(THPlayerController, &ATHPlayerController::ActionFold);
    //}

    return true;
}
