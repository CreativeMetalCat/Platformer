// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManagerBase.h"
#include "Platformer/HumanInterface.h"
#include "Platformer/HealthComponent.h"
#include "Platformer/ScoreComponent.h"
#include "Engine.h"

//#define DEBUG

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
	if (!PlayerIsDead)
	{
		if (!WaveIsDone)
		{
			TakenTime += DeltaTime;
		}
		TotalTakenTime += DeltaTime;
	}
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
				auto ScoreComp = ActorsToRemove[i]->GetComponentByClass(UScoreComponent::StaticClass());
				if (ScoreComp != nullptr)
				{
					int temp = Cast<UScoreComponent>(ScoreComp)->Score;
					Score += temp;
					TotalScore += temp;
				}
				Solders.Remove(ActorsToRemove[i]);
				if (AmountOfSpawned + AmountToSpawn < TotalAmountToSpawn)
				{
#ifdef DEBUG
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attempring to spawn"));
#endif // DEBUG				
					if (SpawnNewSolder())
					{
						if (AmountToSpawn < 0) { AmountToSpawn = 0; }
						AmountToSpawn++;

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

			if (Solders.Num() > 0 || AmountToSpawn > 0) { return; }

		}
		if (WaveId != -1 && AmountToSpawn <= 0 && AmountOfSpawned == TotalAmountToSpawn)
		{

			OnWaveEnded.Broadcast(WaveId);
			UpdateTimerHanlde.Invalidate();
			ProccessEndOfWave();
			WaveIsDone = true;
			AmountOfSpawned = 0;
			TotalAmountToSpawn = 0;
			Score = 0;
			TakenTime = 0;
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

bool AWaveManagerBase::ShouldSpawn(TArray<int> Indicies,int& TotalCount,int&arrayId)
{
	if (Indicies.Num() > 0)
	{
		TotalCount = 0;
		for (int i = 0; i < Indicies.Num(); i++)
		{
			for (int u = 0; u < Indicies[i]; u++)
			{
				TotalCount++;
				if (TotalCount == AmountOfSpawned + 1) 
				{
#ifdef DEBUG
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("New AI can be spawned!"));
#endif // DEBUG	
					arrayId = i;
					
					return true;
				}
			}
		}
	}
#ifdef DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("New AI can NOT be spawned!"));
#endif // DEBUG	

	arrayId = -1;
	return false;
}

void AWaveManagerBase::StartWave(int NewWaveId)
{
	SpawnNewWaveActors(NewWaveId);
	GetWorld()->GetTimerManager().SetTimer(UpdateTimerHanlde, this, &AWaveManagerBase::Update, 0.1f, true);
	WaveIsDone = false;
}

void AWaveManagerBase::StartSpawnTimer(TSubclassOf<AActor> HumanClass, float time)
{
	FTimerDelegate SpawnDelegate = FTimerDelegate::CreateUObject(this, &AWaveManagerBase::SpawnHuman, HumanClass);
	FTimerHandle handle = FTimerHandle();
	GetWorldTimerManager().SetTimer(handle, SpawnDelegate, time,false);
}
