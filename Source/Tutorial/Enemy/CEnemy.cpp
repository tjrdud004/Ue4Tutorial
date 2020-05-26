#include "CEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include "Weapon/CBlackBlade.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "TimerManager.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;

	FString path = L"";
	path = L"AnimMontage'/Game/Character/BlackSword/A_Intermediate_Combo_01_Montage.A_Intermediate_Combo_01_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> attack(*path);
	if (attack.Succeeded())
		AttackMontage = attack.Object;
	path = L"AnimMontage'/Game/Character/Unarm/Hit_Reaction_Montage.Hit_Reaction_Montage'";
	ConstructorHelpers::FObjectFinder<UAnimMontage> hitted(*path);
	if (hitted.Succeeded())
		HittedMontage = hitted.Object;

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	//FString path = L"";
	//ConstructorHelpers::FObjectFinder<ACBlackBlade> blade(*path);

	//if (blade.Succeeded())
	//	BlackBlade = blade.Object;

	Socket = L"BlackBladeSocket";
	HolsterSocket = L"BlackBladeHolsterSocket";

	FTransform transform = FTransform::Identity;
	
	FActorSpawnParameters params;
	params.Owner = this;


	BlackBlade = GetWorld()->SpawnActor(ACBlackBlade::StaticClass(), &transform, params);
	BlackBlade->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), Socket);


}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ACEnemy::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= damage;

	if (Health > 0.f)
	{
		PlayAnimMontage(HittedMontage);
		bCanMove = false;

	}
	else if(bDead == false)
	{
		FRotator rot = DamageCauser->GetActorRotation();
		FVector forward = rot.Quaternion().GetForwardVector();

		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->AddImpulse(forward * GetMesh()->GetMass() * 1000.f);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		
		bCanMove = false;
		bDead = true;

		GetWorldTimerManager().SetTimer(DeadTimerHandle, this, &ACEnemy::Death, 3.f, false);
		
	}

	return damage;
}

void ACEnemy::BeginAttack()
{	
	if(bAttack== true)
	{
		PlayAnimMontage(AttackMontage, 1.0f);
	}
}

void ACEnemy::EndAttack()
{
	if (OnEndAttack.IsBound() == true)
	{
		OnEndAttack.Broadcast();
	}
}

void ACEnemy::HittedEnd()
{
	bCanMove = true;
	EndAttack();
}

void ACEnemy::Death()
{
	GetWorld()->GetTimerManager().ClearTimer(DeadTimerHandle);

	BlackBlade->Destroy();
	Destroy();
}


