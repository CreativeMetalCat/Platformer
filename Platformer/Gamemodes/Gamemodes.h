// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "Gamemodes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameModes : uint8
{
    EGM_Defaut     UMETA(DisplayName = "Defaut"),
    EGM_InfiniteEnemies     UMETA(DisplayName = "InfiniteEnemies"),
    EGM_InfiniteWaves     UMETA(DisplayName = "InfiniteWaves"),
    EGM_Money     UMETA(DisplayName = "Money")
};

UENUM(BlueprintType)
enum class EDifficultyLevel :uint8
{
    EDL_Easy  UMETA(DisplayName = "Easy"),
    EDL_Normal  UMETA(DisplayName = "Normal"),
    EDL_Hard UMETA(DisplayName = "Hard")
};