// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DungeonSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDungeonSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLATFORMER_API IDungeonSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//fake actor's disable(actor is hidden and tick doesn't happen but another timer based function keeps it's position)
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void DisableActor();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
    void EnableActor();
};
