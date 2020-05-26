// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CBlackBlade.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API ACBlackBlade : public ACWeapon
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
		float Damage = 20.f;


public:

	ACBlackBlade();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
