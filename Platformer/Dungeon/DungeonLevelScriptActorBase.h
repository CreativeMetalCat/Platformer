// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DungeonLevelScriptActorBase.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API ADungeonLevelScriptActorBase : public ALevelScriptActor
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int RoomId = 0;
};
