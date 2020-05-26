// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_LookAtTarget.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UCBTTaskNode_LookAtTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_LookAtTarget();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
