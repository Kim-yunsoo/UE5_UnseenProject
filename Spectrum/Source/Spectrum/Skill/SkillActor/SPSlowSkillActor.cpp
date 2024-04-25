// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillActor/SPSlowSkillActor.h"

#include "SpectrumLog.h"
#include "Character/SPCharacterMovementComponent.h"
#include "Character/SPCharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/SPSkillInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASPSlowSkillActor::ASPSlowSkillActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Log, TEXT("NO Parm"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollision->SetBoxExtent(FVector(84, 31, 29));
	BoxCollision->SetCollisionProfileName(TEXT("PropCollision"));
	SetRootComponent(BoxCollision); //루트 컴포넌트로 만들기

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	MainVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainVFX"));
	MainVFX->SetupAttachment(BoxCollision);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> GreenVfxRef(TEXT(
		"/Script/Engine.ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/CP_GreenProjectile.CP_GreenProjectile'"));
	if (GreenVfxRef.Succeeded())
	{
		MainVFX->SetTemplate(GreenVfxRef.Object);
		MainVFX->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> GreenHitRef(
		TEXT("/Script/Engine.ParticleSystem'/Game/MagicProjectilesVol2/Particles/Hits/CP_GreenHit.CP_GreenHit'"));

	if (GreenHitRef.Succeeded())
	{
		EmitterHit = GreenHitRef.Object;
	}


	Speed = 1000.f;
	Gravity = 0.0f;
	BoxCollision->SetIsReplicated(true);
	bIsHoming = false;
}

// ASPSlowSkillActor::ASPSlowSkillActor(AActor* TargetPlayer)
// {
// 	UE_LOG(LogTemp,Log,TEXT("Own Parm"));
//
// 	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
// 	BoxCollision->SetBoxExtent(FVector(84, 31, 29));
// 	BoxCollision->SetCollisionProfileName(TEXT("PropCollision"));
// 	SetRootComponent(BoxCollision); //루트 컴포넌트로 만들기
//
// 	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
// 	ProjectileMovement->ProjectileGravityScale = 0.0f;
// 	ProjectileMovement->InitialSpeed = 1500.f;
// 	ProjectileMovement->MaxSpeed = 1500.0f;
// 	ProjectileMovement->bRotationFollowsVelocity=true;
//
// 	MainVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainVFX"));
// 	MainVFX->SetupAttachment(BoxCollision);
// 	static ConstructorHelpers::FObjectFinder<UParticleSystem> GreenVfxRef(TEXT("/Script/Engine.ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/CP_GreenProjectile.CP_GreenProjectile'"));
// 	if(GreenVfxRef.Succeeded())
// 	{
// 		MainVFX->SetTemplate(GreenVfxRef.Object);
// 		MainVFX->SetRelativeLocation(FVector(50.0f,0.0f,0.0f));
// 	}
//
// 	static ConstructorHelpers::FObjectFinder<UParticleSystem> GreenHitRef(TEXT("/Script/Engine.ParticleSystem'/Game/MagicProjectilesVol2/Particles/Hits/CP_GreenHit.CP_GreenHit'"));
//
// 	if(GreenHitRef.Succeeded())
// 	{
// 		EmitterHit=GreenHitRef.Object;
// 	}
// 	
//
// 	Speed=1500.f;
// 	Gravity=0.0f;
//
// }

// void ASPSlowSkillActor::ServerRPCSlowSkill_Implementation(const FHitResult& Hit)
// {
//
// }

void ASPSlowSkillActor::ServerRPCSlowSkill_Implementation(const FHitResult& Hit)
{
	
}

// Called when the game starts or when spawned
void ASPSlowSkillActor::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("Beginplay"));
	Super::BeginPlay();

	this->SetLifeSpan(10.f); // 10초 뒤 사라지도록 함 
	BoxCollision->IgnoreActorWhenMoving(GetOwner(), true);

	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->ProjectileGravityScale = Gravity;
	ProjectileMovement->HomingAccelerationMagnitude = 2000.f;
	//BoxCollision->IgnoreActorWhenMoving(GetOwner(),true);

	BoxCollision->OnComponentHit.AddDynamic(this, &ASPSlowSkillActor::OnBoxCollisionHit);

	if (TargetActor) // 타겟해야할 액터를 찾은 경우 ? 
	{
		RotateToTarget();
		if (bIsHoming)
		{
			ProjectileMovement->bIsHomingProjectile = true;
			ProjectileMovement->HomingTargetComponent = TargetActor->GetRootComponent();
		}
	}

	if (HasAuthority())
	{
		this->SetReplicates(true);
		this->AActor::SetReplicateMovement(true);
	}
}

void ASPSlowSkillActor::OnBoxCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
		// ServerRPCSlowSkill(Hit);
	if(HasAuthority())
	{
		if(GetOwner())
		{
			SP_LOG(LogSPNetwork,Log,TEXT("%s"),*GetOwner()->GetName() );
		}
		SP_LOG(LogSPNetwork, Log, TEXT("OnBoxCollisionHit"));
		// UE_LOG(LogTemp,Log,TEXT("speed %f"),ProjectileMovement->InitialSpeed);
		if(Hit.GetActor())
		{
			SP_LOG(LogSPNetwork,Log,TEXT("YES %s ") ,*Hit.GetActor()->GetName());
		}
		else
		{
			SP_LOG(LogSPNetwork,Log,TEXT("NO"));
			
		}
		FVector HitLocation = Hit.GetActor()->GetActorLocation();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterHit, HitLocation, FRotator::ZeroRotator,
												 FVector(1.0f), true, EPSCPoolMethod::None, true);
		//사운드 코드 넣기
		//느려지게 만들자
		//HitSlowSkillResult
		ISPSkillInterface* CheckSlowAction = Cast<ISPSkillInterface>(Hit.GetActor());
		if (CheckSlowAction)
		{
			CheckSlowAction->HitSlowSkillResult();
		}
		// MultiRPCSlowSkill(Hit.GetActor());
		this->Destroy();
	}

		// ASPCharacterPlayer* testplayer= Cast<ASPCharacterPlayer>(Hit.GetActor());
		// //testplayer->GetMovementComponent();
		// USPCharacterMovementComponent* testcom= Cast<USPCharacterMovementComponent>(testplayer->GetMovementComponent());
		// testcom->Slow();
		// CheckSlowAction->HitSlowSkillResult();	
	
}

void ASPSlowSkillActor::RotateToTarget()
{
	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector MyLocation = GetActorLocation();
	FVector UnitVector = UKismetMathLibrary::GetDirectionUnitVector(MyLocation, TargetLocation);

	ProjectileMovement->Velocity = UnitVector * Speed;
}

void ASPSlowSkillActor::InitTarget(AActor* TargetPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("InitTarget"));
	TargetActor = TargetPlayer;
	bIsHoming = true;
}

void ASPSlowSkillActor::MultiRPCSlowSkill_Implementation(AActor* HitActor)
{
	SP_LOG(LogSPNetwork, Log, TEXT("MultiRPCSlowSkill Point"));

	ISPSkillInterface* CheckSlowAction = Cast<ISPSkillInterface>(HitActor);
	if (CheckSlowAction)
	{
		CheckSlowAction->HitSlowSkillResult();
	}
}
