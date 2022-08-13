// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TexasHoldem/THGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTHGameMode() {}
// Cross Module References
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHGameMode_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_TexasHoldem();
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
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATHGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_TexasHoldem,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHGameMode_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/** GameMode class to specify pawn and playercontroller */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "THGameMode.h" },
		{ "ModuleRelativePath", "THGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "GameMode class to specify pawn and playercontroller" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATHGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATHGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATHGameMode_Statics::ClassParams = {
		&ATHGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
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
	IMPLEMENT_CLASS(ATHGameMode, 2413504809);
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
