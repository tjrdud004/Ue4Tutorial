// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEndAttackDelegate)


UCLASS()
class TUTORIAL_API ACEnemy : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
		float Health = 100.f;



public:

	ACEnemy();

protected:

	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	void BeginAttack();
	void EndAttack();
	FOnEndAttackDelegate OnEndAttack;
	FORCEINLINE bool IsCanMove() { return bCanMove; }

	void HittedEnd();

	FORCEINLINE class AActor* GetWeapon() { return BlackBlade; }
private:
	void Death();

private:

	class AActor* BlackBlade;
	FName Socket;
	FName HolsterSocket;
	UAnimMontage* AttackMontage;
	UAnimMontage* HittedMontage;
	bool bAttack = true;
	bool IsAttack;
	bool bCanMove = true;
	bool bDead = false;
	FTimerHandle DeadTimerHandle;

};
