// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonLevelScriptActorBase.h"
#include "Kismet/GameplayStatics.h"
#include "Platformer/WaveSystem/WaveManagerBase.h"
#include "Engine.h"

void ADungeonLevelScriptActorBase::SaveRoomState()
{
	UPlatformerGameInstance* gameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance != nullptr)
	{
		gameInstance->MarkRoomAsEnabled(bEnabled, RoomId);
		gameInstance->MarkRoomAsCompleted(RoomId);
	}
}

void ADungeonLevelScriptActorBase::DisableAllActorsInLevel()
{
	if (GetWorld() != nullptr)
	{
		TArray<AActor*>LevelActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), LevelTag, LevelActors);
		if (LevelActors.Num() > 0)
		{
			for (int i = 0; i < LevelActors.Num(); i++)
			{
				LevelActors[i]->SetActorHiddenInGame(true);

				LevelActors[i]->SetActorTickEnabled(false);
				
				LevelActors[i]->SetActorEnableCollision(false);
			}
		}
	}
}

void ADungeonLevelScriptActorBase::EnableAllActorsInLevel()
{
	if (GetWorld() != nullptr)
	{
		TArray<AActor*>LevelActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), LevelTag, LevelActors);
		if (LevelActors.Num() > 0)
		{
			for (int i = 0; i < LevelActors.Num(); i++)
			{
				LevelActors[i]->SetActorHiddenInGame(false);
				LevelActors[i]->SetActorTickEnabled(true);
				LevelActors[i]->SetActorEnableCollision(true);
			}
		}
	}
}

void ADungeonLevelScriptActorBase::SetLevelTag(FName tag)
{
	if (GetWorld() != nullptr)
	{
		TArray<AActor*>LevelActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), LevelTag, LevelActors);
		if (LevelActors.Num() > 0)
		{
			for (int i = 0; i < LevelActors.Num(); i++)
			{
				if (LevelActors[i]->Tags.Find(LevelTag) != INDEX_NONE)//better be safe then sorry
				{
					LevelActors[i]->Tags.Remove(LevelTag);
					LevelActors[i]->Tags.Add(tag);
					if (Cast<AWaveManagerBase >(LevelActors[i]) != nullptr)
					{
						Cast<AWaveManagerBase>(LevelActors[i])->RoomId = RoomId;
					}
				}
			}		
			
		}
	}
	LevelTag = tag;
	
}

void ADungeonLevelScriptActorBase::SetLevelsOrderId(int id)
{
	TArray<AActor*>LevelActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), LevelTag, LevelActors);
	if (LevelActors.Num() > 0)
	{
		for (int i = 0; i < LevelActors.Num(); i++)
		{
			if (Cast<AWaveManagerBase >(LevelActors[i]) != nullptr)
			{
				Cast<AWaveManagerBase>(LevelActors[i])->RoomId = id;

			}
		}
	}
}

void ADungeonLevelScriptActorBase::Init_Implementation()
{
}

void ADungeonLevelScriptActorBase::SetIsEnabled_Implementation(bool Enabled)
{
	bEnabled = Enabled;
	SaveRoomState();
}

void  ADungeonLevelScriptActorBase::BeginPlay()
{

	UPlatformerGameInstance* gameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance != nullptr)
	{
		RoomId = gameInstance->CurrentSpawnedLevelId;
		SetLevelTag(FName(FString::FromInt(gameInstance->CurrentSpawnedLevelId)));

		gameInstance->CurrentSpawnedLevelId += 1;

	}
	else
	{
		SetLevelTag(FName(FString::FromInt(FMath::Rand())));
	}
}
