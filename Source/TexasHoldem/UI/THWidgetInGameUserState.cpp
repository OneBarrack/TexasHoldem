// Fill out your copyright notice in the Description page of Project Settings.


#include "THWidgetInGameUserState.h"
#include "THWidgetInGameUserStateSub.h"
#include "GameState/THGameState.h"
#include "PlayerState/THPlayerState.h"
#include "Controller/THPlayerController.h"

bool UTHWidgetInGameUserState::Initialize()
{
    Super::Initialize();

    // UserState
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_Main"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_1"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_2"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_3"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_4"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_5"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_6"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_7"))));
    SubWidgetUserStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserState_8"))));

    // ActionState
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_Main"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_1"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_2"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_3"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_4"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_5"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_6"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_7"))));
    SubWidgetUserActionStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserActionState_8"))));

    // BettingMoney
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_Main"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_1"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_2"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_3"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_4"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_5"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_6"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_7"))));
    SubWidgetUserBettingMoneys.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_UserBettingMoney_8"))));

    // PlayerRoll
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_Main"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_1"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_2"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_3"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_4"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_5"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_6"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_7"))));
    SubWidgetPlayerRoles.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerRole_8"))));

    // PlayerReady
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_Main"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_1"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_2"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_3"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_4"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_5"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_6"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_7"))));
    SubWidgetPlayerReadyStates.Add(Cast<UTHWidgetInGameUserStateSub>(GetWidgetFromName(TEXT("BP_Widget_InGame_PlayerReadyState_8"))));

    return true;
}

void UTHWidgetInGameUserState::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    // 테이블 자리별 Player 상태 표시를 위한 TableSeattingPos 체크
    if (ATHPlayerController* LocalPlayerController = Cast<ATHPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        // 로컬(Player0) 테이블 포지션
        if (ATHPlayerState* LocalTHPlayerState = LocalPlayerController->GetPlayerState())
        {
            int32 LocalPlayerTableSeattingPos = LocalTHPlayerState->GetTableSeattingPos();
            //Debug_
            //UE_LOG(LogTemp, Log, TEXT("Player:%s"), *LocalPlayerController->GetPlayerState()->GetPlayerNickName());

            // 전체 플레이어 스테이트 확인
            for (APlayerState* OtherPlayerState : LocalPlayerController->GetGameState()->PlayerArray)
            {
                if (ATHPlayerState* THPlayerState = Cast<ATHPlayerState>(OtherPlayerState))
                {
                    // 플레이어 테이블 포지션
                    int32 TableSeattingPos = THPlayerState->GetTableSeattingPos();

                    //Debug_
                    //UE_LOG(LogTemp, Log, TEXT("linked Name:%s TablePos:%d"),
                    //    *OtherPlayerState->GetName(), TableSeattingPos);

                    // 현재 플레이어의 자리를 메인 포지션으로 설정하므로 
                    // 시계방향으로 붙어있는 플레이어 상태를 UI에 표시하기 위한 UI인덱스 설정
                    int32 ResultTableSeattingPos = -1;
                    if (LocalPlayerTableSeattingPos > TableSeattingPos)
                    {
                        ResultTableSeattingPos = MaxPlayerCount - (LocalPlayerTableSeattingPos - TableSeattingPos);
                    }
                    else
                    {
                        ResultTableSeattingPos = TableSeattingPos - LocalPlayerTableSeattingPos;
                    }

                    SubWidgetUserStates[ResultTableSeattingPos]->SetTHPlayerState(THPlayerState);
                    SubWidgetUserActionStates[ResultTableSeattingPos]->SetTHPlayerState(THPlayerState);
                    SubWidgetUserBettingMoneys[ResultTableSeattingPos]->SetTHPlayerState(THPlayerState);
                    SubWidgetPlayerRoles[ResultTableSeattingPos]->SetTHPlayerState(THPlayerState);
                    SubWidgetPlayerReadyStates[ResultTableSeattingPos]->SetTHPlayerState(THPlayerState);
                }
            }
        }
    }
}
