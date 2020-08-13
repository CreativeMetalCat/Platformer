// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "DungeonData.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FDungeonRoomData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bCompleted = false;

    static FDungeonRoomData CreateRoomData() { return  FDungeonRoomData(); }//placehodler, new parametrs will be added as project goes
};