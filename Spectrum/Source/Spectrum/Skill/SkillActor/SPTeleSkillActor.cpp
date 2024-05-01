// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillActor/SPTeleSkillActor.h"

#include "Components/BoxComponent.h"
#include "Interface/SPSkillInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

class ISPSkillInterface;

ASPTeleSkillActor::ASPTeleSkillActor()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> VfxRef(TEXT(
"/Script/Engine.ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_ElectricBall01_Yellow.P_Projectile_ElectricBall01_Yellow'"));
	if (VfxRef.Succeeded())
	{
		MainVFX->SetTemplate(VfxRef.Object);
		MainVFX->SetRelativeLocation(FVector(40.0f, 0.0f, 0.0f));
		// MainVFX->SetRelativeRotation(FRotator(0.0f,0.0f,180.f));
		MainVFX->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitRef(
		TEXT("/Script/Engine.ParticleSystem'/Game/MagicProjectilesVol2/Particles/Hits/CP_TeleHit.CP_TeleHit'"));

	if (HitRef.Succeeded())
	{
		EmitterHit = HitRef.Object;
	}
}

void ASPTeleSkillActor::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentHit.AddDynamic(this, &ASPTeleSkillActor::OnBoxCollisionHit);

	if (HasAuthority())
	{
		this->SetReplicates(true);
		this->AActor::SetReplicateMovement(true);
	}
}

void ASPTeleSkillActor::OnBoxCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		MultiRPCTeleSkill(Hit);
		this->SetActorHiddenInGame(true);
		this->SetLifeSpan(0.1f);
	}
}


void ASPTeleSkillActor::MultiRPCTeleSkill_Implementation(const FHitResult& Hit)
{
	FVector HitLocation = Hit.ImpactPoint;
	if(bIsOnce)
	{
		UParticleSystemComponent* Particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterHit, HitLocation, FRotator::ZeroRotator,
												 FVector(1.0f), true, EPSCPoolMethod::None, true);



		bIsOnce=false;
	}
	
	ISPSkillInterface* CheckIceAction = Cast<ISPSkillInterface>(Hit.GetActor());
	if (CheckIceAction)
	{
		CheckIceAction->HitTeleSkillResult();
	}

}
