// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TexasHoldem/GameMode/THGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTHGameMode() {}
// Cross Module References
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHGameMode_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameMode();
	UPackage* Z_Construct_UPackage__Script_TexasHoldem();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHPlayerState_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHGameState_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_UTHHoldemPlayManager_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ATHGameMode::execCheckExitPlayer)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CheckExitPlayer();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHGameMode::execReceiveNotifyPlayerAction)
	{
		P_GET_OBJECT(ATHPlayerState,Z_Param_BettingPlayer);
		P_GET_PROPERTY(FIntProperty,Z_Param_CallMoney);
		P_GET_PROPERTY(FIntProperty,Z_Param_RaiseMoney);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ReceiveNotifyPlayerAction(Z_Param_BettingPlayer,Z_Param_CallMoney,Z_Param_RaiseMoney);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHGameMode::execGiveTurnToPlayer)
	{
		P_GET_OBJECT(ATHPlayerState,Z_Param_BettingPlayer);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GiveTurnToPlayer(Z_Param_BettingPlayer);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHGameMode::execRestartTexasHoldem)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RestartTexasHoldem();
		P_NATIVE_END;
	}
	void ATHGameMode::StaticRegisterNativesATHGameMode()
	{
		UClass* Class = ATHGameMode::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CheckExitPlayer", &ATHGameMode::execCheckExitPlayer },
			{ "GiveTurnToPlayer", &ATHGameMode::execGiveTurnToPlayer },
			{ "ReceiveNotifyPlayerAction", &ATHGameMode::execReceiveNotifyPlayerAction },
			{ "RestartTexasHoldem", &ATHGameMode::execRestartTexasHoldem },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ATHGameMode_CheckExitPlayer_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHGameMode_CheckExitPlayer_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// ?\xce\xb1\xd7\xbe\xc6\xbf? ?????? ?\xc3\xb7??\xcc\xbe? \xc3\xbc\xc5\xa9(?????\xe2\xbf\xb9?? or ?????\xdd\xbe? ????)\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "?\xce\xb1\xd7\xbe\xc6\xbf? ?????? ?\xc3\xb7??\xcc\xbe? \xc3\xbc\xc5\xa9(?????\xe2\xbf\xb9?? or ?????\xdd\xbe? ????)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHGameMode_CheckExitPlayer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHGameMode, nullptr, "CheckExitPlayer", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHGameMode_CheckExitPlayer_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_CheckExitPlayer_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHGameMode_CheckExitPlayer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHGameMode_CheckExitPlayer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics
	{
		struct THGameMode_eventGiveTurnToPlayer_Parms
		{
			ATHPlayerState* BettingPlayer;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BettingPlayer;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::NewProp_BettingPlayer = { "BettingPlayer", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THGameMode_eventGiveTurnToPlayer_Parms, BettingPlayer), Z_Construct_UClass_ATHPlayerState_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::NewProp_BettingPlayer,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? ?? ?\xce\xbf?\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? ?? ?\xce\xbf?" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHGameMode, nullptr, "GiveTurnToPlayer", nullptr, nullptr, sizeof(THGameMode_eventGiveTurnToPlayer_Parms), Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics
	{
		struct THGameMode_eventReceiveNotifyPlayerAction_Parms
		{
			ATHPlayerState* BettingPlayer;
			int32 CallMoney;
			int32 RaiseMoney;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BettingPlayer;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CallMoney_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CallMoney;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RaiseMoney_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RaiseMoney;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_BettingPlayer = { "BettingPlayer", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THGameMode_eventReceiveNotifyPlayerAction_Parms, BettingPlayer), Z_Construct_UClass_ATHPlayerState_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_CallMoney_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_CallMoney = { "CallMoney", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THGameMode_eventReceiveNotifyPlayerAction_Parms, CallMoney), METADATA_PARAMS(Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_CallMoney_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_CallMoney_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_RaiseMoney_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_RaiseMoney = { "RaiseMoney", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THGameMode_eventReceiveNotifyPlayerAction_Parms, RaiseMoney), METADATA_PARAMS(Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_RaiseMoney_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_RaiseMoney_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_BettingPlayer,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_CallMoney,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::NewProp_RaiseMoney,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// ?\xc3\xb7??\xcc\xbe? ?\xd7\xbc\xc7\xbf? ???? ??\xc6\xbc?? ?\xde\xbe? ?????\xcf\xb4? ????\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "?\xc3\xb7??\xcc\xbe? ?\xd7\xbc\xc7\xbf? ???? ??\xc6\xbc?? ?\xde\xbe? ?????\xcf\xb4? ????" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHGameMode, nullptr, "ReceiveNotifyPlayerAction", nullptr, nullptr, sizeof(THGameMode_eventReceiveNotifyPlayerAction_Parms), Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// \xc8\xa6?? ??\xc5\xb8\xc6\xae\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "\xc8\xa6?? ??\xc5\xb8\xc6\xae" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHGameMode, nullptr, "RestartTexasHoldem", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ATHGameMode_NoRegister()
	{
		return ATHGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATHGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsOneOnOneMatch_MetaData[];
#endif
		static void NewProp_bIsOneOnOneMatch_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsOneOnOneMatch;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsBettingRoundEnded_MetaData[];
#endif
		static void NewProp_bIsBettingRoundEnded_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsBettingRoundEnded;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DealerPosForTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DealerPosForTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_THGameState_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_THGameState;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GamePlayManager_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GamePlayManager;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATHGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameMode,
		(UObject* (*)())Z_Construct_UPackage__Script_TexasHoldem,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ATHGameMode_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ATHGameMode_CheckExitPlayer, "CheckExitPlayer" }, // 2958444070
		{ &Z_Construct_UFunction_ATHGameMode_GiveTurnToPlayer, "GiveTurnToPlayer" }, // 3532104938
		{ &Z_Construct_UFunction_ATHGameMode_ReceiveNotifyPlayerAction, "ReceiveNotifyPlayerAction" }, // 1083971832
		{ &Z_Construct_UFunction_ATHGameMode_RestartTexasHoldem, "RestartTexasHoldem" }, // 3197575293
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "GameMode/THGameMode.h" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsOneOnOneMatch_MetaData[] = {
		{ "Comment", "// 2??(1??1) ??\xc4\xa1????\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "2??(1??1) ??\xc4\xa1????" },
	};
#endif
	void Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsOneOnOneMatch_SetBit(void* Obj)
	{
		((ATHGameMode*)Obj)->bIsOneOnOneMatch = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsOneOnOneMatch = { "bIsOneOnOneMatch", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ATHGameMode), &Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsOneOnOneMatch_SetBit, METADATA_PARAMS(Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsOneOnOneMatch_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsOneOnOneMatch_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsBettingRoundEnded_MetaData[] = {
		{ "Comment", "// ???? ?????\xe5\xb0\xa1 ?????\xc7\xbe?????\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "???? ?????\xe5\xb0\xa1 ?????\xc7\xbe?????" },
	};
#endif
	void Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsBettingRoundEnded_SetBit(void* Obj)
	{
		((ATHGameMode*)Obj)->bIsBettingRoundEnded = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsBettingRoundEnded = { "bIsBettingRoundEnded", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ATHGameMode), &Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsBettingRoundEnded_SetBit, METADATA_PARAMS(Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsBettingRoundEnded_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsBettingRoundEnded_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::NewProp_DealerPosForTable_MetaData[] = {
		{ "Comment", "// ???\xcc\xba? ?? Dealer ??????\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "???\xcc\xba? ?? Dealer ??????" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ATHGameMode_Statics::NewProp_DealerPosForTable = { "DealerPosForTable", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHGameMode, DealerPosForTable), METADATA_PARAMS(Z_Construct_UClass_ATHGameMode_Statics::NewProp_DealerPosForTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::NewProp_DealerPosForTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::NewProp_THGameState_MetaData[] = {
		{ "Comment", "// ???\xd3\xbd?????\xc6\xae\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "???\xd3\xbd?????\xc6\xae" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATHGameMode_Statics::NewProp_THGameState = { "THGameState", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHGameMode, THGameState), Z_Construct_UClass_ATHGameState_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATHGameMode_Statics::NewProp_THGameState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::NewProp_THGameState_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::NewProp_GamePlayManager_MetaData[] = {
		{ "Comment", "// ???? ?\xc3\xb7??? ?\xc5\xb4???\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "???? ?\xc3\xb7??? ?\xc5\xb4???" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATHGameMode_Statics::NewProp_GamePlayManager = { "GamePlayManager", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHGameMode, GamePlayManager), Z_Construct_UClass_UTHHoldemPlayManager_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATHGameMode_Statics::NewProp_GamePlayManager_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::NewProp_GamePlayManager_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATHGameMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsOneOnOneMatch,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHGameMode_Statics::NewProp_bIsBettingRoundEnded,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHGameMode_Statics::NewProp_DealerPosForTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHGameMode_Statics::NewProp_THGameState,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHGameMode_Statics::NewProp_GamePlayManager,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATHGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATHGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATHGameMode_Statics::ClassParams = {
		&ATHGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ATHGameMode_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATHGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATHGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATHGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATHGameMode, 3775523020);
	template<> TEXASHOLDEM_API UClass* StaticClass<ATHGameMode>()
	{
		return ATHGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATHGameMode(Z_Construct_UClass_ATHGameMode, &ATHGameMode::StaticClass, TEXT("/Script/TexasHoldem"), TEXT("ATHGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATHGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
