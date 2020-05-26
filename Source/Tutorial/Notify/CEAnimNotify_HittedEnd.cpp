#include "CEAnimNotify_HittedEnd.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/CEnemy.h"

void UCEAnimNotify_HittedEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACEnemy* enemy = Cast<ACEnemy>(MeshComp->GetOwner());

	if (enemy == NULL)
		return;

	enemy->HittedEnd();


}
