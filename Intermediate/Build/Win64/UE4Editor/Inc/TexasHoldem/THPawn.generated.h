// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TEXASHOLDEM_THPawn_generated_h
#error "THPawn.generated.h already included, missing '#pragma once' in THPawn.h"
#endif
#define TEXASHOLDEM_THPawn_generated_h

#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_SPARSE_DATA
#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_RPC_WRAPPERS
#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATHPawn(); \
	friend struct Z_Construct_UClass_ATHPawn_Statics; \
public: \
	DECLARE_CLASS(ATHPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), NO_API) \
	DECLARE_SERIALIZER(ATHPawn)


#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_INCLASS \
private: \
	static void StaticRegisterNativesATHPawn(); \
	friend struct Z_Construct_UClass_ATHPawn_Statics; \
public: \
	DECLARE_CLASS(ATHPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), NO_API) \
	DECLARE_SERIALIZER(ATHPawn)


#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATHPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATHPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATHPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATHPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATHPawn(ATHPawn&&); \
	NO_API ATHPawn(const ATHPawn&); \
public:


#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATHPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATHPawn(ATHPawn&&); \
	NO_API ATHPawn(const ATHPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATHPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATHPawn); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATHPawn)


#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CurrentBlockFocus() { return STRUCT_OFFSET(ATHPawn, CurrentBlockFocus); }


#define TexasHoldem_Source_TexasHoldem_THPawn_h_9_PROLOG
#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_RPC_WRAPPERS \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_INCLASS \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TexasHoldem_Source_TexasHoldem_THPawn_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_INCLASS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_THPawn_h_12_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class THPawn."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TEXASHOLDEM_API UClass* StaticClass<class ATHPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TexasHoldem_Source_TexasHoldem_THPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
