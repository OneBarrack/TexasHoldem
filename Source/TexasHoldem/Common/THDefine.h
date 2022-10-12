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

const float FinishDelegateTimerDelay = 10.0f; // Showdown ���� FinishiUp �Ѿ����� ���ð� Ÿ�̸�
const float RemainBettingTimerDelay = 10.0f; // �÷��̾��� ���� ���ѽð�