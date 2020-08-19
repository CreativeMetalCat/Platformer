// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedSpawnPoint.h"

// Sets default values
AAdvancedSpawnPoint::AAdvancedSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EditorBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorBillboard"));
	SetRootComponent(EditorBillboard);
	EditorBillboard->bHiddenInGame = true;
}

// Called when the game starts or when spawned
void AAdvancedSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdvancedSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

