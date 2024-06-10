// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPECTRUM_API USPAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USPAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void MagicSpell(AActor* Target, FTransform Transform);
	virtual void InitializeComponent() override;
};
