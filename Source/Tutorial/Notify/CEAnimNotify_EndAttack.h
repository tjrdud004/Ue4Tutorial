// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CEAnimNotify_EndAttack.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UCEAnimNotify_EndAttack : public UAnimNotify
{
	GENERATED_BODY()
public:

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
