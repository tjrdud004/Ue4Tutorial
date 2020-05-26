// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CPlayerAnimInstance.generated.h"

UCLASS()
class TUTORIAL_API UCPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bDrawing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bSheathing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Aim_Yaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Aim_Pitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float InterpSpeed = 15.f;

public:
	UCPlayerAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:


	
};
