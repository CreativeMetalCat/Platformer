// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "LevelData.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FLevelData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LevelName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Lenght = 1500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Height = 800.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bIsCorridor = false;

};
