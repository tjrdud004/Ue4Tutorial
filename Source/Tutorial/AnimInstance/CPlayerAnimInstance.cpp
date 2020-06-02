// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerAnimInstance.h"
#include "Player/CPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

//#include "ActorComponents/CInverseKinematics.h"

UCPlayerAnimInstance::UCPlayerAnimInstance()
{
}

void UCPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACPlayer* player = Cast<ACPlayer>(TryGetPawnOwner());

	if (player == NULL)
		return;

	UActorComponent* actrorComp = player->GetComponentByClass(UCInverseKinematics::StaticClass());
	//UActorComponent* actrorComp = player->FindComponentByClass<UCInverseKinematics>();
	Foot = Cast<UCInverseKinematics>(actrorComp);
	

}

void UCPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());

	if (character == NULL)
		return;

	Speed = character->GetVelocity().Size();
	bInAir = character->GetCharacterMovement()->IsFalling();
	Direction = CalculateDirection(character->GetVelocity(), character->GetActorRotation());
	
	ACPlayer* player = Cast<ACPlayer>(character);

	if (player == NULL)
		return;

	bDrawing = player->IsDrawing();
	bSheathing = player->IsSheathing(); 
	bRunning = player->IsRunning();

	FRotator normalRot = player->GetNormalizeRotator();
	FRotator AimRot = FRotator(Aim_Pitch,Aim_Yaw,0.f);

	AimRot = UKismetMathLibrary::RInterpTo(AimRot, normalRot, DeltaSeconds, InterpSpeed);

	//180.f 정상작동안함. Epsilon 빼주는게 맞는거같은데 나중에 하자.
	AimRot.Yaw = UKismetMathLibrary::ClampAngle(AimRot.Yaw, -179.f, 179.f);
	AimRot.Pitch = UKismetMathLibrary::ClampAngle(AimRot.Pitch, -90.f, 90.f);

	Aim_Pitch = AimRot.Pitch;
	Aim_Yaw = AimRot.Yaw;

	if (Foot == NULL) return;
	FootIK = Foot->GetIK();
	
	

}
