// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"

#include "EnhancedInputComponent.h"
#include "UI/SPHUDWidget.h"
#include "SPGameModeBase.h"
#include "UI/ReturnMain/SPReturnToMainMenu.h"

ASPPlayerController::ASPPlayerController()
{
   static ConstructorHelpers::FClassFinder<USPHUDWidget> SPHUDWidgetRef(TEXT("/Game/Spectrum/UMG/WBP_SPHUD.WBP_SPHUD_C"));
   if (SPHUDWidgetRef.Class)
   {
      SPHUDWidgetClass = SPHUDWidgetRef.Class;
   }

   static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(
      TEXT("/Script/EnhancedInput.InputAction'/Game/Spectrum/Input/Actions/IA_SP_Quit.IA_SP_Quit'"));
   if (nullptr != InputActionJumpRef.Object)
   {
      Quit = InputActionJumpRef.Object;
   }
   bReturnToMainMenuOpen=false;
}

void ASPPlayerController::SetupInputComponent()
{
   Super::SetupInputComponent();

   if(InputComponent ==nullptr) return;

   //InputComponent->BindAction(FName("Quit"), ETriggerEvent::Triggered, this, &ASPPlayerController::ShowReturnToMainMenu);
   if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
   {
      EnhancedInputComponent->BindAction(Quit, ETriggerEvent::Triggered, this, &ASPPlayerController::ShowReturnToMainMenu);
   }
   
}

void ASPPlayerController::OnPossess(APawn* aPawn)
{
   Super::OnPossess(aPawn);
}



void ASPPlayerController::BeginPlay()
{
   Super::BeginPlay();

   FInputModeGameOnly GameOnlyInputMode;
   SetInputMode(GameOnlyInputMode);
   if(IsLocalPlayerController())
   {
      SPHUDWidget = CreateWidget<USPHUDWidget>(this, SPHUDWidgetClass);
      if (SPHUDWidget)
      {
         SPHUDWidget->AddToViewport();
         SPHUDWidget->SetVisibility(ESlateVisibility::Visible);

      }
   }


}

void ASPPlayerController::ShowReturnToMainMenu()
{
   UE_LOG(LogTemp,Log,TEXT("ShowReturnToMainMenu"));
   if(ReturnToMainMenuWidget ==nullptr) return;
   if(ReturnToMainMenu ==nullptr)
   {
      ReturnToMainMenu= CreateWidget<USPReturnToMainMenu>(this, ReturnToMainMenuWidget);  
   }

   if(ReturnToMainMenu)
   {
      bReturnToMainMenuOpen=!bReturnToMainMenuOpen;

      if(bReturnToMainMenuOpen)
      {
         ReturnToMainMenu->MenuSetup();
      }
      else
      {
         ReturnToMainMenu->MenuTearDown();
      }
   }
   
}

void ASPPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
   Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

USPHUDWidget* ASPPlayerController::GetSPHUDWidget() const
{
   return SPHUDWidget;
}

void ASPPlayerController::ClientRCPMathState_Implementation(FName State)
{
   if(State == MatchState::InProgress)
   {
    
      if(SPHUDWidget)
      {
          SPHUDWidget->HideLoadingWidget();
      }
      
   }
}


void ASPPlayerController::ClientRPCSpawnUI_Implementation(const int32 Index)
{
   SPHUDWidget->UpdatePotionUI(Index);
}

