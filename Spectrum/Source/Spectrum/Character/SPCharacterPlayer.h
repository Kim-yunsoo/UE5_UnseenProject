// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SPCharacterBase.h"
#include "InputActionValue.h"
#include "SPCharacterPlayer.generated.h"

/**
 *
 */
UCLASS()
class SPECTRUM_API ASPCharacterPlayer : public ASPCharacterBase
{
	GENERATED_BODY()

	public:
	ASPCharacterPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	// 존재하고 있는지 여부를 알 수 있음


public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected: // 카메라
	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class USPCharacterControlData* CharacterControlData) override;




	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);

	void QuaterMove(const FInputActionValue& Value);

	void SpeedUp(const FInputActionValue& Value);
	void StopSpeedUp(const FInputActionValue& Value);

	void Aiming(const FInputActionValue& Value);
	void StopAiming(const FInputActionValue& Value);

	void Graping(const FInputActionValue& Value);
	void StopGraping(const FInputActionValue& Value);


	ECharacterControlType CurrentCharacterControlType;

protected:
	const float MOVE_PACKET_SEND_DELAY = 0.2f;				// 프레임당 이동 패킷 전송 딜레이
	float MovePacketSendTimer = MOVE_PACKET_SEND_DELAY;

	// 최종적으로 전송할 상태값
	FVector2D DesiredInput;
	FVector DesiredMoveDirection;
	float DesiredYaw;

	FVector2D LastInput; // 이전 프레임의 입력 값을 저장하는 멤버 변수
	float LastMoveTime; // 멤버 변수로 마지막으로 움직인 시간을 기록합니다.

	// 직전 방향값(테스트용)
	FVector2D LastDesiredInput;



	//Camera
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<class UCameraComponent> FollowCamera;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SpeedUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MouseRight;//마우스 오른쪽

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MouseLeft; //마우스 왼쪽

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsAiming : 1; //조준 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsHolding : 1; //잡는지 판단

public:
	const uint8 GetIsAiming() { return bIsAiming; };

};