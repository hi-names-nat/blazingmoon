// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlazingMoonCharacter.h"
#include "BlazingMoonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InteractionComponent.h"
#include "BlazingMoon/BlazingMoon.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Save/BlazingMoonGameInstance.h"
#include "Weapon/BlazingMoonProjectile.h"
#include "Weapon/HealthComponent.h"

//////////////////////////////////////////////////////////////////////////
// ABlazingMoonCharacter

void ABlazingMoonCharacter::OnPlayerHurt()
{PlayerState->Health = HealthComponent->CurrentHealth;}

ABlazingMoonCharacter::ABlazingMoonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	PlayerState = nullptr;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create the placeholder position for 
	AimCameraPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Aiming position"));
	AimCameraPosition->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	AimCameraPosition->SetRelativeLocation(FVector(100, 300, -100));

	ProjectileSpawnTransform = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Spawn Transform"));
	ProjectileSpawnTransform->SetupAttachment(CameraBoom);
	ProjectileSpawnTransform->SetRelativeLocation(FVector(500, 0, 50));
	ProjectileSpawnTransform->SetRelativeRotation(FRotator(30, 0, 0));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->SetupAttachment(RootComponent);

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("interact"));
}

void ABlazingMoonCharacter::BeginPlay()
{
	
	// Call the base class  
	Super::BeginPlay();

	// set up player state
	ConfigurePlayerState();

	//Add Input Mapping Context
	SetMainMappingContext();
	
	ThrowCooldownDelegate.BindLambda([this](){CanThrow=true;});
	HealthComponent->OnHurt.AddDynamic(this, &ABlazingMoonCharacter::OnPlayerHurt);

	BoomDefaultTransform = CameraBoom->GetRelativeTransform();

}

void ABlazingMoonCharacter::ConfigurePlayerState()
{
	//Set up all that tasty stuff with the reference to player state
	PlayerState = Cast<UBlazingMoonGameInstance>(GetGameInstance())->GetPlayerStatePtr();
	HealthComponent->SetHealth(PlayerState->Health);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABlazingMoonCharacter::SetDialogueMappingContext() const
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DefaultMappingContext);
			Subsystem->AddMappingContext(DialogueMappingContext, 0);
		}
	}
}

void ABlazingMoonCharacter::SetMainMappingContext() const
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(DialogueMappingContext);
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABlazingMoonCharacter::SetupDialogue_Implementation() const
{
	SetDialogueMappingContext();
}

void ABlazingMoonCharacter::DestroyDialogue_Implementation() const
{
	SetMainMappingContext();
}


void ABlazingMoonCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	DrawDebugDirectionalArrow(GetWorld(), ProjectileSpawnTransform->GetComponentLocation() - ProjectileSpawnTransform->GetForwardVector()*20, ProjectileSpawnTransform->GetComponentLocation(), 5, FColor::Red);

}

void ABlazingMoonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABlazingMoonCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABlazingMoonCharacter::Look);

		//Aiming
		EnhancedInputComponent->BindAction(BeginAimAction, ETriggerEvent::Triggered, this, &ABlazingMoonCharacter::Aim);
		EnhancedInputComponent->BindAction(EndAimAction, ETriggerEvent::Triggered, this, &ABlazingMoonCharacter::EndAim);
		
		//Attacking
		 AttackBindingHandle = EnhancedInputComponent->
		 BindAction(AttackAction, ETriggerEvent::Triggered, this, &ABlazingMoonCharacter::MeleeAttack)
		 .GetHandle();

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, InteractionComponent, &UInteractionComponent::AttemptInteract);

		
	}
}

void ABlazingMoonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABlazingMoonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABlazingMoonCharacter::Aim(const FInputActionValue& Value)
{
	UE_LOG(LogBlazingMoon, Log, TEXT("Aiming"))
	//Begin Transitioning the camera to the new position

	//Current temp immediate transition.
	const FVector AimLocation = AimCameraPosition->GetRelativeLocation();
	
	CameraCachedTransform = FollowCamera->GetRelativeTransform();
	CameraCachedTransform.SetLocation(FVector(CameraBoom->TargetArmLength, CameraBoom->TargetOffset.Y, CameraBoom->TargetOffset.Z));
	
	CameraBoom->TargetArmLength = CameraBoom->TargetArmLength - AimLocation.X;
	CameraBoom->SetRelativeLocation(FVector(0, AimLocation.Y, AimLocation.Z));
	FollowCamera->SetRelativeRotation(AimCameraPosition->GetRelativeRotation());
	//Bindings for final transition
	OnBeginAim.Broadcast();
	
	//Show aiming reticle
	EnableAimingArc();
	//Prep firing ability
	SwitchAttackMethod(true);
}

void ABlazingMoonCharacter::EndAim()
{
	UE_LOG(LogBlazingMoon, Log, TEXT("Stop Aiming"))
	//Transition the camera back to last relative position

	//Current temp immediate transition
	const auto CachedLocation = CameraCachedTransform.GetLocation();
	CameraBoom->TargetArmLength = CachedLocation.X;
	CameraBoom->SetRelativeLocation(FVector(0, CachedLocation.Y, CachedLocation.Z));
	FollowCamera->SetRelativeRotation(AimCameraPosition->GetRelativeRotation());
	//Bindings for final transition
	OnEndAim.Broadcast();
	
	//Turn off aiming reticle
	DisableAimingArc();
	//Switch to standard attack
	SwitchAttackMethod(false);
}

void ABlazingMoonCharacter::EnableAimingArc()
{
	UE_LOG(LogBlazingMoon, Log, TEXT("Turn on the aiming arc."));
}

void ABlazingMoonCharacter::DisableAimingArc()
{
	UE_LOG(LogBlazingMoon, Log, TEXT("Turn off the aiming arc."));
}

void ABlazingMoonCharacter::DrawAimingArc()
{
	UE_LOG(LogBlazingMoon, Log, TEXT("Should be drawing aiming arc."));
}

void ABlazingMoonCharacter::ThrowAttack_Implementation()
{
	if (!CanThrow) return;
	
	FActorSpawnParameters Params;
	Params.Instigator = this;
	Params.Owner = this;
	auto World = GetWorld(); 
	World->SpawnActor<ABlazingMoonProjectile>(ProjectileClass, ProjectileSpawnTransform->GetComponentLocation(), ProjectileSpawnTransform->GetComponentRotation(), Params);
	World->GetTimerManager().SetTimer(ThrowCooldownHandle, ThrowCooldownDelegate, ThrowCooldown, false);
	CanThrow = false;
	UGameplayStatics::PlaySoundAtLocation(this, ThrowSound, GetActorLocation(), GetActorRotation());
}

void ABlazingMoonCharacter::MeleeAttack_Implementation()
{
	if (!PlayerState->HasFlail) return;

	FHitResult OUT_Hit;
	GetWorld()->LineTraceSingleByChannel(
		OUT_Hit,
		GetActorLocation(),
		GetActorLocation() + (FollowCamera->GetForwardVector() * FlailLength),
		ECC_GameTraceChannel1
		);

	DrawDebugSphere(GetWorld(), OUT_Hit.Location, 50, 12, FColor::Red, true);
	if (const auto OtherHealth = Cast<UHealthComponent>(OUT_Hit.Component))
	{
		OtherHealth->TakeDamage(FlailDamage);
	}
}

void ABlazingMoonCharacter::SwitchAttackMethod(bool Aiming)
{
	auto EnhancedIc = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedIc->RemoveBindingByHandle(AttackBindingHandle);
	if (Aiming)
	{
		AttackBindingHandle = EnhancedIc->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ABlazingMoonCharacter::ThrowAttack).GetHandle();
	}
	else
	{
		AttackBindingHandle = EnhancedIc->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ABlazingMoonCharacter::MeleeAttack).GetHandle();
	}
}




