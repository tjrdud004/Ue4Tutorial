#include "CBTTaskNode_AroundMove.h"
#include "AI/CAIController.h"
#include "Enemy/CEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_AroundMove::UCBTTaskNode_AroundMove()
{
	NodeName = "AroundMove";

	bNotifyTick = true;

}

EBTNodeResult::Type UCBTTaskNode_AroundMove::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	//BT -> AIController -> Pawn = Enemy
	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == NULL)
		return EBTNodeResult::Failed;

	bool IsAround = UKismetMathLibrary::RandomBool();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsAround",IsAround);

	//이러면 안에 안들어가겠지?
	if (IsAround == false)
	{
		//enemy->SetIsTarget(false); 다른데서 풀어줘야함.
		return EBTNodeResult::Succeeded;
	}


	ResetAll();
	enemy->SetIsTarget(true);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_AroundMove::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);

	ACEnemy* enemy = Cast<ACEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == NULL)
		return;

	if (Timer >= RandomTime)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		Timer = 0.f;
	}

	Timer += DeltaSeconds;

	//Target이 만약에 NULL이 될경우 끝내야함.


	//여기에 움직이는 코드를 넣어줘야겠지
	AroundMove(OwnerComp);
	//시간이 다지난경우거나 나머지 추가해줘야할듯.
	


}

void UCBTTaskNode_AroundMove::ResetAll()
{
	RandomTime = UKismetMathLibrary::RandomFloatInRange(3.f, 6.f);
	Timer = 0.f;

	Movement = UKismetMathLibrary::RandomInteger64InRange(0,2);
	
	switch (Movement)
	{
	case 0: Speed = UKismetMathLibrary::RandomFloatInRange(-1.f,-0.5f);
		break;
	case 1: Speed = UKismetMathLibrary::RandomFloatInRange(0.5f,1.f);
		break;
	case 2: Speed = 0;
		break;
	default:
		break;
	}
}

void UCBTTaskNode_AroundMove::AroundMove(UBehaviorTreeComponent& OwnerComp)
{
	ACharacter* enemy = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	ACharacter * target = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));

	if (target == NULL) return;
	
	//ROT
	FVector start = enemy->GetActorLocation();
	FVector end = target->GetActorLocation();

	FRotator findRot = UKismetMathLibrary::FindLookAtRotation(start, end);
	findRot.Pitch = 0.f;
	findRot.Roll = 0.f;
	
	enemy->SetActorRotation(findRot);

	//임시 MOVE
	FRotator controllerRot = FRotator(0.f, enemy->GetControlRotation().Yaw, 0.f);
	FVector controllerRight = UKismetMathLibrary::GetRightVector(controllerRot);
	FVector controllerForward = UKismetMathLibrary::GetForwardVector(controllerRot);

	FVector Temp = enemy->GetActorLocation() + enemy->GetActorRightVector() * (120.f * Speed);

	OwnerComp.GetAIOwner()->MoveToLocation(Temp);

}
