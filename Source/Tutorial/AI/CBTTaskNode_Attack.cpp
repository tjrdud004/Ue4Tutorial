// Fill out your copyright notice in the Description page of Project Settings.
#include "CBTTaskNode_Attack.h"
#include "Enemy/CEnemy.h"
#include "AI/CAIController.h"



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

	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == NULL)
		return;

	if (IsAttack == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
