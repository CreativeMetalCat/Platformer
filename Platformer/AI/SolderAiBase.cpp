// Fill out your copyright notice in the Description page of Project Settings.


#include "SolderAiBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Platformer/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

bool ASolderAiBase::UpdateAI(TArray<AActor*> VisibleActors)
{
	if (!bCanAlwaysSeeEnemy)
	{
		if (VisibleActors.Num() > 0)
		{
			bool bEnemyCanBeSeen = false;
			bool bHadEnemy = false;
			if (CurrentEnemy != nullptr)
			{
				bHadEnemy = true;
				bool bAlive = false;
				auto HealthComp = CurrentEnemy->GetComponentByClass(UHealthComponent::StaticClass());
				if (HealthComp != nullptr)
				{
					bAlive = !Cast<UHealthComponent>(HealthComp)->Dead;
				}
				if (VisibleActors.Find(CurrentEnemy) != -1 && bAlive)
				{
					bEnemyCanBeSeen = true;
					LastSeenLocation = CurrentEnemy->GetActorLocation();
					return true;
				}
				else
				{
					RemoveTarget();
				}
			}
			if (!bEnemyCanBeSeen)
			{
				for (int i = 0; i < VisibleActors.Num(); i++)
				{
					if (VisibleActors[i]->GetClass()->IsChildOf(EnemyClass) || VisibleActors[i]->GetClass() == EnemyClass)
					{
						auto HealthComp = VisibleActors[i]->GetComponentByClass(UHealthComponent::StaticClass());
						if (HealthComp != nullptr)
						{
							if (!Cast<UHealthComponent>(HealthComp)->Dead)
							{
								SetFocus(VisibleActors[i]);
								CurrentEnemy = VisibleActors[i];
								GetBlackboardComponent()->SetValueAsObject(TargetFieldName, VisibleActors[i]);
								OnTargetFound();
								GetWorldTimerManager().PauseTimer(NewWanderPointSelectionTimer);
								return true;
							}
						}
					}
				}
				if (bHadEnemy) { OnEnemyLost(); }
				GetWorldTimerManager().UnPauseTimer(NewWanderPointSelectionTimer);
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			RemoveTarget();
			OnEnemyLost();
			return false;
		}
	}
	else
	{
		if (VisibleActors.Num() > 0)
		{
			return (VisibleActors.Find(CurrentEnemy)!=-1);
		}
		return false;
	}
}

void ASolderAiBase::RemoveTarget()
{
	if (CurrentEnemy != nullptr)
	{
		LastSeenLocation = CurrentEnemy->GetActorLocation();
		bool Found = false;
		auto loc = GetClosestPointToLastLocation(Found);
		GetBlackboardComponent()->SetValueAsVector(LastSeenLocationFieldName, Found ? CurrentEnemy->GetActorLocation() : loc);
	}
	else
	{
		GetBlackboardComponent()->SetValueAsVector(LastSeenLocationFieldName, LastSeenLocation);
	}
	CurrentEnemy = nullptr;
	GetBlackboardComponent()->ClearValue(TargetFieldName);
	SetFocus(nullptr);
	GetWorldTimerManager().UnPauseTimer(NewWanderPointSelectionTimer);
}

void ASolderAiBase::ForceToSeeEnemy(AActor* enemy)
{
	CurrentEnemy = enemy;
	bCanAlwaysSeeEnemy = true;
	SetFocus(enemy);
	GetBlackboardComponent()->SetValueAsObject(TargetFieldName, enemy);
	OnTargetFound();
	GetWorldTimerManager().PauseTimer(NewWanderPointSelectionTimer);
}

void ASolderAiBase::ReactToGunNoise(FVector Location, AActor* NoiseLocationActor)
{
	if (CurrentEnemy == nullptr)//we don't care about player shooting if we can see it
	{
		bool Found = false;
		FVector Pos = GetClosestPointToLastLocation(Found);
		LastSeenLocation = Found ? Pos : Location;
		if (GetBlackboardComponent() != nullptr)
		{
			GetBlackboardComponent()->SetValueAsVector(LastSeenLocationFieldName, LastSeenLocation);
		}		
		if (NoiseLocationActor != nullptr)
		{
			LastNoiseLocationActor = NoiseLocationActor;
			SetFocus(LastNoiseLocationActor);
			GetWorldTimerManager().SetTimer(StopLookingAtNoiseLocationTimerHandle, this, &ASolderAiBase::ForgetAboutNoise, 10.f);
		}
	}
}

void ASolderAiBase::ForgetAboutNoise()
{
	StopLookingAtNoiseLocationTimerHandle.Invalidate();
	if (GetFocusActor() == LastNoiseLocationActor)
	{
		LastNoiseLocationActor = nullptr;
		SetFocus(nullptr);
	}
}

void ASolderAiBase::ResetGiveUpTimer()
{
	GetWorldTimerManager().SetTimer(NewWanderPointSelectionTimer, this, &ASolderAiBase::SelectNewWanderPoint, TimeBeforeGivingUpOnPoint);
}

FVector ASolderAiBase::GetClosestPointToLastLocation(bool& Found)
{
	TArray<AActor*>Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ImportantPointClass, Actors);
	if (Actors.Num() > 0)
	{
		float ClosestDist = 0;
		int ClosestId = -1;
		for (int i = 0; i < Actors.Num(); i++)
		{
			if (FVector::Distance(Actors[i]->GetActorLocation(), LastSeenLocation) < ClosestDist || ClosestId == -1)
			{
				ClosestDist = FVector::Distance(Actors[i]->GetActorLocation(), LastSeenLocation);
				ClosestId = i;
			}
		}
		if (ClosestId != -1)
		{
			Found = true;
			return Actors[ClosestId]->GetActorLocation();
		}
	}
	Found = false;
	return FVector();
}
