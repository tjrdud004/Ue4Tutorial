// Fill out your copyright notice in the Description page of Project Settings.
#include "CBTTaskNode_Attack.h"
#include "Enemy/CEnemy.h"
#include "AI/CAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = L"Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp,NodeMemory);
	//BT -> AIController -> Pawn = Enemy
	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	//if (enemy == NULL)
	//	return EBTNodeResult::Failed;


	IsAttack = true;
	enemy->BeginAttack();
	enemy->OnEndAttack.AddLambda([=]() 
	{
		IsAttack = false;
	});

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);


	//지금 이구문이 필요한지 의문 필요없을듯.
	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == NULL)
		return;

	if (IsAttack == false)
	{
		bool IsAround = UKismetMathLibrary::RandomBool();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsAround",IsAround);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
