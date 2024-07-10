// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Impulsable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UImpulsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AIV_CPP_EXAM_API IImpulsable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnReceiveImpulse() const;
};
