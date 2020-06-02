// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTDecorator_CheckAroundRange.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UCBTDecorator_CheckAroundRange : public UBTDecorator
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		float Range = 500.f;


public:
	UCBTDecorator_CheckAroundRange();


protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
