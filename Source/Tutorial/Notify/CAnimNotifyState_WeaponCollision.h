// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_WeaponCollision.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UCAnimNotifyState_WeaponCollision : public UAnimNotifyState
{
	GENERATED_BODY()
public:

	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
	
};
