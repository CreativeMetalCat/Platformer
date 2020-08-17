// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "PatrolSystemBase.generated.h"

UCLASS()
class PLATFORMER_API APatrolSystemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolSystemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBillboardComponent* EditorBillboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*>PatrolNodes;

	UFUNCTION(BlueprintPure)
	int GetAmountOfPoints(){return PatrolNodes.Num();}

	//return point by id or if id is not valid returns nullptr
	UFUNCTION(BlueprintPure)
	AActor*GetPointById(int id );
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
