#include "CBTDecorator_CheckAroundRange.h"
#include "AI/CAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTDecorator_CheckAroundRange::UCBTDecorator_CheckAroundRange()
{
	NodeName = "Check Around Range";
}

bool UCBTDecorator_CheckAroundRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	if (controller == NULL) return false;

	APawn* pawn = controller->GetPawn();
	if (pawn == NULL) return false;

	APawn* target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (target == NULL) return false;

	//거리안에 들어왔을때.
	if (target->GetDistanceTo(pawn) <= Range)
		return true;

	//거리밖에있을때.
	return false;
}
