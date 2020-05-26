// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_Parry.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"



void UCAnimNotifyState_Parry::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == NULL) return;
	
	//���⼭ ���� �浹�˻縦 �����Ѵ�.
	//���⼭ �÷��̾��� ���� �浹ü�� ���ְ�.


}

void UCAnimNotifyState_Parry::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	//���࿡ ���⼭ �浹�̵Ǹ�.
	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//if (player == NULL) return; // �׳� ������ ������ �����Ű��.
	//
	//player->ResetAttack();

}

void UCAnimNotifyState_Parry::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{

	Super::NotifyEnd(MeshComp,Animation);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == NULL) return;

	//���⼭ �÷��̾��� ���� �浹�� ���ش�.
	//
	player->ResetAttack();
	
}
