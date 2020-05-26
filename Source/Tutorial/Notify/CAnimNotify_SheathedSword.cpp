// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_SheathedSword.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_SheathedSword::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player != NULL)
		player->Sheathed();
}
