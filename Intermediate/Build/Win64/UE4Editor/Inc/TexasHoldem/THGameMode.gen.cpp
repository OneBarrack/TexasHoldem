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
	void ATHGameMode::StaticRegisterNativesATHGameMode()
	{
	}
	UClass* Z_Construct_UClass_ATHGameMode_NoRegister()
	{
		return ATHGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATHGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
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
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WinnerPlayers_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WinnerPlayers_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_WinnerPlayers;
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATHGameMode_Statics::NewProp_WinnerPlayers_Inner = { "WinnerPlayers", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_ATHPlayerState_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::NewProp_WinnerPlayers_MetaData[] = {
		{ "Comment", "// ???? ?\xc3\xb7??\xcc\xbe?\n" },
		{ "ModuleRelativePath", "GameMode/THGameMode.h" },
		{ "ToolTip", "???? ?\xc3\xb7??\xcc\xbe?" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ATHGameMode_Statics::NewProp_WinnerPlayers = { "WinnerPlayers", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ATHGameMode, WinnerPlayers), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ATHGameMode_Statics::NewProp_WinnerPlayers_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATHGameMode_Statics::NewProp_WinnerPlayers_MetaData)) };
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
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHGameMode_Statics::NewProp_WinnerPlayers_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATHGameMode_Statics::NewProp_WinnerPlayers,
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
		nullptr,
		Z_Construct_UClass_ATHGameMode_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
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
	IMPLEMENT_CLASS(ATHGameMode, 2201624709);
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
