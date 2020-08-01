// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"
#include "PhysicsHumanBase.generated.h"

UCLASS()
class PLATFORMER_API APhysicsHumanBase : public ACharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APhysicsHumanBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/*Mesh that is used to check if player is visible*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = AIVisibility)
		/*Mesh that is used to check if player is visible*/
		USkeletalMeshComponent* GetBodyMesh()const;

	USkeletalMeshComponent* GetBodyMesh_Implementation()const { return GetMesh(); }


	virtual bool CanBeSeenFrom(
		const FVector& ObserverLocation,
		FVector& OutSeenLocation,
		int32& NumberOfLoSChecksPerformed,
		float& OutSightStrength,
		const AActor* IgnoreActor = NULL
	) const;

};
