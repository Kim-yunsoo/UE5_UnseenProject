// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SPAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/SPCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"


USPAnimInstance::USPAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
	bIsAiming = false;
	bIsHolding = false;
	DeltaY = 0;
	DeltaZ = 0;
}

void USPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	//GetOwningActor() 현재 소유중인 액터정보를 얻을 수 있다. 리턴 타입이 액터라 캐릭터로 형변환
	Owner = Cast<ASPCharacterBase>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void USPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsUping = Movement->IsFlying();
		//if (Owner->IsMyPlayer() == true)
			bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
		//else if (Owner->IsMyPlayer() == false)
		//	bIsJumping = /*bIsFalling | */(Movement->JumpZVelocity > 1.0f);
		bIsAiming = Owner->GetIsAiming();
		if (Owner->IsMyPlayer() == false && bIsAiming == true)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("222222222")));
		else if(Owner->IsMyPlayer() == false && bIsAiming == false)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("333333333")));

		bIsHolding = Owner->GetIsHolding();
		
		FRotator ControlRotation = Owner->GetControlRotation();
		FRotator GetActorRotation = Owner->GetActorRotation();
		FRotator DeltaRotation=UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation, GetActorRotation);

		float  foo = 0.f;

		FRotator NewRotator = UKismetMathLibrary::MakeRotator(0, DeltaY, DeltaZ);

		FRotator RInterp = UKismetMathLibrary::RInterpTo(NewRotator, DeltaRotation, DeltaSeconds, 3);
		UKismetMathLibrary::BreakRotator(RInterp, foo, DeltaY, DeltaZ);

		DeltaY = UKismetMathLibrary::ClampAngle(DeltaY, -90, 90);
		DeltaZ = UKismetMathLibrary::ClampAngle(DeltaZ, -160, 160);

	}
}
