// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "NavLinkProxyBlueprintBase.generated.h"

/**
 * This class allows to access certain variables that are not accessible otherwise and simplifies some functions
 */
UCLASS()
class PLATFORMER_API ANavLinkProxyBlueprintBase : public ANavLinkProxy
{
	GENERATED_BODY()
public:
    //Get's left point for first Simple nav link item
    UFUNCTION(BlueprintPure)
        //Get's left point for first Simple nav link item
        FVector GetLeftPoint(bool&Exists);

    //Get's left point for first Simple nav link item
    UFUNCTION(BlueprintPure)
        //Get's left point for first Simple nav link item
        FVector GetRightPoint(bool& Exists);

    //Get's left point for first Simple nav link item
    UFUNCTION(BlueprintPure)
        //Get's left point for first Simple nav link item
        FVector GetLeftPointForSpecificLink(int id,bool& Exists);

    //Get's left point for first Simple nav link item
    UFUNCTION(BlueprintPure)
        //Get's left point for first Simple nav link item
        FVector GetRightPointForSpecificLink(int id, bool& Exists);
};
