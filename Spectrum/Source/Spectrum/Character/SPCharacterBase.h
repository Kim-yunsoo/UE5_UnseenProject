// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class SPECTRUM_API ASPCharacterBase : public ACharacter
{
	GENERATED_BODY()

	public:
	// Sets default values for this character's properties
	ASPCharacterBase();

protected:
	virtual void SetCharacterControlData(const class USPCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class USPCharacterControlData*> CharacterControlManager;
};
