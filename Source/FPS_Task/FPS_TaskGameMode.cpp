// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_TaskGameMode.h"
#include "FPS_TaskHUD.h"
#include "FPS_TaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_TaskGameMode::AFPS_TaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/AlaaTask/MyBlueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPS_TaskHUD::StaticClass();
}
