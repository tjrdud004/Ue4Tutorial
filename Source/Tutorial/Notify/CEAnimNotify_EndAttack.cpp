#include "CEAnimNotify_EndAttack.h"
#include "Enemy/CEnemy.h"
#include "Components/SkeletalMeshComponent.h"



void UCEAnimNotify_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());

	if (enemy == NULL)
		return;

	enemy->EndAttack();

}
