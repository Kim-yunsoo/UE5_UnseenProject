// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillActor/SPSkillActorBase.h"
#include "SPTeleSkillActor.generated.h"

/**
 * 
 */
UCLASS()
class SPECTRUM_API ASPTeleSkillActor : public ASPSkillActorBase
{
	GENERATED_BODY()

	ASPTeleSkillActor();

protected:
	UFUNCTION(NetMulticast, Unreliable)
	void MultiRPCTeleSkill(const FHitResult& Hit );
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
						   UPrimitiveComponent* OtherComp, FVector NormalImpulse,
						   const FHitResult& Hit);

};
