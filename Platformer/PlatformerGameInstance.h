// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "Dungeon/DungeonData.h"
#include "Dungeon/CellData.h"
#include "PlatformerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API UPlatformerGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()
public:
    //id used by Streamed levels. Only used during level generation
    int CurrentSpawnedLevelId = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
        TArray<FDungeonRoomData>Rooms;

    //for mini-map generation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
        TArray<FCellData>Corridors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
        FDungeonData DungeonData;

    //-1 if player is not in any room
    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
        int PlayerCurrentRoomId = -1;

    //-1 if player is not in any corridor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
        int PlayerCurrentCorridorId = -1;

    //with each completed room enemies get a little bit stronger
    UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
        int TotalRoomsCompleted = 0;

    UFUNCTION(BlueprintPure)
        bool IsRoomCompleted(int RoomId);

    UFUNCTION(BlueprintCallable)
        void MarkRoomAsCompleted(int RoomId);

    UFUNCTION(BlueprintCallable)
        void MarkRoomAsEnabled(bool Enabled, int roomId);

    UFUNCTION(BlueprintPure)
        bool GetIsRoomEnabled(int RoomId);

};
