// Fill out your copyright notice in the Description page of Project Settings.

#include "CAnimNotifyState_WeaponCollision.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy.h"
#include "Weapon/CWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"



void UCAnimNotifyState_WeaponCollision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());

	if (player != NULL)
	{
		FWeaponDesc& weaponDesc = player->GetCurWeaponDesc();
		ACWeapon* weapon = Cast<ACWeapon>(weaponDesc.WeaponActor);

		//if (weapon == NULL)
		//	return;

		weapon->SetCapsuleCollision(ECollisionEnabled::QueryAndPhysics);

	}
	else if (enemy != NULL)
	{
		ACWeapon* weapon = Cast<ACWeapon>(enemy->GetWeapon());

		weapon->SetCapsuleCollision(ECollisionEnabled::QueryAndPhysics);
	}

}

void UCAnimNotifyState_WeaponCollision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	if (player != NULL)
	{
		FWeaponDesc& weaponDesc = player->GetCurWeaponDesc();
		ACWeapon* weapon = Cast<ACWeapon>(weaponDesc.WeaponActor);

		//if (weapon == NULL)
		//	return;

		weapon->SetCapsuleCollision(ECollisionEnabled::NoCollision);

	}
	else if (enemy != NULL)
	{
		ACWeapon* weapon = Cast<ACWeapon>(enemy->GetWeapon());

		weapon->SetCapsuleCollision(ECollisionEnabled::NoCollision);
	}
}
