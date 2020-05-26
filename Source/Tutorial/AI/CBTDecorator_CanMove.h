// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTDecorator_CanMove.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UCBTDecorator_CanMove : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UCBTDecorator_CanMove();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
