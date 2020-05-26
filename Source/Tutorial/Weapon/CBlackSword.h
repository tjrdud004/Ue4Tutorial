// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CBlackSword.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ACBlackSword : public ACWeapon
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
		float Damage = 20.f;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* BaseParticle;

public:
	ACBlackSword();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;



private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

};
