// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Patrol/PatrolSystemBase.h"
#include "AdvancedSpawnPoint.generated.h"

UCLASS()
class PLATFORMER_API AAdvancedSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdvancedSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* EditorBillboard;

	//patrol system that will be given to solder by wave manager
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	APatrolSystemBase*patrol;
};
