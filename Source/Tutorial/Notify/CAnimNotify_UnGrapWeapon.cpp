// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_UnGrapWeapon.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotify_UnGrapWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player != NULL)
	{
		FWeaponDesc& weapon = player->GetCurWeaponDesc();

		if (weapon.WeaponActor != NULL)
			weapon.WeaponActor->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), weapon.HolsterSocket);

	}

}
