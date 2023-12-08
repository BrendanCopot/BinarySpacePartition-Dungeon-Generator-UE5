// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef BSP_BSPGameModeBase_generated_h
#error "BSPGameModeBase.generated.h already included, missing '#pragma once' in BSPGameModeBase.h"
#endif
#define BSP_BSPGameModeBase_generated_h

#define BSP_Source_BSP_BSPGameModeBase_h_15_SPARSE_DATA
#define BSP_Source_BSP_BSPGameModeBase_h_15_RPC_WRAPPERS
#define BSP_Source_BSP_BSPGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define BSP_Source_BSP_BSPGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABSPGameModeBase(); \
	friend struct Z_Construct_UClass_ABSPGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ABSPGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/BSP"), NO_API) \
	DECLARE_SERIALIZER(ABSPGameModeBase)


#define BSP_Source_BSP_BSPGameModeBase_h_15_INCLASS \
private: \
	static void StaticRegisterNativesABSPGameModeBase(); \
	friend struct Z_Construct_UClass_ABSPGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ABSPGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/BSP"), NO_API) \
	DECLARE_SERIALIZER(ABSPGameModeBase)


#define BSP_Source_BSP_BSPGameModeBase_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ABSPGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ABSPGameModeBase) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABSPGameModeBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABSPGameModeBase); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABSPGameModeBase(ABSPGameModeBase&&); \
	NO_API ABSPGameModeBase(const ABSPGameModeBase&); \
public:


#define BSP_Source_BSP_BSPGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ABSPGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABSPGameModeBase(ABSPGameModeBase&&); \
	NO_API ABSPGameModeBase(const ABSPGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABSPGameModeBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABSPGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ABSPGameModeBase)


#define BSP_Source_BSP_BSPGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET
#define BSP_Source_BSP_BSPGameModeBase_h_12_PROLOG
#define BSP_Source_BSP_BSPGameModeBase_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	BSP_Source_BSP_BSPGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	BSP_Source_BSP_BSPGameModeBase_h_15_SPARSE_DATA \
	BSP_Source_BSP_BSPGameModeBase_h_15_RPC_WRAPPERS \
	BSP_Source_BSP_BSPGameModeBase_h_15_INCLASS \
	BSP_Source_BSP_BSPGameModeBase_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define BSP_Source_BSP_BSPGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	BSP_Source_BSP_BSPGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	BSP_Source_BSP_BSPGameModeBase_h_15_SPARSE_DATA \
	BSP_Source_BSP_BSPGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	BSP_Source_BSP_BSPGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	BSP_Source_BSP_BSPGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BSP_API UClass* StaticClass<class ABSPGameModeBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID BSP_Source_BSP_BSPGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
