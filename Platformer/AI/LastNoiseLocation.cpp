// Fill out your copyright notice in the Description page of Project Settings.


#include "LastNoiseLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Platformer/Human/PhysicsHumanBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Platformer/AI/SolderAiBase.h"

// Sets default values
ALastNoiseLocation::ALastNoiseLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EditorBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorBillboard"));
	SetRootComponent(EditorBillboard);
	EditorBillboard->bHiddenInGame = true;
}

// Called when the game starts or when spawned
void ALastNoiseLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALastNoiseLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALastNoiseLocation::NotifyAi(FVector Location)
{
	//this part of code has a lot of comments for the future use of similar functions, so ignore things that look self explanoty but have comments

	SetActorLocation(Location);//just for debug
	TArray<AActor*>AIs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APhysicsHumanBase::StaticClass(), AIs);
	if (AIs.Num() > 0)
	{
		for (int i = 0; i < AIs.Num(); i++)
		{
			if (FVector::Dist(AIs[i]->GetActorLocation(), Location) <= MaxRange)
			{
				//Some heavy casting and looping(not exactly happie with it but it will do)
				//c++ makes everything better, right?
				auto human = Cast<APhysicsHumanBase>(AIs[i]);//have to do that since you can not call GetController() on AActor
				if (human != nullptr)//It is supposed to always be valid, but i don't trust UGameplayStatics::GetAllActorsOfClass returning correct Type and unlike in BP it takes only TArray<AActor*> and any other type
				{
					//cast directly to ASolderAiBase because all enemies have this ai
					auto aiCont = Cast<ASolderAiBase>(human->GetController());//to prevent nulitiple cast calls
					if (aiCont != nullptr)
					{
						aiCont->ReactToGunNoise(Location, this);
					}
				}
			}
		}
	}
}

