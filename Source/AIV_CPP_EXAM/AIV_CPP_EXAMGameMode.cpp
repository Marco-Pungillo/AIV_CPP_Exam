// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIV_CPP_EXAMGameMode.h"
#include "AIV_CPP_EXAMCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIV_CPP_EXAMGameMode::AAIV_CPP_EXAMGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
