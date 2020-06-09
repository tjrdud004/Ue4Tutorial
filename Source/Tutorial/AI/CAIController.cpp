// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIController.h"
#include "ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Enemy/CEnemy.h"

ACAIController::ACAIController()
{
	SetGenericTeamId(FGenericTeamId(2));

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 2500.0f;
	Sight->LoseSightRadius = 3000.0f;
	Sight->PeripheralVisionAngleDegrees = 45.0f;
	Sight->SetMaxAge(5.0f);

	//시야 감시대상의 TeamId를 보는것.
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());


	FString path = L"";

	path = L"BlackboardData'/Game/Enemy/AI/BB.BB'";
	ConstructorHelpers::FObjectFinder<UBlackboardData> bb(*path);
	if (bb.Succeeded())
		BB = bb.Object;

	path = L"BehaviorTree'/Game/Enemy/AI/BT.BT'";
	ConstructorHelpers::FObjectFinder<UBehaviorTree> bt(*path);
	if (bt.Succeeded())
		BT = bt.Object;
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	//Blackboard Default
	Blackboard->SetValueAsBool("IsAround", true);

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController::OnSensingTarget);
}

void ACAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BB, Blackboard))
	{
		RunBehaviorTree(BT);
	}
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::OnSensingTarget(AActor * Actor, FAIStimulus Stimulus)
{
	ACEnemy* enemy = Cast<ACEnemy>(GetPawn());

	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject("Target", Actor);
		//이부분이 문제임.
		
		if (enemy != NULL)
		{

			enemy->GetCharacterMovement()->MaxWalkSpeed = 600.f;
			enemy->SetIsTarget(true);
			//->SetIsTarget(true);

		}

	}
	else
	{
		Blackboard->SetValueAsObject("Target", NULL);
		if (enemy != NULL)
		{
			enemy->GetCharacterMovement()->MaxWalkSpeed = 250.f;
		}	enemy->SetIsTarget(false);
	}
}