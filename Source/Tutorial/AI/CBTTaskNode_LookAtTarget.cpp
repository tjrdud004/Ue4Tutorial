#include "CBTTaskNode_LookAtTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/CAIController.h"
#include "Kismet/KismetMathLibrary.h"

UCBTTaskNode_LookAtTarget::UCBTTaskNode_LookAtTarget()
{
	NodeName = "Look At Target";
}

EBTNodeResult::Type UCBTTaskNode_LookAtTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	APawn* pawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (pawn == NULL)
		return EBTNodeResult::Failed;
	
	APawn* target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));

	if (target == NULL)
		return EBTNodeResult::Failed;
	FVector start = pawn->GetActorLocation();
	FVector end = target->GetActorLocation();

	start.Z = 0;
	end.Z = 0;

	FRotator rot = UKismetMathLibrary::FindLookAtRotation(start,end );

	pawn->SetActorRotation(rot);

	return EBTNodeResult::Succeeded;
}
