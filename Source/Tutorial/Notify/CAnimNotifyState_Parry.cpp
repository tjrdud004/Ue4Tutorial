// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_Parry.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"



void UCAnimNotifyState_Parry::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == NULL) return;
	
	//여기서 부터 충돌검사를 시작한다.
	//여기서 플레이어의 검의 충돌체를 켜주고.


}

void UCAnimNotifyState_Parry::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	//만약에 여기서 충돌이되면.
	//ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	//if (player == NULL) return; // 그냥 영상은 끝까지 재생시키자.
	//
	//player->ResetAttack();

}

void UCAnimNotifyState_Parry::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{

	Super::NotifyEnd(MeshComp,Animation);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == NULL) return;

	//여기서 플레이어의 검의 충돌을 꺼준다.
	//
	player->ResetAttack();
	
}
