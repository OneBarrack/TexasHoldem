// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// TexasHold`em's Rules
const int32 MinPlayerCount = 2;
const int32 MaxPlayerCount = 9;

const int32 NumOfAllCards = 52;
const int32 NumOfCardsForSuit = 13;
const int32 NumOfCardsForPlayer = 2;
const int32 MaxNumOfCommunityCards = 5;

const int32 MaxRoleCount = 3;

const int32 MinAceNumber = 1;
const int32 MaxAceNumber = 14;

const int32 FirstBlindBettingMoney = 200;
const float IncreaseRateForBlindBettingMoney = 2.0f;

const int32 StartPlayerMoney = 10000;

const float FinishDelegateTimerDelay = 10.0f; // Showdown 이후 FinishiUp 넘어가기까지 대기시간 타이머
const float RemainBettingTimerDelay = 10.0f; // 플레이어의 베팅 제한시간