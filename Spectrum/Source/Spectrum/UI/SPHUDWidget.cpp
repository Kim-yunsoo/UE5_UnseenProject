// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SPHUDWidget.h"

#include "SpectrumLog.h"
#include "SPGameTimeWidget.h"
#include "SPKeyWidget.h"
#include "SPManualWidget.h"
#include "SPScoreWidget.h"
#include "SPSkillWidget.h"
#include "Interface/SPCharacterHUDInterface.h"
#include "Potion/Make/SPMakingPotionWidget.h"
#include "UI/SPTargetUI.h"
#include "UI/Interaction/SPInteractionWidget.h"

class ISPCharacterHUDInterface;

USPHUDWidget::USPHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
void USPHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlowSkillWidget = Cast<USPSkillWidget>(GetWidgetFromName("WBSkill"));
	IceSkillWidget = Cast<USPSkillWidget>(GetWidgetFromName("WBSkill"));
	TeleSkillWidget = Cast<USPSkillWidget>(GetWidgetFromName("WBSkill"));

	ScoreWidget = Cast<USPScoreWidget>(GetWidgetFromName("WBSPScoreWidget"));

	TargetUI = Cast<USPTargetUI>(GetWidgetFromName(TEXT("WBTargetUI")));

	MakingPotionWidget = Cast<USPMakingPotionWidget>(GetWidgetFromName(TEXT("WBPSPMakingPotionWidget")));

	ManualWidget = Cast<USPManualWidget>(GetWidgetFromName(TEXT("WBPManual")));

	//ensure(TargetUI);
	GameTimeWidget= Cast<USPGameTimeWidget>(GetWidgetFromName(TEXT("WBGameTimeWidget")));
	
	//ensure(TargetUI);

	KeyWidget = Cast<USPKeyWidget>(GetWidgetFromName("WBPKey"));
	
	if(InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<USPInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed); 
	}

	ISPCharacterHUDInterface* CharacterWidget = Cast<ISPCharacterHUDInterface>(GetOwningPlayerPawn());
	if(CharacterWidget)
	{
		CharacterWidget->SetupHUDWidget(this);
	}

}



void USPHUDWidget::ToggleMouse()
{
	if(bIsShowMouse)
	{
		const FInputModeGameOnly InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
		GetOwningPlayer()->SetShowMouseCursor(false);
	}
	else
	{
	
		const FInputModeGameAndUI InputMode;
		GetOwningPlayer()->SetInputMode(InputMode);
		GetOwningPlayer()->SetShowMouseCursor(true);
	}
}

void USPHUDWidget::UpdateTime(float CountdownTime)
{
	GameTimeWidget->UpdateTime(CountdownTime);
}

void USPHUDWidget::UpdateSlowCDTime(float NewCurrentTime)
{
	SlowSkillWidget->UpdateSlowBar(NewCurrentTime);
}

void USPHUDWidget::UpdateMakingPotionWidget(bool bIsVisible)
{
	if(bIsVisible)
	{
		if(MakingPotionWidget)
		{
			MakingPotionWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if(MakingPotionWidget)
		{
			MakingPotionWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void USPHUDWidget::UpdateManualWidget(bool bIsVisible)
{
	if(bIsVisible)
	{
		if(ManualWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("aaHAPPY"));
			ManualWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if(ManualWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("HAPPY"));
			ManualWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void USPHUDWidget::UpdateIceCDTime(float NewCurrentTime)
{
	IceSkillWidget->UpdateIceBar(NewCurrentTime);
}

void USPHUDWidget::UpdateTeleCDTime(float NewCurrentTime)
{
	TeleSkillWidget->UpdateTeleBar(NewCurrentTime);
}

void USPHUDWidget::UpdateScore(const ColorType& Mycolor, const int32 Score)
{
	ScoreWidget->UpdateScore(Mycolor,Score);
}

void USPHUDWidget::ShowInteractionWidget()
{
	if(InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void USPHUDWidget::HideInteractionWidget()
{
	if(InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void USPHUDWidget::UpdateInteractionWidget(const FInteractableData* InteractableData)
{
	if(InteractionWidget)
	{
		if(InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}

void USPHUDWidget::ToggleKeyWidget(bool bIsVisible)
{
	if(bIsVisible)
	{
		if(KeyWidget)
		{
			KeyWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if(KeyWidget)
		{
			KeyWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void USPHUDWidget::ClearMakingWieget()
{
	MakingPotionWidget->ClearWidget();
}
	

void USPHUDWidget::MakingPotionWieget(USPItemBase* Item)
{
	MakingPotionWidget->MakingPotion(Item);
}
