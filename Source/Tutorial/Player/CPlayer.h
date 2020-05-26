#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	UnArm = 0,
	BlackSword,
	Count,
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Dash, Burst, Skill3, Skill4, Count
};

USTRUCT(BlueprintType)
struct FWeaponDesc
{
	GENERATED_USTRUCT_BODY()
public:
	FName Socket = "";
	FName HolsterSocket = "";
	UClass* WeaponClass = NULL;
	AActor* WeaponActor = NULL;

	float AttackMontageSpeed = 1.0f;
	TArray<class UAnimMontage*> AttackMontages;
	TSubclassOf<class UCPlayerAnimInstance> AnimInstance;
	class UAnimMontage* SkillMontages[(int)ESkillType::Count];
};

UCLASS()
class TUTORIAL_API ACPlayer : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float Speed = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float RunSpeed = 600.0f;

protected:
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* TargetCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TargetingLostDistance = 1000.f;


	

public:
	ACPlayer();

	virtual void Tick(float DeltaTime) override;

public:

	//Notify 호출함수들.
	void Equipped();
	void Sheathed();
	
	void TurnOnComoboCheck();
	void ResetAttack();
	void HittedSetting(bool val);

	//AnimInstance에서 호출하는 함수들.
	FORCEINLINE bool IsDrawing() { return bDrawing; }
	FORCEINLINE bool IsSheathing() { return bSheathing; }
	FORCEINLINE bool IsCanHitted() { return bCanHitted; }
	FORCEINLINE bool IsTargeting() { return TargetEnemy == NULL ? false : true; }
	//FRotator GetCamRotation();

	FRotator GetNormalizeRotator();
	FORCEINLINE FWeaponDesc& GetCurWeaponDesc() { return WeaponDesc[(int)CurWeaponType]; }

private:
	//CharacterMovement
	void MoveForward(float Value);
	void MoveRight(float Value);
	//void Jumping();
	void Running();
	void StopRunning();

	//CameraMovement
	void Turn(float Value);
	void LookUp(float Value);


	//EquipWeapon
	void OnBlackSwordEquip();
	void OnEquip(EWeaponType Type);

	void Equip();
	void Sheath();
	//Attack
	void Attack();

	//Parry
	void Parry();

	//RollAndBackStep
	void RollAndBackStep();
	void ResetRollAndBackStep();
	void CheckLastVector();
	void RotationRoll();

	//Skill
	void OnSkillDash();
	void OnSkillBurst();

private:
	bool IsKeyDownCheck(FKey key);
	void RotationKey();
	
	void FindTarget();
	void SetTargetEnemy(class ACEnemy* Enemy, bool bOrientRotation);

	bool LostTargetDistance();
private:


protected:
	virtual void BeginPlay() override;

public:	
	//이게 뭐였는지 기억안남
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FGenericTeamId GetGenericTeamId() const override;
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	

private:

	bool bAttack = true;
	bool bCanMove = true;
	bool bForward;
	//Montage로 플레이하지.
	bool bRoll;
	bool bBackStep;

	bool bDrawing;
	bool bSheathing;
	bool bDrawn; 

	//굳이 bool값으로 잡을필요가? NotifyState로 충돌 조절하면 될듯함.
	bool bParry;

	bool bAttacking;
	bool bComboCheck;
	UINT ComboCount = 0;

	//맞을수있는지 없는지 Check 해준다.
	bool bCanHitted = true;

private:
	class USpringArmComponent* SpringArm;
	class UCameraComponent* MainCamera;
	

private:
	//Spawn시키기위해 필요함.
	FWeaponDesc WeaponDesc[(int)EWeaponType::Count];
	EWeaponType CurWeaponType = EWeaponType::UnArm;

	
	class UAnimMontage* RollMontage;
	class UAnimMontage* BackStepMontage;
	class UAnimMontage* ParryMontage;
	class UAnimMontage* HittedMontage;
	
	//Targeting // 아직 수정의 요지가 많다.
	class ACEnemy* TargetEnemy = NULL;
	bool bRolling;
};
