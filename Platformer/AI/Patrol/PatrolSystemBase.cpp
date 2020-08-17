// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolSystemBase.h"

// Sets default values
APatrolSystemBase::APatrolSystemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EditorBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorBillboard"));
	SetRootComponent(EditorBillboard);
	EditorBillboard->bHiddenInGame = true;
}

// Called when the game starts or when spawned
void APatrolSystemBase::BeginPlay()
{
	Super::BeginPlay();
}

AActor* APatrolSystemBase::GetPointById(int id)
{
	if (PatrolNodes.Num() > 0)
	{
		if(PatrolNodes.IsValidIndex(id))
		{
			return PatrolNodes[id];
		}
		return nullptr;
	}
	return nullptr;
}

// Called every frame
void APatrolSystemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

