#include "CBlackSword.h"
#include "ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"
#include "Enemy/CEnemy.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"


ACBlackSword::ACBlackSword()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FString path = L"SkeletalMesh'/Game/Player/Weapon/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'";
	ConstructorHelpers::FObjectFinder<USkeletalMesh> blackSword(*path);
	
	if (blackSword.Succeeded())
		Mesh->SkeletalMesh = blackSword.Object;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Capsule->SetupAttachment(Mesh);
	Capsule->SetRelativeLocation(FVector(0, 0, 60));
	Capsule->SetRelativeRotation(FRotator(180, 0, 0));
	Capsule->SetCapsuleRadius(10);
	Capsule->SetCapsuleHalfHeight(50);

	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BaseParticle = CreateDefaultSubobject<UParticleSystemComponent>(L"BaseParticle");


	path = L"ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Defense/P_Shield_Spawn.P_Shield_Spawn'";

	static ConstructorHelpers::FObjectFinder<UParticleSystem> baseParticle(*path);
	if (baseParticle.Succeeded())
		BaseParticle->SetTemplate(baseParticle.Object);

}

void ACBlackSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBlackSword::BeginPlay()
{
	Super::BeginPlay();
	
	Capsule->OnComponentBeginOverlap.AddDynamic(this,&ACBlackSword::OnBeginOverlap);

}

void ACBlackSword::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if (enemy != NULL)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage ,NULL,GetOwner(),NULL);
		BaseParticle->ActivateSystem();
		
	}
}
