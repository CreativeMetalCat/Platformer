// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RoomType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERoomType : uint8
{
    ERT_Default     UMETA(DisplayName = "Defaut"),
    ERT_Store     UMETA(DisplayName = "Store"),
    ERT_Chest     UMETA(DisplayName = "Chest")
};