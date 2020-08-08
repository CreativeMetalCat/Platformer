// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LastNoiseLocation.generated.h"

UCLASS()
class PLATFORMER_API ALastNoiseLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALastNoiseLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBillboardComponent* EditorBillboard;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxRange = 4000.f;

	UFUNCTION(BlueprintCallable)
		void NotifyAi(FVector Location);

};
