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

//여기의 Return값으로 Task들의 실행을 결정함.
EBTNodeResult::Type UCBTTaskNode_FindPatrol::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//혹시 나중에 쓸일이 있어서 받는건가? 나중에 좀더 자세하게 알아볼것.
	EBTNodeResult::Type type = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	if(controller == NULL)
		return EBTNodeResult::Failed;

	APawn* pawn = controller->GetPawn();
	if(pawn == NULL)
		return EBTNodeResult::Failed;

	//Editor 모드에서 P로 자동생성 가능한 NavMesh라고 생각하면 될듯.
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(navSystem == NULL)
		return EBTNodeResult::Failed;


	FNavLocation location;
	FVector origin = pawn->GetActorLocation();

	//원형태로 Distance만큼의 거리를 보는것.
	if (navSystem->GetRandomPointInNavigableRadius(origin, Distance, location))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("Patrol", location.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
}
