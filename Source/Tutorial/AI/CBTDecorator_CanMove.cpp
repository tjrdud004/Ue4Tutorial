#include "CBTDecorator_CanMove.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/CAIController.h"
#include "Enemy/CEnemy.h"

UCBTDecorator_CanMove::UCBTDecorator_CanMove()
{
	NodeName = "Can Move";
}

bool UCBTDecorator_CanMove::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (enemy == NULL)
		return false;

	return enemy->IsCanMove();
}
