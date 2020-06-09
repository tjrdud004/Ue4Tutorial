// Fill out your copyright notice in the Description page of Project Settings.


#include "CStamina.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CPlayer.h"



UCStamina::UCStamina()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCStamina::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UCStamina::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCStamina::SetTimerHandle(bool bDecrease)
{

	if(bDecrease == true)
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCStamina::DecreaseStamina, 0.05f ,true);
	else
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCStamina::IncreaseStamina, 0.05f, true);

}

void UCStamina::DecreaseStamina()
{
	if (CurStamina <= 0.0f)
	{
		//순서 중요. 안 그럼 차오르는 속도가 애매해짐.
		Cast<ACPlayer>(GetOwner())->StopRunning();
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCStamina::OnIncreaseStamina, 2.f, false);

		return;
	}

	CurStamina -= RateStamina;

	//bIncrease = false;
	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCStamina::OnIncreaseStamina, 2.f, false);

}

bool UCStamina::DecreaseStamina(const float & Minus)
{
	if (CurStamina - Minus <= 0.0f)
		return false;

	CurStamina -= Minus;
	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCStamina::OnIncreaseStamina, 2.f, false);

	return true;
}

void UCStamina::IncreaseStamina()
{
	if (CurStamina >= 100.0f)
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
		return;
	}

	CurStamina += RateStamina;

}

void UCStamina::OnIncreaseStamina()
{
	
	GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCStamina::IncreaseStamina, 0.05f, true);


}

