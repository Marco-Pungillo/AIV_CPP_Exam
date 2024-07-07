// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITelekineticObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UITelekineticObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AIV_CPP_EXAM_API IITelekineticObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnObjectHold();
	virtual void OnObjectHoldStop();

	virtual void OnObjectPush();
	virtual void OnObjectPull();
};
