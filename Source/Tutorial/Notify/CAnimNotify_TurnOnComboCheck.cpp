// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_TurnOnComboCheck.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_TurnOnComboCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player != NULL)
	{
		player->TurnOnComoboCheck();
	}
}
