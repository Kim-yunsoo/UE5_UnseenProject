// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "SPGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SPECTRUM_API ASPGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	ASPGameModeBase();

	virtual void BeginPlay() override;

private:
	TSubclassOf<UUserWidget> SPLobbyWidgetClass;
	class USPLobbyWidget* LobbyWidget;

protected: //Timer

	virtual void PostInitializeComponents() override; //여기서 타이머 가동한다. 
	virtual void DefaultGameTimer(); //타이머로 사용할 함수 
	FTimerHandle GameTimerHandle;
	
	UFUNCTION(Client,Unreliable)
	void ClientRPC();
	


};
