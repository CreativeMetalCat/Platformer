// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoomBase.generated.h"

//Originally made as base for all rooms now only base for corridors
UCLASS()
class PLATFORMER_API ADungeonRoomBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADungeonRoomBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float RoomLenght = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool HasUpWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool HasDownWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool HasRightWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool HasLeftWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsEndOfTheDungeon = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsDeadEnd = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsDrop = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IdOfDropStart = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int IdOfDropEnd = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ADungeonRoomBase* DropStart;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Horizontal lenght*/
	UFUNCTION(BlueprintPure)
		float GetRoomLenght() { return  RoomLenght; }



	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GenerateWalls();

	void GenerateWalls_Implementation() {}

};
