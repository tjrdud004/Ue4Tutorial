#include "CAnimNotifyState_Hitted.h"
#include "Player/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"

void UCAnimNotifyState_Hitted::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	
	if (player == NULL)
		return;

	player->HittedSetting(false);

}

void UCAnimNotifyState_Hitted::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());

	if (player == NULL)
		return;

	player->HittedSetting(true);
}
