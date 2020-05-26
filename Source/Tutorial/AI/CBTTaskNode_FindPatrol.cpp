// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTTaskNode_FindPatrol.h"
#include "AI/CAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_FindPatrol::UCBTTaskNode_FindPatrol()
{
	NodeName = "Find Patrol";
}

//������ Return������ Task���� ������ ������.
EBTNodeResult::Type UCBTTaskNode_FindPatrol::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//Ȥ�� ���߿� ������ �־ �޴°ǰ�? ���߿� ���� �ڼ��ϰ� �˾ƺ���.
	EBTNodeResult::Type type = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	if(controller == NULL)
		return EBTNodeResult::Failed;

	APawn* pawn = controller->GetPawn();
	if(pawn == NULL)
		return EBTNodeResult::Failed;

	//Editor ��忡�� P�� �ڵ����� ������ NavMesh��� �����ϸ� �ɵ�.
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(navSystem == NULL)
		return EBTNodeResult::Failed;


	FNavLocation location;
	FVector origin = pawn->GetActorLocation();

	//�����·� Distance��ŭ�� �Ÿ��� ���°�.
	if (navSystem->GetRandomPointInNavigableRadius(origin, Distance, location))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("Patrol", location.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
}
