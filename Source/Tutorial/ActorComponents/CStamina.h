// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStamina.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TUTORIAL_API UCStamina : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxStamina= 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RateStamina = 1.f; 

public:	
	// Sets default values for this component's properties
	UCStamina();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

public:
	void SetTimerHandle(bool bDecrease);
	FORCEINLINE float GetCurStaminaPercent() { return CurStamina / MaxStamina; }
	
public:
	void DecreaseStamina();
	bool DecreaseStamina(const float& Minus);
	void IncreaseStamina();
	void OnIncreaseStamina();


	

private:
	FTimerHandle TimerHandle;
	float Timer = 0.f;
	float MaxTime = 2.f;
		
};
