// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SPCharacterAIInterface.h"
#include "Interface/SPNonCharacterWidgetInterface.h"
#include "Interface/AIInterface/SPDamagableInterface.h"
#include "SPCharacterNonPlayer.generated.h"

class ASPAIController;

UCLASS()
class SPECTRUM_API ASPCharacterNonPlayer : public ACharacter, public ISPNonCharacterWidgetInterface,
                                           public ISPCharacterAIInterface, public ISPDamagableInterface
{
	GENERATED_BODY()

public:
	ASPCharacterNonPlayer();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackMontage;


	void AttackHitCheck();
	void SetDead();
	void PlayDeadAnimation();
	void DamageResponse();
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	float DeadEventDelayTime = 5.0f;

protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	// TObjectPtr<class USPNonCharacterStatComponent> Stat;

	//UI Widget Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USPWidgetComponent> HpBar;

	UPROPERTY()
	TObjectPtr<class USPDamageSystemComponent> DamageSystemComponent;

	UPROPERTY()
	float DefendRadius;
	UPROPERTY()
	float AttackRadius;

	UPROPERTY()
	TObjectPtr<ASPAIController> AIController;

	virtual void SetupCharacterWidget(class USPUserWidget* InUserWidget) override;

	//AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void Attack() override;

	virtual void NotifyComboActionEnd();
	FAICharacterAttackFinished OnAttackFinished;

	// float MaxHealth;
	// float Health;
	// uint8 bIsDead : 1;

public: //interface
	virtual float SetMovementSpeed(const MovementSpeed MoveSpeed) override;
	virtual float GetIdealAttackRange() override;
	virtual float GetIdealDefendRange() override;


	virtual float GetCurrentHealth() override;
	virtual float GetMaxHealth() override;
	virtual float Heal(float Amount) override;
	

	UFUNCTION(BlueprintCallable)
	virtual bool TakeDamage(float Amount, bool ShouldForceInterrupt) override;
	virtual bool IsDead() override;

	virtual void HitResponse();
};
