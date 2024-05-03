// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_ExamGameMode.h"
#include "CPP_ExamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPP_ExamGameMode::ACPP_ExamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
