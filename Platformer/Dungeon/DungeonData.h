// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "RoomType.h"
#include "DungeonData.generated.h"

/**
 * Struct used to store info anount specific room
 */
USTRUCT(Blueprintable)
struct FDungeonRoomData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bCompleted = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bEnabled = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ERoomType RoomType = ERoomType::ERT_Default;

    static FDungeonRoomData CreateRoomData() { return  FDungeonRoomData(); }//placehodler, new parametrs will be added as project goes
};

/*
Stores info about whole dungeon(such horisontal and vertical size)
*/
USTRUCT(Blueprintable)
struct FDungeonData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int SizeX = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int SizeY = 2;
};
