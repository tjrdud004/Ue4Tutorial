#include "CAnimNotifyState_Hitted.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/CEnemy.h"

void UCAnimNotifyState_Hitted::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());
	
	if (player != NULL)
	{
		player->HittedSetting(false);
	}
	else if (enemy != NULL)
	{
		enemy->HittedBegin();
	}




}

void UCAnimNotifyState_Hitted::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());

	if (player == NULL)
		return;

	player->HittedSetting(true);
}
