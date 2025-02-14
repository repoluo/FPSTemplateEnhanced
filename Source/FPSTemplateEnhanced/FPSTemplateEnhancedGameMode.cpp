// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSTemplateEnhancedGameMode.h"
#include "FPSTemplateEnhancedCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSTemplateEnhancedGameMode::AFPSTemplateEnhancedGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
