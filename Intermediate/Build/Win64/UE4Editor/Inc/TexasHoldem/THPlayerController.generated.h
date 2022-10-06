// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UUserWidget;
struct FPlayerSaveData;
enum class EPlayerAction : uint8;
struct FPlayerActionActivateInfo;
class ATHPlayer;
class ATHPlayerState;
class ATHGameState;
class ATHGameMode;
#ifdef TEXASHOLDEM_THPlayerController_generated_h
#error "THPlayerController.generated.h already included, missing '#pragma once' in THPlayerController.h"
#endif
#define TEXASHOLDEM_THPlayerController_generated_h

#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_SPARSE_DATA
#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_RPC_WRAPPERS \
	virtual void Client_SendNotifyExitGame_Implementation(); \
	virtual void Server_SetPlayerSaveData_Implementation(FPlayerSaveData const& InPlayerSaveData); \
	virtual void Server_SetGamePause_Implementation(bool bPaused); \
	virtual void Server_SendNotifyPlayerAction_Implementation(EPlayerAction const& InPlayerAction, int32 CallMoney, int32 RaiseMoney); \
	virtual void Server_ToggleReservedToExitState_Implementation(); \
 \
	DECLARE_FUNCTION(execChangeHUDWidget); \
	DECLARE_FUNCTION(execClient_SendNotifyExitGame); \
	DECLARE_FUNCTION(execServer_SetPlayerSaveData); \
	DECLARE_FUNCTION(execServer_SetGamePause); \
	DECLARE_FUNCTION(execServer_SendNotifyPlayerAction); \
	DECLARE_FUNCTION(execServer_ToggleReservedToExitState); \
	DECLARE_FUNCTION(execActionFold); \
	DECLARE_FUNCTION(execActionCall); \
	DECLARE_FUNCTION(execActionCheck); \
	DECLARE_FUNCTION(execActionAllin); \
	DECLARE_FUNCTION(execActionRaise); \
	DECLARE_FUNCTION(execActionFull); \
	DECLARE_FUNCTION(execActionHalf); \
	DECLARE_FUNCTION(execActionQuarter); \
	DECLARE_FUNCTION(execToggleReservedToExitState); \
	DECLARE_FUNCTION(execCheckForActionActivate); \
	DECLARE_FUNCTION(execGetPlayerActionActivateInfo); \
	DECLARE_FUNCTION(execSetPlayerSaveData); \
	DECLARE_FUNCTION(execExitGame); \
	DECLARE_FUNCTION(execGetPlayerPawn); \
	DECLARE_FUNCTION(execGetPlayerState); \
	DECLARE_FUNCTION(execGetGameState); \
	DECLARE_FUNCTION(execGetGameMode); \
	DECLARE_FUNCTION(execInit);


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execChangeHUDWidget); \
	DECLARE_FUNCTION(execClient_SendNotifyExitGame); \
	DECLARE_FUNCTION(execServer_SetPlayerSaveData); \
	DECLARE_FUNCTION(execServer_SetGamePause); \
	DECLARE_FUNCTION(execServer_SendNotifyPlayerAction); \
	DECLARE_FUNCTION(execServer_ToggleReservedToExitState); \
	DECLARE_FUNCTION(execActionFold); \
	DECLARE_FUNCTION(execActionCall); \
	DECLARE_FUNCTION(execActionCheck); \
	DECLARE_FUNCTION(execActionAllin); \
	DECLARE_FUNCTION(execActionRaise); \
	DECLARE_FUNCTION(execActionFull); \
	DECLARE_FUNCTION(execActionHalf); \
	DECLARE_FUNCTION(execActionQuarter); \
	DECLARE_FUNCTION(execToggleReservedToExitState); \
	DECLARE_FUNCTION(execCheckForActionActivate); \
	DECLARE_FUNCTION(execGetPlayerActionActivateInfo); \
	DECLARE_FUNCTION(execSetPlayerSaveData); \
	DECLARE_FUNCTION(execExitGame); \
	DECLARE_FUNCTION(execGetPlayerPawn); \
	DECLARE_FUNCTION(execGetPlayerState); \
	DECLARE_FUNCTION(execGetGameState); \
	DECLARE_FUNCTION(execGetGameMode); \
	DECLARE_FUNCTION(execInit);


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_EVENT_PARMS \
	struct THPlayerController_eventServer_SendNotifyPlayerAction_Parms \
	{ \
		EPlayerAction InPlayerAction; \
		int32 CallMoney; \
		int32 RaiseMoney; \
	}; \
	struct THPlayerController_eventServer_SetGamePause_Parms \
	{ \
		bool bPaused; \
	}; \
	struct THPlayerController_eventServer_SetPlayerSaveData_Parms \
	{ \
		FPlayerSaveData InPlayerSaveData; \
	};


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_CALLBACK_WRAPPERS
#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATHPlayerController(); \
	friend struct Z_Construct_UClass_ATHPlayerController_Statics; \
public: \
	DECLARE_CLASS(ATHPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), NO_API) \
	DECLARE_SERIALIZER(ATHPlayerController) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		PlayerActionActivateInfo=NETFIELD_REP_START, \
		NETFIELD_REP_END=PlayerActionActivateInfo	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_INCLASS \
private: \
	static void StaticRegisterNativesATHPlayerController(); \
	friend struct Z_Construct_UClass_ATHPlayerController_Statics; \
public: \
	DECLARE_CLASS(ATHPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TexasHoldem"), NO_API) \
	DECLARE_SERIALIZER(ATHPlayerController) \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		PlayerActionActivateInfo=NETFIELD_REP_START, \
		NETFIELD_REP_END=PlayerActionActivateInfo	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATHPlayerController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATHPlayerController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATHPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATHPlayerController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATHPlayerController(ATHPlayerController&&); \
	NO_API ATHPlayerController(const ATHPlayerController&); \
public:


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATHPlayerController(ATHPlayerController&&); \
	NO_API ATHPlayerController(const ATHPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATHPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATHPlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATHPlayerController)


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__PlayerActionActivateInfo() { return STRUCT_OFFSET(ATHPlayerController, PlayerActionActivateInfo); } \
	FORCEINLINE static uint32 __PPO__CurrentHUDWidget() { return STRUCT_OFFSET(ATHPlayerController, CurrentHUDWidget); } \
	FORCEINLINE static uint32 __PPO__PossessedPlayer() { return STRUCT_OFFSET(ATHPlayerController, PossessedPlayer); }


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_17_PROLOG \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_EVENT_PARMS


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_RPC_WRAPPERS \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_CALLBACK_WRAPPERS \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_INCLASS \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_PRIVATE_PROPERTY_OFFSET \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_SPARSE_DATA \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_CALLBACK_WRAPPERS \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_INCLASS_NO_PURE_DECLS \
	TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TEXASHOLDEM_API UClass* StaticClass<class ATHPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TexasHoldem_Source_TexasHoldem_Controller_THPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
