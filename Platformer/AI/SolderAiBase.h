// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Platformer/Human/PhysicsHumanBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Platformer/AI/Patrol/PatrolSystemBase.h"
#include "SolderAiBase.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API ASolderAiBase : public AAIController
{
	GENERATED_BODY()

protected:
	/*this timer is paused when ai sees enemy*/
	FTimerHandle NewWanderPointSelectionTimer;

	FTimerHandle StopLookingAtNoiseLocationTimerHandle;

	FTimerHandle AlertTimerhandle;
public:

	/*IF ai can not reach WanderPoint in 20 this time new point will be selected*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Wandering)
		float TimeBeforeGivingUpOnPoint = 20.f;

	/*Default enemy class. Ususally Player class*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<APhysicsHumanBase> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		float AlertTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		bool bCanAlwaysSeeEnemy = false;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool bHasSeenEnemy = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Noise)
		AActor* LastNoiseLocationActor = nullptr;

	/*Class of actors that will be used to simplify movement to LastSeenLocation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lost)
		TSubclassOf <AActor>ImportantPointClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		AActor* CurrentEnemy = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		FVector LastSeenLocation;

	/*Additional set of enemies*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TArray<AActor*>Enemies;

	//by default it's false and only changed by WaveManager that spawns it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Patrolling)
		bool bPatrolling = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Patrolling)
		APatrolSystemBase* PatrolSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Patrolling)
		int CurrentPointId = 0;

	/*Behaviour tree used by this ai. Defined in child bps*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BehaviorTree)
		UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blackboard)
		FName TargetFieldName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blackboard)
		FName LastSeenLocationFieldName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blackboard)
		FName WanderingPointFieldName;

	/*Returns true if enemy can be seen*/
	UFUNCTION(BlueprintCallable)
		bool UpdateAI(TArray<AActor*>VisibleActors);

	UFUNCTION(BlueprintCallable)
		void RemoveTarget();

	UFUNCTION(BlueprintCallable)
		void ForceToSeeEnemy(AActor* enemy);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		AActor* GetPointToGoTo();

	AActor* GetPointToGoTo_Implementation();

	UFUNCTION(BlueprintCallable)
		void OnReachedPointOfTravel();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		AActor* GetPointOfWandering();

	AActor* GetPointOfWandering_Implementation() { return nullptr; }

	UFUNCTION(BlueprintCallable)//NoiseLocationActor is ALastNoiseLocation
		void ReactToGunNoise(FVector Location, AActor* NoiseLocationActor);

	UFUNCTION(BlueprintCallable)
		void ForgetAboutNoise();

	UFUNCTION(BlueprintCallable)
		void ResetGiveUpTimer();

	UFUNCTION(BlueprintPure)
		FVector GetClosestPointToLastLocation(bool& Found);

	/*Called when old enemy was lost and new one wasn't found*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnEnemyLost();

	virtual void OnEnemyLost_Implementation() {}

	//when enemy is seen end delay passed
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnAlert();

	void OnAlert_Implementation() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SelectNewWanderPoint();

	virtual void SelectNewWanderPoint_Implementation() {}

	/*Called when new target is found*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnTargetFound();

	virtual void OnTargetFound_Implementation() {}
};
