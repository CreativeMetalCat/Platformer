// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "Navigation/NavLinkProxyBlueprintBase.h"
#include "JumpNavLinkProxy.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API AJumpNavLinkProxy : public ANavLinkProxyBlueprintBase
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure)
        bool ShouldJump(AActor*agent);
};
