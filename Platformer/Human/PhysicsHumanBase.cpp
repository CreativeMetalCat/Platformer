// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsHumanBase.h"

// Sets default values
APhysicsHumanBase::APhysicsHumanBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APhysicsHumanBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsHumanBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APhysicsHumanBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool APhysicsHumanBase::GetIsBoneOnTheHead(FName BoneName)
{
	if (HeadBones.Num() > 0) 
	{
		for (int i = 0; i < HeadBones.Num(); i++)
		{
			if (HeadBones[i] == BoneName) { return true; }
		}
	}
	return false;
}

bool APhysicsHumanBase::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor) const
{

	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;

	/*Platformer solution uses only a few bones to improve performance, and because we care only about few spots on the human*/
	TArray<FName> sockets;
	sockets.Add(FName("head"));
	sockets.Add(FName("spine_01"));
	sockets.Add(FName("foot_l"));
	sockets.Add(FName("foot_r"));

	FCollisionQueryParams params = FCollisionQueryParams();
	params.AddIgnoredActor(IgnoreActor);

	for (int i = 0; i < sockets.Num(); i++)
	{
		FVector socketLocation;

		if (GetBodyMesh() != nullptr)
		{
			socketLocation = GetBodyMesh()->GetSocketLocation(sockets[i]);
		}
		else
		{
			socketLocation = GetMesh()->GetSocketLocation(sockets[i]);
		}

#ifdef PERCEPTION_TEST
		const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, socketLocation
			, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)) // << Changed this line
			, FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));

#else
		const bool bHitSocket = GetWorld()->LineTraceSingleByChannel(HitResult, ObserverLocation, socketLocation, ECollisionChannel::ECC_Visibility, params);
#endif // PERCEPTION_TEST

		NumberOfLoSChecksPerformed++;

		if (bHitSocket == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this))) {
			OutSeenLocation = socketLocation;
			OutSightStrength = 1;

			return true;
		}

	}

#ifdef PERCEPTION_TEST
	const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation()
		, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)) // << Changed this line
		, FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));

#else

	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ObserverLocation, GetActorLocation(), ECollisionChannel::ECC_Visibility, params);
#endif // PERCEPTION_TEST

	NumberOfLoSChecksPerformed++;

	if (bHit == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
	{
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;

		return true;
	}

	OutSightStrength = 0;
	return false;
}


