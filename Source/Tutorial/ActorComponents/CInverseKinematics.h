// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInverseKinematics.generated.h"

USTRUCT(BlueprintType)
struct FIk
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HipOffset = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Location_Left;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Location_Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FRotator Rotation_Left;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FRotator Rotation_Right;
	
};

UCLASS( ClassGroup=(InverseKinematics), meta=(BlueprintSpawnableComponent) )
class TUTORIAL_API UCInverseKinematics : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "InverseKinematics")
		FName LeftFootSocket = "Foot_L";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InverseKinematics")
		FName RightFootSocket = "Foot_R";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InverseKinematics")
		float TraceDistance = 55.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InverseKinematics")
		float AdjustOffset = 5.f; // 발과 땅사이 간경?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InverseKinematics")
		float HipsInterpSpeed = 17.f; // Pelvis/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InverseKinematics")
		float FeetInterpSpeed = 22.f;




public:
	UCInverseKinematics();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE const FIk& GetIK() { return Ik; }


private:
	float Trace(FName Socket, FVector& OutputImpactNormal);
	//노말벡터를 회전값으로 바꿔주는 함수. 
	FRotator NormalToRotator(FVector& Normal);

private:
	FIk Ik;

	class ACharacter* Character;
	float CapsuleHalfHeight;

};
