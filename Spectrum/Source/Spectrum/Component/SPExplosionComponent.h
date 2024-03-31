// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPExplosionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPECTRUM_API USPExplosionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USPExplosionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void Explode();
protected:
	bool bHasExecutedOnce;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<UParticleSystem> Effect ;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*>ActorArray ;

	float Damage = 200.0f;
};
