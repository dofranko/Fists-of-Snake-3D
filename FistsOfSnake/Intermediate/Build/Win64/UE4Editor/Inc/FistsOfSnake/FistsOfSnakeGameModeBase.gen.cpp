// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FistsOfSnake/FistsOfSnakeGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFistsOfSnakeGameModeBase() {}
// Cross Module References
	FISTSOFSNAKE_API UClass* Z_Construct_UClass_AFistsOfSnakeGameModeBase_NoRegister();
	FISTSOFSNAKE_API UClass* Z_Construct_UClass_AFistsOfSnakeGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_FistsOfSnake();
// End Cross Module References
	void AFistsOfSnakeGameModeBase::StaticRegisterNativesAFistsOfSnakeGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AFistsOfSnakeGameModeBase_NoRegister()
	{
		return AFistsOfSnakeGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_FistsOfSnake,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "FistsOfSnakeGameModeBase.h" },
		{ "ModuleRelativePath", "FistsOfSnakeGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFistsOfSnakeGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics::ClassParams = {
		&AFistsOfSnakeGameModeBase::StaticClass,
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
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFistsOfSnakeGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFistsOfSnakeGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFistsOfSnakeGameModeBase, 1125040637);
	template<> FISTSOFSNAKE_API UClass* StaticClass<AFistsOfSnakeGameModeBase>()
	{
		return AFistsOfSnakeGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFistsOfSnakeGameModeBase(Z_Construct_UClass_AFistsOfSnakeGameModeBase, &AFistsOfSnakeGameModeBase::StaticClass, TEXT("/Script/FistsOfSnake"), TEXT("AFistsOfSnakeGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFistsOfSnakeGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
