// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "Dungeon/DungeonData.h"
#include "PlatformerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API UPlatformerGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
        TArray<FDungeonRoomData>Rooms;

    UFUNCTION(BlueprintPure)
        bool IsRoomCompleted(int RoomId);

    UFUNCTION(BlueprintCallable)
        void MarkRoomAsCompleted(int RoomId);

    UFUNCTION(BlueprintCallable)
        void MarkRoomAsEnabled(bool Enabled, int roomId);

    UFUNCTION(BlueprintPure)
        bool GetIsRoomEnabled(int RoomId);

};
