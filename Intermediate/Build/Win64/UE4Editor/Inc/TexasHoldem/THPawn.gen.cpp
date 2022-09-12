// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TexasHoldem/THPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTHPawn() {}
// Cross Module References
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHPawn_NoRegister();
	TEXASHOLDEM_API UClass* Z_Construct_UClass_ATHPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_TexasHoldem();
// End Cross Module References
	void ATHPawn::StaticRegisterNativesATHPawn()
	{
	}
	UClass* Z_Construct_UClass_ATHPawn_NoRegister()
	{
		return ATHPawn::StaticClass();
	}
	struct Z_Construct_UClass_ATHPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATHPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_TexasHoldem,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATHPawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "THPawn.h" },
		{ "ModuleRelativePath", "THPawn.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATHPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATHPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATHPawn_Statics::ClassParams = {
		&ATHPawn::StaticClass,
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
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATHPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATHPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATHPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATHPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATHPawn, 3590999215);
	template<> TEXASHOLDEM_API UClass* StaticClass<ATHPawn>()
	{
		return ATHPawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATHPawn(Z_Construct_UClass_ATHPawn, &ATHPawn::StaticClass, TEXT("/Script/TexasHoldem"), TEXT("ATHPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATHPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
