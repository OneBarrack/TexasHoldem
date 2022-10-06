// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTexasHoldem_init() {}
	TEXASHOLDEM_API UFunction* Z_Construct_UDelegateFunction_TexasHoldem_OnNotifyRestartGameSignature__DelegateSignature();
	TEXASHOLDEM_API UFunction* Z_Construct_UDelegateFunction_TexasHoldem_OnChangedGamePlayStateSignature__DelegateSignature();
	TEXASHOLDEM_API UFunction* Z_Construct_UDelegateFunction_TexasHoldem_OnChangedCurrentTurnPlayerSignature__DelegateSignature();
	TEXASHOLDEM_API UFunction* Z_Construct_UDelegateFunction_TexasHoldem_OnChangedBettingRoundSignature__DelegateSignature();
	TEXASHOLDEM_API UFunction* Z_Construct_UDelegateFunction_TexasHoldem_OnChangedCommunityCardsSignature__DelegateSignature();
	TEXASHOLDEM_API UFunction* Z_Construct_UDelegateFunction_TexasHoldem_OnChangedPlayersForTableSeattingPosSignature__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_TexasHoldem()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_TexasHoldem_OnNotifyRestartGameSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_TexasHoldem_OnChangedGamePlayStateSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_TexasHoldem_OnChangedCurrentTurnPlayerSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_TexasHoldem_OnChangedBettingRoundSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_TexasHoldem_OnChangedCommunityCardsSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_TexasHoldem_OnChangedPlayersForTableSeattingPosSignature__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/TexasHoldem",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xDF92782B,
				0xCBB1412E,
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
