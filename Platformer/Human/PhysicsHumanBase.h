// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"
#include "Platformer/Dungeon/DungeonSystemInterface.h"
#include "PhysicsHumanBase.generated.h"

UCLASS()
class PLATFORMER_API APhysicsHumanBase : public ACharacter, public IAISightTargetInterface,public IDungeonSystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APhysicsHumanBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DisabledActorUpdateTimerHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bones)
		TArray<FName>HeadBones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dungeon)
	FVector LastPosition;

	UFUNCTION(BlueprintPure)
		bool GetIsBoneOnTheHead(FName BoneName);

	/*Mesh that is used to check if player is visible*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = AIVisibility)
		/*Mesh that is used to check if player is visible*/
		USkeletalMeshComponent* GetBodyMesh()const;

	USkeletalMeshComponent* GetBodyMesh_Implementation()const { return GetMesh(); }

	//tick function in low consumption mode
	void DisabledActorUpdate();
	
	void DisableActor_Implementation() override;

	void EnableActor_Implementation() override;
	
	virtual bool CanBeSeenFrom(
		const FVector& ObserverLocation,
		FVector& OutSeenLocation,
		int32& NumberOfLoSChecksPerformed,
		float& OutSightStrength,
		const AActor* IgnoreActor = NULL
	) const;

};
