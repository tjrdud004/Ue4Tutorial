// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_SkillDash.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCAnimNotifyState_SkillDash::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == NULL) return;
	
	player->GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	MoveSpeed = 100.0f;
}

void UCAnimNotifyState_SkillDash::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == NULL) return;

	FRotator rot = player->GetActorRotation();
	rot.Roll = 0;
	rot.Pitch = 0;
	
	player->AddMovementInput(FQuat(rot).GetForwardVector(), MoveSpeed);
	MoveSpeed -= 1.0f;
}

void UCAnimNotifyState_SkillDash::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == NULL) return;
	
	player->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	
}