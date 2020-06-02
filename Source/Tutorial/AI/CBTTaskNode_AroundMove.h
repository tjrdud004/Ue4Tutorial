// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_AroundMove.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UCBTTaskNode_AroundMove : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_AroundMove();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	void ResetAll();
	void AroundMove(UBehaviorTreeComponent& OwnerComp);
private:

	//이거를 여기서 정의할게아니라 각각 들고있게만들던지 그래야지.
	float MaxDistance = 400.f;
	float MinDistance = 200.f;
	float RandomTime = 1.f;
	float Timer = 0.f;
	float Speed = 1.f;
	float Scale = 1.f;
	int64 Movement;

	
};
