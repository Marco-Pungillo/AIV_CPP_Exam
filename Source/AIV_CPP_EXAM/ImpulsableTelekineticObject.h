// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TelekineticActor.h"
#include "Impulsable.h"
#include "ImpulsableTelekineticObject.generated.h"

/**
 * 
 */
UCLASS()
class AIV_CPP_EXAM_API AImpulsableTelekineticObject : public ATelekineticActor, public IImpulsable
{
	GENERATED_BODY()
	
public:
	virtual void OnReceiveImpulse() override;
};
