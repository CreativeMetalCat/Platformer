// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManagerBase.h"
#include "Platformer/HumanInterface.h"
#include "Platformer/HealthComponent.h"
#include "Engine.h"

#define DEBUG

// Sets default values
AWaveManagerBase::AWaveManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManagerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveManagerBase::Update()
{
	if (!WaveIsDone)
	{
		if (Solders.Num() > 0)
		{
			TArray<AActor*>ActorsToRemove;
			for (int i = 0; i < Solders.Num(); i++)
			{
				if (Solders[i]->IsValidLowLevel())
				{
					auto healthComp = Solders[i]->GetComponentByClass(UHealthComponent::StaticClass());
					if (healthComp != nullptr)
					{
						if (Cast<UHealthComponent>(healthComp)->Dead)
						{

							ActorsToRemove.Add(Solders[i]);
						}
					}
				}
				else
				{
					ActorsToRemove.Add(Solders[i]);
				}
			}
			for (int i = 0; i < ActorsToRemove.Num(); i++)
			{
				Solders.Remove(ActorsToRemove[i]);
				if (AmountOfSpawned < TotalAmountToSpawn)
				{
#ifdef DEBUG
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attempring to spawn"));
#endif // DEBUG				
					if (SpawnNewSolder())
					{
						AmountOfSpawned++;

#ifdef DEBUG
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawn Successed"));
#endif // DEBUG		
					}
#ifdef DEBUG
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawn Failed"));
					}
#endif // DEBUG
				}
			}

			if (Solders.Num() > 0 || AmountOfSpawned == TotalAmountToSpawn) { return; }

		}
		if (WaveId != -1)
		{
			OnWaveEnded.Broadcast(WaveId);
			UpdateTimerHanlde.Invalidate();
			ProccessEndOfWave();
			WaveIsDone = true;
		}
	}
}

void AWaveManagerBase::StartNewWave()
{
	if (WaveIdIsValid(WaveId + 1))
	{
		StartWave(WaveId + 1);
		WaveId++;
	}
}

bool AWaveManagerBase::ShouldSpawn(TArray<int> Indicies,int TotalCount,int& TotalCountRes,int&arrayId)
{
	if (Indicies.Num() > 0)
	{
		
		for (int i = 0; i < Indicies.Num(); i++)
		{
			for (int u = 0; u < Indicies[i]; u++)
			{
				TotalCount++;
				if (TotalCount == AmountOfSpawned + 1) 
				{
					arrayId = i;
					TotalCountRes = AmountOfSpawned + 1;
					return true;
				}
			}
		}
	}
	return false;
}

void AWaveManagerBase::StartWave(int NewWaveId)
{
	SpawnNewWaveActors(NewWaveId);
	GetWorld()->GetTimerManager().SetTimer(UpdateTimerHanlde, this, &AWaveManagerBase::Update, 0.1f, true);
	WaveIsDone = false;
}

