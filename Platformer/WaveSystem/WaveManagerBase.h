// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManagerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveEnded, int, WaveId);

UCLASS()
class PLATFORMER_API AWaveManagerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManagerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintAssignable)
		FOnWaveEnded OnWaveEnded;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool WaveIsDone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*>Solders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle UpdateTimerHanlde;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmountOfSpawned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TotalAmountToSpawn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int WaveId = -1;

	UFUNCTION(BlueprintCallable)
		void Update();

	UFUNCTION(BlueprintCallable)
		void StartNewWave();

	UFUNCTION(BlueprintPure)
		bool ShouldSpawn(TArray<int> Indicies, int& TotalCount, int& arrayId);

	UFUNCTION(BlueprintCallable)
		void StartWave(int NewWaveId);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SpawnNewWaveActors(int NewWaveId);

	void SpawnNewWaveActors_Implementation(int NewWaveId) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ProccessEndOfWave();

	void ProccessEndOfWave_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool WaveIdIsValid(int id);

	bool WaveIdIsValid_Implementation(int id) { return false; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool SpawnNewSolder();

	bool SpawnNewSolder_Implementation() { return false; }

};
