#include "CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AnimInstance/CPlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine.h"

#include "Weapon/CWeapon.h"
#include "Enemy/CEnemy.h"
#include "Camera/CSkillCameraShake.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	FString path;
	
	
	//Roll
	{
		path = L"AnimMontage'/Game/Character/Unarm/Roll_Montage.Roll_Montage'";
		//path = L"AnimMontage'/Game/Character/Unarm/Hit_Reaction_Montage.Hit_Reaction_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> roll(*path);
		if (roll.Succeeded())
			RollMontage = roll.Object;
	}

	//BackStep
	{
		path = L"AnimMontage'/Game/Character/Unarm/StepBack_Montage.StepBack_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> backStep(*path);
		if (backStep.Succeeded())
			BackStepMontage = backStep.Object;
	}

	//Parry
	{
		path = L"AnimMontage'/Game/Character/BlackSword/1H_Parry_Montage.1H_Parry_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> parry(*path);
		if (parry.Succeeded())
			ParryMontage = parry.Object;
	}

	//Hitted
	{
		path = L"AnimMontage'/Game/Character/Unarm/Hit_Reaction_Montage.Hit_Reaction_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> hitted(*path);
		if (hitted.Succeeded())
			HittedMontage = hitted.Object;
	}

	//BlackSword
	{
		path = L"Class'/Script/Tutorial.CBlackSword'";

		FWeaponDesc& desc = WeaponDesc[(int)EWeaponType::BlackSword];
		ConstructorHelpers::FClassFinder<ACWeapon> weapon(*path);
		
		desc.Socket = L"SwordSocket";
		desc.HolsterSocket = L"SwordHolsterSocket";

		if (weapon.Succeeded())
			desc.WeaponClass = weapon.Class;

		path = L"AnimBlueprint'/Game/Player/AnimInstance/BpBlackSword.BpBlackSword_C'";
		ConstructorHelpers::FClassFinder<UAnimInstance> animInstance(*path);
		
		if (animInstance.Succeeded())
			desc.AnimInstance = animInstance.Class;

		path = L"AnimMontage'/Game/Character/BlackSword/Primary_Attack_A_Montage.Primary_Attack_A_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> combo1(*path);
		if (combo1.Succeeded())
			desc.AttackMontages.Emplace(combo1.Object);

		path = L"AnimMontage'/Game/Character/BlackSword/Primary_Attack_B_Montage.Primary_Attack_B_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> combo2(*path);
		if (combo2.Succeeded())
			desc.AttackMontages.Emplace(combo2.Object);

		path = L"AnimMontage'/Game/Character/BlackSword/Primary_Attack_C_Montage.Primary_Attack_C_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> combo3(*path);
		if (combo3.Succeeded())
			desc.AttackMontages.Emplace(combo3.Object);

		path = L"AnimMontage'/Game/Character/BlackSword/Ability_Q_Montage.Ability_Q_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> DashSkill(*path);
		if (DashSkill.Succeeded())
			desc.SkillMontages[(int)ESkillType::Dash] = DashSkill.Object;


		path = L"AnimMontage'/Game/Character/BlackSword/1H_Special_Montage.1H_Special_Montage'";
		ConstructorHelpers::FObjectFinder<UAnimMontage> BurstSkill(*path);
		if (BurstSkill.Succeeded())
			desc.SkillMontages[(int)ESkillType::Burst] = BurstSkill.Object;
	}

	
}

bool ACPlayer::IsKeyDownCheck(FKey key)
{
	return UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(key);
}

void ACPlayer::RotationKey()
{
	//FRotator rot = GetActorRotation();
	FRotator rot =  MainCamera->GetComponentRotation();
	rot.Pitch = 0;
	rot.Roll= 0;

	if (IsKeyDownCheck(EKeys::A) && IsKeyDownCheck(EKeys::W))
	{
		rot.Yaw += -45.0f;
	}
	else if (IsKeyDownCheck(EKeys::A) && IsKeyDownCheck(EKeys::S))
	{
		rot.Yaw += -135.0f;
	}
	else if (IsKeyDownCheck(EKeys::D) && IsKeyDownCheck(EKeys::W))
	{
		rot.Yaw += 45.0f;
	}
	else if (IsKeyDownCheck(EKeys::D) && IsKeyDownCheck(EKeys::S))
	{
		rot.Yaw += 130.0f;
	}
	else if (IsKeyDownCheck(EKeys::A))
	{
		rot.Yaw += -90.0f;
	}
	else if (IsKeyDownCheck(EKeys::S))
	{
		rot.Yaw += -180.0f;
	}
	else if (IsKeyDownCheck(EKeys::D))
	{
		rot.Yaw += 90.0f;
	}
	else if (IsKeyDownCheck(EKeys::W))
	{
		rot.Yaw += 0;
	}
	
	SetActorRotation(rot);
}

void ACPlayer::FindTarget()
{
	if (TargetEnemy == NULL)
	{

		TArray<FHitResult> Hits;
		FCollisionShape Sphere = FCollisionShape::MakeSphere(500.f);
		DrawDebugSphere(GetWorld(), GetActorLocation(), Sphere.GetSphereRadius(), 100, FColor::Blue, true);

		FVector start = GetActorLocation();
		FVector end = GetActorLocation();
		end.Z += 250.f;

		bool IsHit = GetWorld()->SweepMultiByChannel(Hits, start, end, FQuat::Identity
			, ECC_WorldDynamic, Sphere);

		if (IsHit == true)
		{
			for (FHitResult& hit : Hits)
			{
				//적이 있을경우.
				ACEnemy* enemy = Cast<ACEnemy>(hit.GetActor());
				if (enemy != NULL)
				{
					SetTargetEnemy(enemy, false);
					return;
				}
			}
		}
		//거리안에 적이 없을경우.
		SetTargetEnemy(NULL, true);
		return;
	}
	else
	{
		//이미 Targeting이 되있지만 해제하고싶을때.
		SetTargetEnemy(NULL, true);
		return;
	}



}

void ACPlayer::SetTargetEnemy(ACEnemy * Enemy, bool bOrientRotation)
{
	TargetEnemy = Enemy;
	GetCharacterMovement()->bOrientRotationToMovement = bOrientRotation;
	//bUseControllerRotationYaw = true; // 이것도 하려면 CameraSetting을 해야함.
}

bool ACPlayer::LostTargetDistance()
{
	FVector start = GetActorLocation();
	FVector end = TargetEnemy->GetActorLocation();
	float dist = FVector::Distance(start,end);

	if (dist > TargetingLostDistance)
		return true;

	return false;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform = FTransform::Identity;
	FActorSpawnParameters params;
	params.Owner = this;

	//BlackSword
	{
		FWeaponDesc& weapon = WeaponDesc[(int)EWeaponType::BlackSword];
		weapon.WeaponActor = GetWorld()->SpawnActor(weapon.WeaponClass, &transform, params);
		weapon.WeaponActor->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), weapon.HolsterSocket);
	}

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
	MainCamera = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));

}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetEnemy != NULL && bRolling == false)
	{
		FVector start = GetActorLocation();
		FVector end = TargetEnemy->GetActorLocation();

		FRotator rot = UKismetMathLibrary::FindLookAtRotation(start,end);
		rot.Pitch = 0.f;
		rot.Roll = 0.f;
		FRotator ActorRot = GetActorRotation();
		rot = UKismetMathLibrary::RInterpTo(ActorRot, rot, DeltaTime, 5.f);

		SetActorRotation(rot);

		//이렇게 두면 정상적으로 작동은 하겠지만 애매함...
		if (LostTargetDistance() == true)
		{
			SetTargetEnemy(NULL, true);
		}
	}
}

FRotator ACPlayer::GetNormalizeRotator()
{
	FRotator lookRot = GetControlRotation();
	//Targeting중일땐 Enemy쪽을 바라보게 만들기위함.
	if (IsTargeting() == true)
	{
		FVector start = GetActorLocation();
		FVector end = TargetEnemy->GetActorLocation();

		FRotator rot = UKismetMathLibrary::FindLookAtRotation(start, end);
		rot.Pitch = 0.f;
		rot.Roll = 0.f;

		lookRot = rot;
	}
	else
	{
		lookRot = GetControlRotation();
	}

	FRotator  ActorRot = GetActorRotation();

	return UKismetMathLibrary::NormalizedDeltaRotator(lookRot,ActorRot);
}

void ACPlayer::MoveForward(float Value)
{
	bForward = Value > 0.1f;
	if (bCanMove == false) return;

	FRotator rotation = GetControlRotation();
	FRotator temp = FRotator(0, rotation.Yaw, 0);
	FVector forward = FQuat(temp).GetForwardVector();

	AddMovementInput(forward, Value);
}

void ACPlayer::MoveRight(float Value)
{
	if (bCanMove == false) return;

	FRotator rotation = GetControlRotation();
	FRotator temp = FRotator(0, rotation.Yaw, 0);
	FVector right = FQuat(temp).GetRightVector();

	AddMovementInput(right, Value);
}

void ACPlayer::CheckLastVector()
{
	if (bRoll == true) return;
	if (bBackStep == true) return;

	//현재 공격중인데
	if (bAttacking == true)
		if (bComboCheck == false)
			return;

	if (bCanMove == false) return;

	//Notify에서 설정해줌.
	bCanMove = false;
	bAttack = false;

	FVector LastVec = GetCharacterMovement()->GetLastInputVector();
	bool bMove = UKismetMathLibrary::NotEqual_VectorVector(LastVec, FVector::ZeroVector, 0.00001f);

}

void ACPlayer::RotationRoll()
{
	if (bRoll == true) return;
	if (bBackStep == true) return;

	//현재 공격중인데
	if (bAttacking == true)
		if (bComboCheck == false)
			return;

	if (bCanMove == false) return;

	//Notify에서 설정해줌.
	bCanMove = false;
	bAttack = false;

	
	if(IsKeyDownCheck(EKeys::A) || IsKeyDownCheck(EKeys::S) || IsKeyDownCheck(EKeys::D) || IsKeyDownCheck(EKeys::W))
	{
		bRoll = true;
		bRolling = true;
		RotationKey();
		PlayAnimMontage(RollMontage);
	}
	else
	{
		bBackStep = true;
		PlayAnimMontage(BackStepMontage);
	}
	
	bCanHitted = false;
}

void ACPlayer::Running()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	bRunning = true;
}

void ACPlayer::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	bRunning = false;
}

void ACPlayer::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ACPlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ACPlayer::OnBlackSwordEquip()
{
	OnEquip(EWeaponType::BlackSword);
}

void ACPlayer::OnEquip(EWeaponType Type)
{
	//뭔가 하는중엔 Return;
	if (bDrawing == true) return;
	if (bSheathing == true) return;
	if (bCanMove == false) return;

	if (bDrawn == false)
	{
		CurWeaponType = Type;
		FWeaponDesc& weapon = WeaponDesc[(int)Type];
		GetMesh()->SetAnimInstanceClass(weapon.AnimInstance);

		Equip();

		return;
	}
	
	if (GetCharacterMovement()->IsFalling() == false)
	{
		Sheath();
	}
}

//나중에 Notify로 제어할예정.
void ACPlayer::Equip()
{
	bDrawing = true;
	bCanMove = false;
}

//Notify로 호출할거임.
void ACPlayer::Equipped()
{
	bDrawing = false;
	bDrawn = true;
	bCanMove = true;

	//bUseControllerRotationYaw = true;
	//GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACPlayer::Sheath()
{
	bSheathing = true;
	bCanMove = false;
}

void ACPlayer::Attack()
{
	if (bAttack == false) return;
	
	FWeaponDesc& desc = WeaponDesc[(int)CurWeaponType];

	if (desc.AttackMontages.Num() <= 0) return;

	if (bAttacking == false)
	{
		PlayAnimMontage(desc.AttackMontages[ComboCount]);
		ComboCount++;
		bAttacking = true;
		bCanMove = false;
	}
	else if(bComboCheck == true)
	{
		PlayAnimMontage(desc.AttackMontages[ComboCount]);

		ComboCount++;
		ComboCount %= 3;

		bComboCheck = false;
		bCanMove = false;
	}
}

void ACPlayer::Parry()
{
	if (bCanMove == false) return;
	if (bAttacking == true) return;
	if (bRoll == true) return;
	if (bBackStep == true) return;
	if (CurWeaponType == EWeaponType::UnArm) return;
	
	//여기서 false 해주는건 Parry 끝나면 풀어주든지 해줘야할듯. 
	//NotifyState로 충돌구간을 지정해주면될듯. 충돌했을때도 조건값 풀어줘야함.
	bCanMove = false;
	bAttack = false;

	PlayAnimMontage(ParryMontage, 1.5f);
}

void ACPlayer::RollAndBackStep()
{
	//안에서 bool값을 수정해줌. 그러면 이게 AnimInstance에 적용됨.
	//CheckLastVector();
	RotationRoll();
}

void ACPlayer::ResetRollAndBackStep()
{
	bRoll = false;
	bBackStep = false;
}

void ACPlayer::OnSkillDash()
{
	if (CurWeaponType == EWeaponType::UnArm) return;
	if (bCanMove == false) return;
	if (bRoll == true) return;
	if (bBackStep == true) return;

	bCanMove = false;
	bAttack = false;

	FWeaponDesc& desc = GetCurWeaponDesc();
	PlayAnimMontage(desc.SkillMontages[(int)ESkillType::Dash],1.3f);
}

void ACPlayer::OnSkillBurst()
{
	if (CurWeaponType == EWeaponType::UnArm) return;
	if (bCanMove == false) return;
	if (bRoll == true) return;
	if (bBackStep == true) return;

	bCanMove = false;
	bAttack = false;

	FWeaponDesc& desc = GetCurWeaponDesc();
	PlayAnimMontage(desc.SkillMontages[(int)ESkillType::Burst], 1.3f);
	
}

void ACPlayer::Sheathed()
{
	bSheathing = false;
	bDrawn = false;
	bCanMove = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	CurWeaponType = EWeaponType::UnArm;
}

void ACPlayer::TurnOnComoboCheck()
{
	bComboCheck = true;
}

void ACPlayer::ResetAttack()
{
	ComboCount = 0;
	bAttacking = false;
	bComboCheck = false;
	bCanMove = true;
	bAttack = true;
	bCanHitted = true;
	bRolling = false;
}

void ACPlayer::HittedSetting(bool val)
{
	ComboCount = 0;
	bCanMove = val;
	bAttack = val;
	bCanHitted = val;
	bRoll = !val;
	bBackStep = !val;
	bAttacking = false;
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement
	PlayerInputComponent->BindAxis("MoveForward",this ,&ACPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::MoveRight);
	//Roll
	PlayerInputComponent->BindAction("RollAndBackStep", EInputEvent::IE_Pressed, this, &ACPlayer::RollAndBackStep);
	PlayerInputComponent->BindAction("RollAndBackStep", EInputEvent::IE_Released, this, &ACPlayer::ResetRollAndBackStep);
	//PlayerInputComponent->BindAction("Jumping",EInputEvent::IE_Released, this,&ACharacter::StopJumping);
	//Run
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer::Running);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer::StopRunning);

	//WeaponEquip
	PlayerInputComponent->BindAction("BlackSword", EInputEvent::IE_Pressed, this, &ACPlayer::OnBlackSwordEquip);

	//Attack
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACPlayer::Attack);

	//Parry
	PlayerInputComponent->BindAction("Parry", EInputEvent::IE_Pressed, this, &ACPlayer::Parry);

	//Skill
	PlayerInputComponent->BindAction("SkillDash", EInputEvent::IE_Pressed, this, &ACPlayer::OnSkillDash);
	PlayerInputComponent->BindAction("SkillBurst", EInputEvent::IE_Pressed, this, &ACPlayer::OnSkillBurst);
	
	//Targeting
	PlayerInputComponent->BindAction("Target", EInputEvent::IE_Pressed, this, &ACPlayer::FindTarget);
	
	//CameraMove
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::LookUp);

}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(1);
}

float ACPlayer::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	PlayAnimMontage(HittedMontage);

	APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	camManager->PlayCameraShake(UCSkillCameraShake::StaticClass(), 0.2f);

	return 0.0f;
}

