// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/CEnemy.h"

UCEnemyAnimInstance::UCEnemyAnimInstance()
{
}

void UCEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UCEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());

	if (character == NULL)
		return;


	Speed = character->GetVelocity().Size();
	Direction = CalculateDirection(character->GetVelocity(),character->GetActorRotation());
	bInAir = character->GetCharacterMovement()->IsFalling();
	
	ACEnemy* enemy = Cast<ACEnemy>(character);
	if (enemy == NULL)
		return;
	
	bTarget = enemy->IsTarget();


}
