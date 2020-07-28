// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnAnyDamage_Implementation(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!Dead)
	{
		Health -= Damage;
		if (Health <= MinHealth)
		{
			Dead = true;
			OnHealthDepleted.Broadcast();
		}
	}
}

void UHealthComponent::ClampHealth()
{
	if (Health > MaxHealth) { Health = MaxHealth; }
	else if (Health < MinHealth) { Health = MinHealth; }
}

float UHealthComponent::AddHealth(float amount)
{
	float temp = 0;
	if (Health + amount > MaxHealth) { temp = Health + amount - MaxHealth; }
	Health += amount;
	ClampHealth();

	return temp;
}

