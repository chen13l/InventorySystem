#include "Player/BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* Context : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(Context, 0);
		}
	}
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
}
