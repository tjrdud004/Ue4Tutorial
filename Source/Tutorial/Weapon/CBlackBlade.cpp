// Fill out your copyright notice in the Description page of Project Settings.


#include "CBlackBlade.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/CPlayer.h"
#include "Engine.h"


ACBlackBlade::ACBlackBlade()
{
	PrimaryActorTick.bCanEverTick = true;

	FString path = L"SkeletalMesh'/Game/Enemy/Weapon/Blade_BlackWyrmBlade/SK_Blade_BlackWyrmBlade.SK_Blade_BlackWyrmBlade'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> blackBlade(*path);

	if (blackBlade.Succeeded())
		Mesh->SkeletalMesh = blackBlade.Object;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(Mesh);
	Capsule->SetRelativeLocation(FVector(0, 10, 40));
	Capsule->SetRelativeRotation(FRotator(0, 0, 0));
	Capsule->SetCapsuleRadius(20);
	Capsule->SetCapsuleHalfHeight(60);

	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Capsule->bHiddenInGame = false;
}

void ACBlackBlade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBlackBlade::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this,&ACBlackBlade::OnBeginOverlap);
}

void ACBlackBlade::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	
	if (player != NULL && player->IsCanHitted() == true)
		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, GetOwner(), NULL);
	

}
