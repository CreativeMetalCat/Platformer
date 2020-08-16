// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Platformer/PlatformerGameInstance.h"
#include "RoomType.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bEnabled = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName LevelTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ERoomType RoomType = ERoomType::ERT_Default;

    UFUNCTION(BlueprintCallable)
        void SaveRoomState();

    UFUNCTION(BlueprintCallable)
        void DisableAllActorsInLevel();

    UFUNCTION(BlueprintCallable)
        void EnableAllActorsInLevel();

    UFUNCTION(BlueprintCallable)
        void SetLevelTag(FName tag);

    //set id used by wave manager
    UFUNCTION(BlueprintCallable)
        void SetLevelsOrderId(int id);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
        void Init();

    void Init_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
        void SetIsEnabled(bool Enabled);

    void SetIsEnabled_Implementation(bool Enabled);

    virtual void BeginPlay()override;

};
