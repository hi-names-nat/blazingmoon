// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Save/BlazingMoonGameInstance.h"
#include "Weapon/HealthComponent.h"
#include "Weapon/Damage/UDamageFire.h"
#include "BlazingMoonCharacter.generated.h"


class UDialogueComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginAim);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndAim);

UCLASS(config=Game)
class BLAZINGMOON_API ABlazingMoonCharacter : public ACharacter
{
	GENERATED_BODY()

	//Input
	 
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Camera Position While Aiming */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* AimCameraPosition;

	/** Position to spawn the projectile from */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ProjectileSpawnTransform;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DialogueMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BeginAimAction;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EndAimAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	
protected:

	UPROPERTY()
	UUDamageFire* fire;
	
	UPROPERTY(BlueprintAssignable, Category = Aim)
	FOnBeginAim OnBeginAim;
	
	UPROPERTY(BlueprintAssignable, Category = Aim)
	FOnEndAim OnEndAim;
	
	//System

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Aim, meta = (AllowPrivateAccess = "true"))
	FTransform BoomDefaultTransform;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Aim, meta = (AllowPrivateAccess = "true"))
	FTransform CameraCachedTransform;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Throwable, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABlazingMoonProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Throwable, meta = (AllowPrivateAccess = "true"))
	float ThrowCooldown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Throwable, meta = (AllowPrivateAccess = "true"))
	USoundBase* ThrowSound;

	FTimerDelegate ThrowCooldownDelegate;
	FTimerHandle ThrowCooldownHandle;
	bool CanThrow = true;

	//Reference to the playerstate object within GameInstance
	FBlazingMoonPlayerState* PlayerState;

	//todo: maybe add some sort of combo for multiclicking flail...
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= Flail, meta=(AllowPrivateAccess="true"))
	float FlailLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= Flail, meta=(AllowPrivateAccess="true"))
	int FlailDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Flail, meta = (AllowPrivateAccess = "true"))
	USoundBase* FlailSound;

public:
	ABlazingMoonCharacter();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Aim(const FInputActionValue& Value);
	void EndAim();

	void EnableAimingArc();
	void DisableAimingArc();
	void DrawAimingArc();

	UFUNCTION(BlueprintNativeEvent)
	void ThrowAttack();
	UFUNCTION(BlueprintNativeEvent)
	void MeleeAttack();
	void SwitchAttackMethod(bool Aiming);
	uint32 AttackBindingHandle;

	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION()
	void OnPlayerHurt();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	//Setup the state of this instance of the player
	void ConfigurePlayerState();

	void SetDialogueMappingContext() const;
	void SetMainMappingContext() const;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE void DoDamage(const float Damage, UDamageType* DamageType) const
	{
		HealthComponent->DamageObject(Damage, DamageType);
	}

	UFUNCTION(BlueprintImplementableEvent)
	void FillDialogue(const FString& Text) const;
	UFUNCTION(BlueprintNativeEvent)
	void SetupDialogue() const;
	UFUNCTION(BlueprintNativeEvent)
	void DestroyDialogue() const;
};

