// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TEXASHOLDEM_THGameMode_generated_h
#error "THGameMode.generated.h already included, missing '#pragma once' in THGameMode.h"
#endif
#define TEXASHOLDEM_THGameMode_generated_h

#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_SPARSE_DATA
#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_RPC_WRAPPERS
#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_RPC_WRAPPERS_NO_PURE_DECLS
#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATHGameMode(); \
	friend struct Z_Construct_UClass_ATHGameMode_Statics; \
public: \
	DECLARE_CLASS(ATHGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), NO_API) \
	DECLARE_SERIALIZER(ATHGameMode)


#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_INCLASS \
private: \
	static void StaticRegisterNativesATHGameMode(); \
	friend struct Z_Construct_UClass_ATHGameMode_Statics; \
public: \
	DECLARE_CLASS(ATHGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), NO_API) \
	DECLARE_SERIALIZER(ATHGameMode)


#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATHGameMode(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATHGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATHGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATHGameMode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATHGameMode(ATHGameMode&&); \
	NO_API ATHGameMode(const ATHGameMode&); \
public:


#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATHGameMode(ATHGameMode&&); \
	NO_API ATHGameMode(const ATHGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATHGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATHGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATHGameMode)


#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__THGameState() { return STRUCT_OFFSET(ATHGameMode, THGameState); } \
	FORCEINLINE static uint32 __PPO__GamePlayManager() { return STRUCT_OFFSET(ATHGameMode, GamePlayManager); }


#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_15_PROLOG
#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_RPC_WRAPPERS \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_INCLASS \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_INCLASS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TEXASHOLDEM_API UClass* StaticClass<class ATHGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TexasHoldem_Source_TexasHoldem_GameMode_THGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
