// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoomBase.h"
#include "Components/BillboardComponent.h"
#include "LevelData.h"
#include "CellData.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Platformer/PlatformerGameInstance.h"
#include "RoomType.h"
#include "DungeonGenerator.generated.h"



UCLASS()
class PLATFORMER_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle StreamedLevelInitTimer;
public:

	int SpawnedShops = 0;

	int SpawnedChests = 0;

	TArray<TArray<AActor*>>StreamedLevelsActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPlatformerGameInstance* gameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBillboardComponent* EditorBillboard;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Amount of room per level*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		int RoomsXAmount = 0;

	/*Amount of levels*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		int RoomsYAmount = 0;

	//corridor lenght
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		float CorridorLenght = 1800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		float RoomSpawnOffset = 950.f;

	//room lenght(constant for all rooms)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		float RoomLenght = 950.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		float MinDistanceBetweenRooms = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Size)
		float MinHeightBetweenRooms = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector StartingPoint = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* StartingPointActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxShopsPerDungeon = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxChestsPerDungeon = 2;

	/*Shops are ChanceOfItemRoomSpawn+5,Chests are ChanceOfItemRoomSpawn+10*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int  ChanceOfItemRoomSpawn = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString>RoomLevelNames;

	//Rooms used as goal for each dungeon
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString>EndRoomLevelNames;

	//Rooms that have shops
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString>ItemLevelNames;

	//if true  no two similar maps will be spawned next to each other
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bNotUseRandomnessCheck = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<ADungeonRoomBase>>CorridorClasses;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ADungeonRoomBase*>Corridors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLevelData>Rooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ULevelStreamingDynamic*>StreamedLevels;

	UFUNCTION(BlueprintCallable)
		void Generate();

	UFUNCTION(BlueprintCallable)
		void InitStreamedLevels();

	bool SpawnRoom(TArray<FString>LevelNames, int LocationX, int LocationY, ERoomType roomType,int id);

};
