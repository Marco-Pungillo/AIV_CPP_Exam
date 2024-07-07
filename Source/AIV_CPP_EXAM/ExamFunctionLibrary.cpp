// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamFunctionLibrary.h"

bool UExamFunctionLibrary::GameSave(AActor* Actor, FString SlotName, int32 UserIndex)
{
	USaveGame* save = UGameplayStatics::CreateSaveGameObject(UExamSaveGame::StaticClass());
	if (save) 
	{
		UExamSaveGame* SaveGameInstance = Cast<UExamSaveGame>(save);
		if (save)
		{
			SaveGameInstance->PlayerLocation = Actor->GetActorLocation();
			SaveGameInstance->PlayerRotation = Actor->GetActorRotation();
			SaveGameInstance->PlayerScale = Actor->GetActorScale();

			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, UserIndex);
			return true;
		}
	}

	return false;
}

bool UExamFunctionLibrary::GameLoad(AActor* Actor, FString SlotName, int32 UserIndex)
{
	UExamSaveGame* LoadedSave = Cast<UExamSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (LoadedSave && Actor)
	{
		Actor->SetActorLocation(LoadedSave->PlayerLocation);
		Actor->SetActorRotation(LoadedSave->PlayerRotation);
		Actor->SetActorScale3D(LoadedSave->PlayerScale);
		return true;
	}
	return false;
}
