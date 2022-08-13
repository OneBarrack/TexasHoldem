// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
struct FKey;
#ifdef TEXASHOLDEM_TexasHoldemBlock_generated_h
#error "TexasHoldemBlock.generated.h already included, missing '#pragma once' in TexasHoldemBlock.h"
#endif
#define TEXASHOLDEM_TexasHoldemBlock_generated_h

#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_SPARSE_DATA
#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnFingerPressedBlock); \
	DECLARE_FUNCTION(execBlockClicked);


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnFingerPressedBlock); \
	DECLARE_FUNCTION(execBlockClicked);


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATexasHoldemBlock(); \
	friend struct Z_Construct_UClass_ATexasHoldemBlock_Statics; \
public: \
	DECLARE_CLASS(ATexasHoldemBlock, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), TEXASHOLDEM_API) \
	DECLARE_SERIALIZER(ATexasHoldemBlock)


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_INCLASS \
private: \
	static void StaticRegisterNativesATexasHoldemBlock(); \
	friend struct Z_Construct_UClass_ATexasHoldemBlock_Statics; \
public: \
	DECLARE_CLASS(ATexasHoldemBlock, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), TEXASHOLDEM_API) \
	DECLARE_SERIALIZER(ATexasHoldemBlock)


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	TEXASHOLDEM_API ATexasHoldemBlock(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATexasHoldemBlock) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(TEXASHOLDEM_API, ATexasHoldemBlock); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATexasHoldemBlock); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	TEXASHOLDEM_API ATexasHoldemBlock(ATexasHoldemBlock&&); \
	TEXASHOLDEM_API ATexasHoldemBlock(const ATexasHoldemBlock&); \
public:


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	TEXASHOLDEM_API ATexasHoldemBlock(ATexasHoldemBlock&&); \
	TEXASHOLDEM_API ATexasHoldemBlock(const ATexasHoldemBlock&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(TEXASHOLDEM_API, ATexasHoldemBlock); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATexasHoldemBlock); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATexasHoldemBlock)


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__DummyRoot() { return STRUCT_OFFSET(ATexasHoldemBlock, DummyRoot); } \
	FORCEINLINE static uint32 __PPO__BlockMesh() { return STRUCT_OFFSET(ATexasHoldemBlock, BlockMesh); }


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_10_PROLOG
#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_RPC_WRAPPERS \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_INCLASS \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_INCLASS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TEXASHOLDEM_API UClass* StaticClass<class ATexasHoldemBlock>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TexasHoldem_Source_TexasHoldem_TexasHoldemBlock_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
