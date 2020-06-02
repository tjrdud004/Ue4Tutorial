// Fill out your copyright notice in the Description page of Project Settings.


#include "CInverseKinematics.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h" 
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UCInverseKinematics::UCInverseKinematics()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCInverseKinematics::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacter>(GetOwner());
	if (Character == NULL) return;
	CapsuleHalfHeight = Character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();


}


// Called every frame
void UCInverseKinematics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FVector leftNormal, rightNormal;
	//거리 추적.
	float leftTraceDistance = Trace(LeftFootSocket,leftNormal);
	float rightTraceDistance = Trace(RightFootSocket, rightNormal);


	float offset = UKismetMathLibrary::Min(leftTraceDistance,rightTraceDistance);
	offset = offset > 0.f ? 0.f : offset;

	float half = CapsuleHalfHeight - FMath::Abs(offset) * 0.5f;
	float scaleHalf = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	
	Ik.HipOffset = UKismetMathLibrary::FInterpTo(Ik.HipOffset,offset,DeltaTime,HipsInterpSpeed);

	float interpValue = UKismetMathLibrary::FInterpTo(scaleHalf, half, DeltaTime, HipsInterpSpeed);

	Character->GetCapsuleComponent()->SetCapsuleHalfHeight(interpValue);

	Ik.Location_Left = UKismetMathLibrary::FInterpTo(Ik.Location_Left, leftTraceDistance - offset, DeltaTime, FeetInterpSpeed);
	Ik.Location_Right = UKismetMathLibrary::FInterpTo(Ik.Location_Right, -(rightTraceDistance - offset),DeltaTime,FeetInterpSpeed);

	Ik.Rotation_Left = UKismetMathLibrary::RInterpTo(Ik.Rotation_Left, NormalToRotator(leftNormal), DeltaTime, FeetInterpSpeed);
	Ik.Rotation_Right = UKismetMathLibrary::RInterpTo(Ik.Rotation_Right, NormalToRotator(rightNormal), DeltaTime, FeetInterpSpeed);


}

float UCInverseKinematics::Trace(FName Socket, FVector & OutputImpactNormal)
{
	FVector location = Character->GetMesh()->GetSocketLocation(Socket);
	FVector start = FVector(location.X, location.Y, Character->GetActorLocation().Z);

	//내캐릭터 중심 - 캡슐의 반 - 추적하고자 하는거리. 이게 EndZ
	float z = start.Z - CapsuleHalfHeight - TraceDistance;
	FVector end = FVector(location.X, location.Y, z);

	//자기 자신을 충돌에서 제외함.
	TArray<AActor*> ignore;
	ignore.Add(GetOwner());

	FHitResult hit;
	bool bHit = UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(), start, end, UEngineTypes::ConvertToTraceType(ECC_Visibility), true,
		ignore,EDrawDebugTrace::ForOneFrame,hit,true,FLinearColor::Blue
	);

	OutputImpactNormal = hit.ImpactNormal;

	//blocking이 가능한 친구랑 히트가 됬는지.
	if (hit.IsValidBlockingHit() == false)
		return 0.f;

	float length = (hit.ImpactPoint - hit.TraceEnd).Size();

	return AdjustOffset + length - TraceDistance;
	
}

FRotator UCInverseKinematics::NormalToRotator(FVector & Normal)
{

	float t = UKismetMathLibrary::DegAtan2(Normal.Y,Normal.Z); // Roll. // Y가 오른쪽, Z가 위
	//Pitch는 뒤집어 지는것을 알아야한다.
	float t2 = -UKismetMathLibrary::DegAtan2(Normal.X, Normal.Z); // Pitch // X가 전방 , Z가 윗방

	return FRotator(t2, 0.f, t);


	
}

