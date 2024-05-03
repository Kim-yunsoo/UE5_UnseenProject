// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SPLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPECTRUM_API ASPLobbyGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void PostInitializeComponents() override; //여기서 타이머 가동한다. 
	virtual void DefaultGameTimer(); //타이머로 사용할 함수 
	FTimerHandle GameTimerHandle;
	
};
