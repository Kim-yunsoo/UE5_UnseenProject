// Fill out your copyright notice in the Description page of Project Settings.
#include "Potion/SPBlackPotion.h"

#include "SpectrumLog.h"
#include "Component/SPExplosionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


// Sets default values
ASPBlackPotion::ASPBlackPotion()
{
	SphereComponent->SetSphereRadius(35.46f);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PotionMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Spectrum/Assets/Potion/B_Potion/B_Potion.B_Potion'"));
	if (PotionMeshRef.Object)
	{
		PotionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackPotionMesh"));
		PotionMesh->SetStaticMesh(PotionMeshRef.Object);
		PotionMesh->SetupAttachment(SphereComponent);
		PotionMesh->SetRelativeLocation(FVector(2.98f, 0.74f, -20.10f));
		PotionMesh->SetRelativeScale3D(FVector(1.84f, 1.18f, 1.74f));
		PotionMesh->SetCollisionProfileName(TEXT("NoCollision"));
	}
	ExplosionComponent = CreateDefaultSubobject<USPExplosionComponent>(TEXT("ExplosionComponent"));
	WaterSound = LoadObject<USoundWave>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Spectrum/Sound/Water2.Water2'"));
	CrushSound = LoadObject<USoundWave>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Spectrum/Sound/Crush.Crush'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitRef(
TEXT("/Script/Engine.ParticleSystem'/Game/MagicProjectilesVol2/Particles/Hits/CP_BlackPotion.CP_BlackPotion'"));

	if (HitRef.Succeeded())
	{
		EmitterHit = HitRef.Object;
	}
}

// Called when the game starts or when spawned
void ASPBlackPotion::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ASPBlackPotion::HandleActorHit);
	if(HasAuthority())
	{
		this->SetReplicates(true);
		this->AActor::SetReplicateMovement(true);
		ExplosionComponent->SetIsReplicated(true);
	}
}

void ASPBlackPotion::HandleActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	ClientRPCSound();
	FVector HitLocation = Hit.ImpactPoint;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterHit, HitLocation, FRotator::ZeroRotator,
												 FVector(1.0f), true, EPSCPoolMethod::None, true);
	ExplosionComponent->Explode();
	this->SetLifeSpan(0.1f);
	
}

void ASPBlackPotion::MultiRPCExplosion_Implementation()
{
	ExplosionComponent->Explode();
	this->SetLifeSpan(0.1f);
}

void ASPBlackPotion::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ASPBlackPotion::ClientRPCSound_Implementation()
{
	//SP_SUBLOG(LogTemp, Warning, TEXT("ClientRPCSound_Implementation"));
	UGameplayStatics::PlaySound2D(GetWorld(), WaterSound);
	UGameplayStatics::PlaySound2D(GetWorld(), CrushSound);
}



