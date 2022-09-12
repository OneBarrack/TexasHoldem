// Fill out your copyright notice in the Description page of Project Settings.


#include "THWidgetInGameUserStateSub.h"

ATHPlayerState* UTHWidgetInGameUserStateSub::GetTHPlayerState()
{
    return THPlayerState;
}

void UTHWidgetInGameUserStateSub::SetTHPlayerState(ATHPlayerState* InTHPlayerState)
{
    THPlayerState = InTHPlayerState;
}
