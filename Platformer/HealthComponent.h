// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted);

/*
*This Component exists to help unify health info storing between different actors , actual damage calculation is done in actors themselfes
*/
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable)
		FOnHealthDepleted OnHealthDepleted;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnAnyDamage(float Damage,const class UDamageType* DamageType,class AController* InstigatedBy,AActor* DamageCauser);

	void OnAnyDamage_Implementation(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
		void ClampHealth();

	/*returns amount of health that didn't get added due to max health*/
	UFUNCTION(BlueprintCallable)
		/*returns amount of health that didn't get added due to max health*/
		float AddHealth(float amount);

	/*if false MaxHealth will be ignored*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasHealthLimit = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Dead = false;
};
