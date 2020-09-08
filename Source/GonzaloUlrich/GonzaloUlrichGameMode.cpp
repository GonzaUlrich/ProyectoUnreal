// Copyright Epic Games, Inc. All Rights Reserved.

#include "GonzaloUlrichGameMode.h"
#include "GonzaloUlrichHUD.h"
#include "GonzaloUlrichCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGonzaloUlrichGameMode::AGonzaloUlrichGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGonzaloUlrichHUD::StaticClass();
}
