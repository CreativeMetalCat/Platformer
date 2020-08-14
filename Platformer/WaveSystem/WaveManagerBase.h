// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Platformer/Gamemodes/Gamemodes.h"
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

	TArray<FTimerHandle>SpawnTimers;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle NextWaveTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle TimeIsUpTimerHandle;

	UPROPERTY(BlueprintAssignable)
		FOnWaveEnded OnWaveEnded;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool WaveIsDone = false;

	//tag that will be given to all solders
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName LevelTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		EGameModes Gamemode = EGameModes::EGM_Defaut;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		EDifficultyLevel DifficultyLevel = EDifficultyLevel::EDL_Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Endless)
		TArray<TSubclassOf<AActor>>AllowedSpawnClasses;

	/*How long did it take for player to complete this waves. Only counts actuall wave time*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TakenTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAutoNextWave = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeBetweenWaves = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeBeforeTimeIsUp = 60.f;

	/*How long did it take player to die. Count all time*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TotalTakenTime = 0.f;

	/*How much people did player kill*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TotalScore = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxEnemiesAtOnce = 3;

	/*How much people did player kill*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Score = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*>Solders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle UpdateTimerHanlde;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmountOfSpawned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmountToSpawn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TotalAmountToSpawn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmountOfDeadSolders = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmountOfHeadShots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int WaveId = -1;

	/*For the Endless modes*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TotalWaveCount = 0 ;

	UFUNCTION(BlueprintCallable)
		void Update();

	UFUNCTION(BlueprintCallable)
		void OnTimeIsUp();

	UFUNCTION(BlueprintCallable)
		void StartNewWave();

	UFUNCTION(BlueprintPure)
		bool ShouldSpawn(TArray<int> Indicies, int& TotalCount, int& arrayId);

	UFUNCTION(BlueprintPure)
		int GetHowManySoldersIsLeft();

	//return total wave count for this assest or for entire dungeon, based on gamemod
	UFUNCTION(BlueprintPure)
		int GetTotalWaveCount();

	UFUNCTION(BlueprintCallable)
		void StartWave(int NewWaveId);

	UFUNCTION(BlueprintCallable)
		void StartSpawnTimer(TSubclassOf<AActor>HumanClass, float time);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnEnemyDied();

	void OnEnemyDied_Implementation(){}

	/*This function should not be called directly and exist only to help to connect c++ and bp code*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SpawnHuman(TSubclassOf<AActor>HumanClass);

	void SpawnHuman_Implementation(TSubclassOf<AActor>HumanClass){}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		AActor* GetPlayer();

	AActor* GetPlayer_Implementation() { return nullptr; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void BP_OnTimeIsUp();

	void BP_OnTimeIsUp_Implementation(){}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		int GetTotalAmountOfAvailableWaves();

	int GetTotalAmountOfAvailableWaves_Implementation() { return -1; }

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
