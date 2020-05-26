// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

UCLASS()
class TUTORIAL_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Capsule;


public:	
	
	ACWeapon();

	virtual void Tick(float DeltaTime) override;
	void SetCapsuleCollision(ECollisionEnabled::Type NewType);

protected:
	
	virtual void BeginPlay() override;

public:	
	// Called every frame

};
