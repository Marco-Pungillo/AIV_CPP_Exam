// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamFunctionLibrary.h"

bool UExamFunctionLibrary::GameSave(const AActor* Actor, const FString SlotName, const int32 UserIndex, const FVector Position)
{
	USaveGame* save = UGameplayStatics::CreateSaveGameObject(UExamSaveGame::StaticClass());
	if (save) 
	{
		UExamSaveGame* SaveGameInstance = Cast<UExamSaveGame>(save);
		if (save)
		{
			SaveGameInstance->PlayerData.PlayerLocation = Position;
			SaveGameInstance->PlayerData.PlayerRotation = Actor->GetActorRotation();
			SaveGameInstance->PlayerData.PlayerScale = Actor->GetActorScale();

			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, UserIndex);
			return true;
		}
	}

	return false;
}

bool UExamFunctionLibrary::GameLoad(AActor* Actor, const FString SlotName, const int32 UserIndex)
{
	UExamSaveGame* LoadedSave = Cast<UExamSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (LoadedSave && Actor)
	{
		Actor->SetActorLocation(LoadedSave->PlayerData.PlayerLocation);
		Actor->SetActorRotation(LoadedSave->PlayerData.PlayerRotation);
		Actor->SetActorScale3D(LoadedSave->PlayerData.PlayerScale);
		return true;
	}
	return false;
}
