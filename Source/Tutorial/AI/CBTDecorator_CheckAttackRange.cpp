#include "CBTDecorator_CheckAttackRange.h"
#include "AI/CAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTDecorator_CheckAttackRange::UCBTDecorator_CheckAttackRange()
{
	NodeName = "Check Attack Range";
}

bool UCBTDecorator_CheckAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetAIOwner());
	//RetNullResult(controller, false);
	if (controller == NULL) return false;

	APawn* pawn = controller->GetPawn();
	//RetNullResult(pawn, false);a
	if (pawn == NULL) return false;

	APawn* target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	//RetNullResult(target, false);
	if (target == NULL) return false;

	if (target->GetDistanceTo(pawn) <= Range)
		return true;

	return false;
}
