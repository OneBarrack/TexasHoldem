// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// TexasHold`em's Rules
const int MinPlayerCount = 2;
const int MaxPlayerCount = 9;

const int NumOfAllCards = 52;
const int NumOfCardsForSuit = 13;
const int NumOfCardsForPlayer = 2;
const int MaxNumOfCommunityCards = 5;

const int MaxRoleCount = 3;

const int MinAceNumber = 1;
const int MaxAceNumber = 14;

const int FirstBlindBettingMoney = 200;
const float IncreaseRateForBlindBettingMoney = 2.0f;

const int StartPlayerMoney = 10000;

// Showdown 이후 FinishiUp 넘어가기까지 대기시간 타이머
const float FinishDelegateTimerDelay = 10.0f;
