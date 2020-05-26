// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTDecorator_CheckAttackRange.generated.h"

UCLASS()
class TUTORIAL_API UCBTDecorator_CheckAttackRange : public UBTDecorator
{	
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Range = 200.0f;
	


public:
	UCBTDecorator_CheckAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
