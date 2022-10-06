// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TexasHoldem/Controller/THPlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTHPlayerController() {}
// Cross Module References
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHPlayerController_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_TexasHoldem();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHGameMode_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHGameState_NoRegister();
	TEXASHOLDEM_API UScriptStruct* Z_Construct_UScriptStruct_FPlayerActionActivateInfo();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHPlayer_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHPlayerState_NoRegister();
	TEXASHOLDEM_API UEnum* Z_Construct_UEnum_TexasHoldem_EPlayerAction();
	TEXASHOLDEM_API UScriptStruct* Z_Construct_UScriptStruct_FPlayerSaveData();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_UTHHoldemPlayManager_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ATHPlayerController::execChangeHUDWidget)
	{
		P_GET_OBJECT(UClass,Z_Param_NewHUDWidgetClass);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ChangeHUDWidget(Z_Param_NewHUDWidgetClass);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execClient_SendNotifyExitGame)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Client_SendNotifyExitGame_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execServer_SetPlayerSaveData)
	{
		P_GET_STRUCT(FPlayerSaveData,Z_Param_InPlayerSaveData);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Server_SetPlayerSaveData_Implementation(Z_Param_InPlayerSaveData);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execServer_SetGamePause)
	{
		P_GET_UBOOL(Z_Param_bPaused);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Server_SetGamePause_Implementation(Z_Param_bPaused);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execServer_SendNotifyPlayerAction)
	{
		P_GET_ENUM(EPlayerAction,Z_Param_InPlayerAction);
		P_GET_PROPERTY(FIntProperty,Z_Param_CallMoney);
		P_GET_PROPERTY(FIntProperty,Z_Param_RaiseMoney);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Server_SendNotifyPlayerAction_Implementation(EPlayerAction(Z_Param_InPlayerAction),Z_Param_CallMoney,Z_Param_RaiseMoney);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execServer_ToggleReservedToExitState)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Server_ToggleReservedToExitState_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionFold)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionFold();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionCall)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionCall();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionCheck)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionCheck();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionAllin)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionAllin();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionRaise)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_RaiseMoney);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionRaise(Z_Param_RaiseMoney);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionFull)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionFull();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionHalf)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionHalf();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execActionQuarter)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ActionQuarter();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execToggleReservedToExitState)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ToggleReservedToExitState();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execCheckForActionActivate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CheckForActionActivate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execGetPlayerActionActivateInfo)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FPlayerActionActivateInfo*)Z_Param__Result=P_THIS->GetPlayerActionActivateInfo();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execSetPlayerSaveData)
	{
		P_GET_STRUCT_REF(FPlayerSaveData,Z_Param_Out_InPlayerSaveData);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetPlayerSaveData(Z_Param_Out_InPlayerSaveData);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execExitGame)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ExitGame();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execGetPlayerPawn)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(ATHPlayer**)Z_Param__Result=P_THIS->GetPlayerPawn();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execGetPlayerState)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(ATHPlayerState**)Z_Param__Result=P_THIS->GetPlayerState();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execGetGameState)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(ATHGameState**)Z_Param__Result=P_THIS->GetGameState();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execGetGameMode)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(ATHGameMode**)Z_Param__Result=P_THIS->GetGameMode();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATHPlayerController::execInit)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Init();
		P_NATIVE_END;
	}
	static FName NAME_ATHPlayerController_BP_ExitGame = FName(TEXT("BP_ExitGame"));
	void ATHPlayerController::BP_ExitGame()
	{
		ProcessEvent(FindFunctionChecked(NAME_ATHPlayerController_BP_ExitGame),NULL);
	}
	static FName NAME_ATHPlayerController_Client_SendNotifyExitGame = FName(TEXT("Client_SendNotifyExitGame"));
	void ATHPlayerController::Client_SendNotifyExitGame()
	{
		ProcessEvent(FindFunctionChecked(NAME_ATHPlayerController_Client_SendNotifyExitGame),NULL);
	}
	static FName NAME_ATHPlayerController_Server_SendNotifyPlayerAction = FName(TEXT("Server_SendNotifyPlayerAction"));
	void ATHPlayerController::Server_SendNotifyPlayerAction(EPlayerAction const& InPlayerAction, int32 CallMoney, int32 RaiseMoney)
	{
		THPlayerController_eventServer_SendNotifyPlayerAction_Parms Parms;
		Parms.InPlayerAction=InPlayerAction;
		Parms.CallMoney=CallMoney;
		Parms.RaiseMoney=RaiseMoney;
		ProcessEvent(FindFunctionChecked(NAME_ATHPlayerController_Server_SendNotifyPlayerAction),&Parms);
	}
	static FName NAME_ATHPlayerController_Server_SetGamePause = FName(TEXT("Server_SetGamePause"));
	void ATHPlayerController::Server_SetGamePause(bool bPaused)
	{
		THPlayerController_eventServer_SetGamePause_Parms Parms;
		Parms.bPaused=bPaused ? true : false;
		ProcessEvent(FindFunctionChecked(NAME_ATHPlayerController_Server_SetGamePause),&Parms);
	}
	static FName NAME_ATHPlayerController_Server_SetPlayerSaveData = FName(TEXT("Server_SetPlayerSaveData"));
	void ATHPlayerController::Server_SetPlayerSaveData(FPlayerSaveData const& InPlayerSaveData)
	{
		THPlayerController_eventServer_SetPlayerSaveData_Parms Parms;
		Parms.InPlayerSaveData=InPlayerSaveData;
		ProcessEvent(FindFunctionChecked(NAME_ATHPlayerController_Server_SetPlayerSaveData),&Parms);
	}
	static FName NAME_ATHPlayerController_Server_ToggleReservedToExitState = FName(TEXT("Server_ToggleReservedToExitState"));
	void ATHPlayerController::Server_ToggleReservedToExitState()
	{
		ProcessEvent(FindFunctionChecked(NAME_ATHPlayerController_Server_ToggleReservedToExitState),NULL);
	}
	void ATHPlayerController::StaticRegisterNativesATHPlayerController()
	{
		UClass* Class = ATHPlayerController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ActionAllin", &ATHPlayerController::execActionAllin },
			{ "ActionCall", &ATHPlayerController::execActionCall },
			{ "ActionCheck", &ATHPlayerController::execActionCheck },
			{ "ActionFold", &ATHPlayerController::execActionFold },
			{ "ActionFull", &ATHPlayerController::execActionFull },
			{ "ActionHalf", &ATHPlayerController::execActionHalf },
			{ "ActionQuarter", &ATHPlayerController::execActionQuarter },
			{ "ActionRaise", &ATHPlayerController::execActionRaise },
			{ "ChangeHUDWidget", &ATHPlayerController::execChangeHUDWidget },
			{ "CheckForActionActivate", &ATHPlayerController::execCheckForActionActivate },
			{ "Client_SendNotifyExitGame", &ATHPlayerController::execClient_SendNotifyExitGame },
			{ "ExitGame", &ATHPlayerController::execExitGame },
			{ "GetGameMode", &ATHPlayerController::execGetGameMode },
			{ "GetGameState", &ATHPlayerController::execGetGameState },
			{ "GetPlayerActionActivateInfo", &ATHPlayerController::execGetPlayerActionActivateInfo },
			{ "GetPlayerPawn", &ATHPlayerController::execGetPlayerPawn },
			{ "GetPlayerState", &ATHPlayerController::execGetPlayerState },
			{ "Init", &ATHPlayerController::execInit },
			{ "Server_SendNotifyPlayerAction", &ATHPlayerController::execServer_SendNotifyPlayerAction },
			{ "Server_SetGamePause", &ATHPlayerController::execServer_SetGamePause },
			{ "Server_SetPlayerSaveData", &ATHPlayerController::execServer_SetPlayerSaveData },
			{ "Server_ToggleReservedToExitState", &ATHPlayerController::execServer_ToggleReservedToExitState },
			{ "SetPlayerSaveData", &ATHPlayerController::execSetPlayerSaveData },
			{ "ToggleReservedToExitState", &ATHPlayerController::execToggleReservedToExitState },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionAllin_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionAllin_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionAllin_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionAllin", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionAllin_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionAllin_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionAllin()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionAllin_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionCall_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionCall_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionCall_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionCall", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionCall_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionCall_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionCall()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionCall_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionCheck_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionCheck_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionCheck_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionCheck", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionCheck_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionCheck_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionCheck()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionCheck_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionFold_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionFold_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionFold_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionFold", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionFold_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionFold_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionFold()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionFold_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionFull_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionFull_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionFull_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionFull", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionFull_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionFull_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionFull()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionFull_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionHalf_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionHalf_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionHalf_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionHalf", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionHalf_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionHalf_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionHalf()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionHalf_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionQuarter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionQuarter_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionQuarter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionQuarter", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionQuarter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionQuarter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionQuarter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionQuarter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics
	{
		struct THPlayerController_eventActionRaise_Parms
		{
			int32 RaiseMoney;
		};
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
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::NewProp_RaiseMoney_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::NewProp_RaiseMoney = { "RaiseMoney", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventActionRaise_Parms, RaiseMoney), METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::NewProp_RaiseMoney_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::NewProp_RaiseMoney_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::NewProp_RaiseMoney,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ActionRaise", nullptr, nullptr, sizeof(THPlayerController_eventActionRaise_Parms), Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ActionRaise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ActionRaise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_BP_ExitGame_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_BP_ExitGame_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_BP_ExitGame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "BP_ExitGame", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_BP_ExitGame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_BP_ExitGame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_BP_ExitGame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_BP_ExitGame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics
	{
		struct THPlayerController_eventChangeHUDWidget_Parms
		{
			TSubclassOf<UUserWidget>  NewHUDWidgetClass;
		};
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_NewHUDWidgetClass;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::NewProp_NewHUDWidgetClass = { "NewHUDWidgetClass", nullptr, (EPropertyFlags)0x0014000000000080, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventChangeHUDWidget_Parms, NewHUDWidgetClass), Z_Construct_UClass_UUserWidget_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::NewProp_NewHUDWidgetClass,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//Debug    \n/////////////////////////\n" },
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
		{ "ToolTip", "Debug\n/" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ChangeHUDWidget", nullptr, nullptr, sizeof(THPlayerController_eventChangeHUDWidget_Parms), Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "CheckForActionActivate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Client\n" },
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
		{ "ToolTip", "Client" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "Client_SendNotifyExitGame", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01040CC1, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ExitGame_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ExitGame_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// ???? ????\n" },
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ExitGame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ExitGame", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ExitGame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ExitGame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ExitGame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ExitGame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics
	{
		struct THPlayerController_eventGetGameMode_Parms
		{
			ATHGameMode* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventGetGameMode_Parms, ReturnValue), Z_Construct_UClass_ATHGameMode_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "GetGameMode", nullptr, nullptr, sizeof(THPlayerController_eventGetGameMode_Parms), Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_GetGameMode()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_GetGameMode_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics
	{
		struct THPlayerController_eventGetGameState_Parms
		{
			ATHGameState* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventGetGameState_Parms, ReturnValue), Z_Construct_UClass_ATHGameState_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "GetGameState", nullptr, nullptr, sizeof(THPlayerController_eventGetGameState_Parms), Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_GetGameState()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_GetGameState_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics
	{
		struct THPlayerController_eventGetPlayerActionActivateInfo_Parms
		{
			FPlayerActionActivateInfo ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000582, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventGetPlayerActionActivateInfo_Parms, ReturnValue), Z_Construct_UScriptStruct_FPlayerActionActivateInfo, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::NewProp_ReturnValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::NewProp_ReturnValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "GetPlayerActionActivateInfo", nullptr, nullptr, sizeof(THPlayerController_eventGetPlayerActionActivateInfo_Parms), Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics
	{
		struct THPlayerController_eventGetPlayerPawn_Parms
		{
			ATHPlayer* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventGetPlayerPawn_Parms, ReturnValue), Z_Construct_UClass_ATHPlayer_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "GetPlayerPawn", nullptr, nullptr, sizeof(THPlayerController_eventGetPlayerPawn_Parms), Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics
	{
		struct THPlayerController_eventGetPlayerState_Parms
		{
			ATHPlayerState* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventGetPlayerState_Parms, ReturnValue), Z_Construct_UClass_ATHPlayerState_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "GetPlayerState", nullptr, nullptr, sizeof(THPlayerController_eventGetPlayerState_Parms), Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_GetPlayerState()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_GetPlayerState_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_Init_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Init_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_Init_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "Init", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Init_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Init_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_Init()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_Init_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics
	{
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_InPlayerAction_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InPlayerAction_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_InPlayerAction;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CallMoney;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RaiseMoney;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_InPlayerAction_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_InPlayerAction_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_InPlayerAction = { "InPlayerAction", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventServer_SendNotifyPlayerAction_Parms, InPlayerAction), Z_Construct_UEnum_TexasHoldem_EPlayerAction, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_InPlayerAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_InPlayerAction_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_CallMoney = { "CallMoney", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventServer_SendNotifyPlayerAction_Parms, CallMoney), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_RaiseMoney = { "RaiseMoney", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventServer_SendNotifyPlayerAction_Parms, RaiseMoney), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_InPlayerAction_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_InPlayerAction,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_CallMoney,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::NewProp_RaiseMoney,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "Server_SendNotifyPlayerAction", nullptr, nullptr, sizeof(THPlayerController_eventServer_SendNotifyPlayerAction_Parms), Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bPaused_MetaData[];
#endif
		static void NewProp_bPaused_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bPaused;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::NewProp_bPaused_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::NewProp_bPaused_SetBit(void* Obj)
	{
		((THPlayerController_eventServer_SetGamePause_Parms*)Obj)->bPaused = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::NewProp_bPaused = { "bPaused", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(THPlayerController_eventServer_SetGamePause_Parms), &Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::NewProp_bPaused_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::NewProp_bPaused_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::NewProp_bPaused_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::NewProp_bPaused,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "Server_SetGamePause", nullptr, nullptr, sizeof(THPlayerController_eventServer_SetGamePause_Parms), Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InPlayerSaveData_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_InPlayerSaveData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData = { "InPlayerSaveData", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventServer_SetPlayerSaveData_Parms, InPlayerSaveData), Z_Construct_UScriptStruct_FPlayerSaveData, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "Server_SetPlayerSaveData", nullptr, nullptr, sizeof(THPlayerController_eventServer_SetPlayerSaveData_Parms), Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04240CC1, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// RPC\n// Server\n" },
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
		{ "ToolTip", "RPC\nServer" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "Server_ToggleReservedToExitState", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00240CC1, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics
	{
		struct THPlayerController_eventSetPlayerSaveData_Parms
		{
			FPlayerSaveData InPlayerSaveData;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InPlayerSaveData_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_InPlayerSaveData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData = { "InPlayerSaveData", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(THPlayerController_eventSetPlayerSaveData_Parms, InPlayerSaveData), Z_Construct_UScriptStruct_FPlayerSaveData, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::NewProp_InPlayerSaveData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "SetPlayerSaveData", nullptr, nullptr, sizeof(THPlayerController_eventSetPlayerSaveData_Parms), Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATHPlayerController, nullptr, "ToggleReservedToExitState", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ATHPlayerController_NoRegister()
	{
		return ATHPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ATHPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GamePlayMgr_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GamePlayMgr;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlayerActionActivateInfo_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_PlayerActionActivateInfo;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentHUDWidget_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CurrentHUDWidget;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PossessedPlayer_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PossessedPlayer;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATHPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_TexasHoldem,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ATHPlayerController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ATHPlayerController_ActionAllin, "ActionAllin" }, // 802000514
		{ &Z_Construct_UFunction_ATHPlayerController_ActionCall, "ActionCall" }, // 1140222149
		{ &Z_Construct_UFunction_ATHPlayerController_ActionCheck, "ActionCheck" }, // 4106053540
		{ &Z_Construct_UFunction_ATHPlayerController_ActionFold, "ActionFold" }, // 1896184152
		{ &Z_Construct_UFunction_ATHPlayerController_ActionFull, "ActionFull" }, // 1126529415
		{ &Z_Construct_UFunction_ATHPlayerController_ActionHalf, "ActionHalf" }, // 608612646
		{ &Z_Construct_UFunction_ATHPlayerController_ActionQuarter, "ActionQuarter" }, // 1857333626
		{ &Z_Construct_UFunction_ATHPlayerController_ActionRaise, "ActionRaise" }, // 300092084
		{ &Z_Construct_UFunction_ATHPlayerController_BP_ExitGame, "BP_ExitGame" }, // 4136695987
		{ &Z_Construct_UFunction_ATHPlayerController_ChangeHUDWidget, "ChangeHUDWidget" }, // 2141488785
		{ &Z_Construct_UFunction_ATHPlayerController_CheckForActionActivate, "CheckForActionActivate" }, // 3379249805
		{ &Z_Construct_UFunction_ATHPlayerController_Client_SendNotifyExitGame, "Client_SendNotifyExitGame" }, // 674685665
		{ &Z_Construct_UFunction_ATHPlayerController_ExitGame, "ExitGame" }, // 3937885386
		{ &Z_Construct_UFunction_ATHPlayerController_GetGameMode, "GetGameMode" }, // 182189808
		{ &Z_Construct_UFunction_ATHPlayerController_GetGameState, "GetGameState" }, // 3277204299
		{ &Z_Construct_UFunction_ATHPlayerController_GetPlayerActionActivateInfo, "GetPlayerActionActivateInfo" }, // 3886625324
		{ &Z_Construct_UFunction_ATHPlayerController_GetPlayerPawn, "GetPlayerPawn" }, // 1342897840
		{ &Z_Construct_UFunction_ATHPlayerController_GetPlayerState, "GetPlayerState" }, // 1398029703
		{ &Z_Construct_UFunction_ATHPlayerController_Init, "Init" }, // 112213339
		{ &Z_Construct_UFunction_ATHPlayerController_Server_SendNotifyPlayerAction, "Server_SendNotifyPlayerAction" }, // 146651320
		{ &Z_Construct_UFunction_ATHPlayerController_Server_SetGamePause, "Server_SetGamePause" }, // 2914146986
		{ &Z_Construct_UFunction_ATHPlayerController_Server_SetPlayerSaveData, "Server_SetPlayerSaveData" }, // 298447646
		{ &Z_Construct_UFunction_ATHPlayerController_Server_ToggleReservedToExitState, "Server_ToggleReservedToExitState" }, // 1937034527
		{ &Z_Construct_UFunction_ATHPlayerController_SetPlayerSaveData, "SetPlayerSaveData" }, // 3051167718
		{ &Z_Construct_UFunction_ATHPlayerController_ToggleReservedToExitState, "ToggleReservedToExitState" }, // 2856900192
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHPlayerController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/** PlayerController class used to enable cursor */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "Controller/THPlayerController.h" },
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
		{ "ToolTip", "PlayerController class used to enable cursor" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHPlayerController_Statics::NewProp_GamePlayMgr_MetaData[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATHPlayerController_Statics::NewProp_GamePlayMgr = { "GamePlayMgr", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHPlayerController, GamePlayMgr), Z_Construct_UClass_UTHHoldemPlayManager_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_GamePlayMgr_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_GamePlayMgr_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PlayerActionActivateInfo_MetaData[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PlayerActionActivateInfo = { "PlayerActionActivateInfo", nullptr, (EPropertyFlags)0x0040000000000020, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHPlayerController, PlayerActionActivateInfo), Z_Construct_UScriptStruct_FPlayerActionActivateInfo, METADATA_PARAMS(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PlayerActionActivateInfo_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PlayerActionActivateInfo_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHPlayerController_Statics::NewProp_CurrentHUDWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATHPlayerController_Statics::NewProp_CurrentHUDWidget = { "CurrentHUDWidget", nullptr, (EPropertyFlags)0x0040000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHPlayerController, CurrentHUDWidget), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_CurrentHUDWidget_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_CurrentHUDWidget_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PossessedPlayer_MetaData[] = {
		{ "ModuleRelativePath", "Controller/THPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PossessedPlayer = { "PossessedPlayer", nullptr, (EPropertyFlags)0x0040000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHPlayerController, PossessedPlayer), Z_Construct_UClass_ATHPlayer_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PossessedPlayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PossessedPlayer_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATHPlayerController_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHPlayerController_Statics::NewProp_GamePlayMgr,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PlayerActionActivateInfo,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHPlayerController_Statics::NewProp_CurrentHUDWidget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHPlayerController_Statics::NewProp_PossessedPlayer,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATHPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATHPlayerController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATHPlayerController_Statics::ClassParams = {
		&ATHPlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ATHPlayerController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ATHPlayerController_Statics::PropPointers),
		0,
		0x008002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATHPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATHPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATHPlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATHPlayerController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATHPlayerController, 2998474199);
	template<> TEXASHOLDEM_API UClass* StaticClass<ATHPlayerController>()
	{
		return ATHPlayerController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATHPlayerController(Z_Construct_UClass_ATHPlayerController, &ATHPlayerController::StaticClass, TEXT("/Script/TexasHoldem"), TEXT("ATHPlayerController"), false, nullptr, nullptr, nullptr);

	void ATHPlayerController::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_PlayerActionActivateInfo(TEXT("PlayerActionActivateInfo"));

		const bool bIsValid = true
			&& Name_PlayerActionActivateInfo == ClassReps[(int32)ENetFields_Private::PlayerActionActivateInfo].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ATHPlayerController"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATHPlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
