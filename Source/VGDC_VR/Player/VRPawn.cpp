// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "../Environment/ShootableInterface.h"
#include "DrawDebugHelpers.h"


// Sets default values
AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	/// Component Setup
	// May not be necessary to have a seperate Root component and VROrigin - 
	//   i.e. VROrigin may be good enough as the root
	// We should investigate this further
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(RootComponent);

	// Attach camera to VROrigin and enable head tracking
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VROrigin);
	Camera->bLockToHmd = true;



	/// MotionControllers setup
	// Make sure we snap the controllers to the pawn properly
	FAttachmentTransformRules ControllerAttachRules =
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	// Initialize left controller
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	LeftController->AttachToComponent(VROrigin, ControllerAttachRules);
	LeftController->SetRelativeLocation(FVector(0.0f));
	LeftController->Hand = EControllerHand::Left;

	// Initialize right controller
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	RightController->AttachToComponent(VROrigin, ControllerAttachRules);
	RightController->SetRelativeLocation(FVector(0.0f));
	RightController->Hand = EControllerHand::Right;



	/// Interactors setup
	LeftControllerInteractor = CreateAbstractDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left UI Interactor"));
	LeftControllerInteractor->SetupAttachment(LeftController);
	LeftControllerInteractor->SetRelativeLocation(FVector(0.0f));

	RightControllerInteractor = CreateAbstractDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right UI Interactor"));
	RightControllerInteractor->SetupAttachment(RightController);
	RightControllerInteractor->SetRelativeLocation(FVector(0.0f));

	

	/// Meshes setup
	// Get the in-engine HMD mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeadsetMesh(TEXT("StaticMesh'/Engine/VREditor/Devices/Generic/GenericHMD.GenericHMD'"));
	if (HeadsetMesh.Object == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Failed to load headset mesh!"));

	// Get the in-engine Oculus Touch mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ControllerMesh(TEXT("StaticMesh'/Engine/VREditor/Devices/Oculus/OculusControllerMesh.OculusControllerMesh'"));
	if (ControllerMesh.Object == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Failed to load controller mesh!"));

	// Initialize headset mesh
	UStaticMeshComponent* HeadsetMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	HeadsetMeshComp->SetupAttachment(Camera);
	HeadsetMeshComp->SetRelativeLocation(FVector(0.0f));
	HeadsetMeshComp->SetStaticMesh(HeadsetMesh.Object);
	HeadsetMeshComp->bOwnerNoSee = true; // Do not render the headset for the player

	// Initialize left controller mesh
	LeftControllerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Controller Mesh"));
	LeftControllerMesh->SetupAttachment(LeftController);
	LeftControllerMesh->SetRelativeLocation(FVector(0.0f));
	LeftControllerMesh->SetStaticMesh(ControllerMesh.Object);

	// Initialize right controller mesh
	RightControllerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Controller Mesh"));
	RightControllerMesh->SetRelativeScale3D(FVector(1.0f, -1.0f, 1.0f)); // So that we don't have two left hands
	RightControllerMesh->SetupAttachment(RightController);
	RightControllerMesh->SetRelativeLocation(FVector(0.0f));
	RightControllerMesh->SetStaticMesh(ControllerMesh.Object);

	

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	// Oculus / Vive handle their camera location relative to the ground;
	// PS VR handles it from eye level
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("RightTrigger", this, &AVRPawn::RightTrigger);
	PlayerInputComponent->BindAxis("LeftTrigger", this, &AVRPawn::LeftTrigger);

}

void AVRPawn::RightTrigger(float Val)
{
	if (Val >= WeaponSensitivity && !isHoldingRightTrigger)
	{
		isHoldingRightTrigger = true;
		WeaponTracing(RightController, Val);
	}
	else if (Val < WeaponSensitivity && isHoldingRightTrigger)
	{
		isHoldingRightTrigger = false;
	}
}

void AVRPawn::LeftTrigger(float Val)
{
	if (Val >= WeaponSensitivity && !isHoldingLeftTrigger)
	{
		isHoldingLeftTrigger = true;
		WeaponTracing(LeftController, Val);
	}
	else if (Val < WeaponSensitivity && isHoldingLeftTrigger)
	{
		isHoldingLeftTrigger = false;
	}
}

void AVRPawn::WeaponTracing(UMotionControllerComponent* Controller, 
	float Sensitivity)
{
	// Make sure firing sensitivity is valid
	Sensitivity = FMath::Clamp(Sensitivity, 0.0f, 1.0f);

	

	// Trace parameters
	FVector TraceStart = Controller->GetComponentLocation() + (Controller->GetForwardVector() * TracingOffset);
	FVector TraceEnd   = Controller->GetComponentLocation() + (Controller->GetForwardVector() * WeaponRange);
	FHitResult Hit;

	// Actual ray tracing call
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, 
		ECollisionChannel::ECC_Visibility);



	// Some Debug Stuff
	UE_LOG(LogTemp, Log, TEXT("Firing from %s | Sensitivity: %f"),
		*Controller->GetName(), Sensitivity);

	if(DebugDrawWeaponRays)
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd,	FColor(0, 0, 255 * Sensitivity), false, -1.0f, 0, 3.0f);



	if (Hit.bBlockingHit)
	{
		// Some Debug Stuff
		UE_LOG(LogTemp, Log, TEXT("Blocking hit!"));
		UE_LOG(LogTemp, Log, TEXT("Hit Component: %s | Hit location: %s"), 
			*Hit.GetComponent()->GetName(), *Hit.Location.ToString());

		if (DebugDrawWeaponHits)
			DrawDebugSphere(GetWorld(), Hit.Location, 8.0f, 4, FColor(255, 0, 0));


		// Check if actor is a Shootable actor
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UShootableInterface::StaticClass()))
		{
			UE_LOG(LogTemp, Log, TEXT("Hit a shootable actor \"%s\"!"), *Hit.GetActor()->GetName());

			// How to call the interface function, as per Discord
			// Docs say otherwise, but the docs say to do it in a way that doesn't compile
			IShootableInterface::Execute_OnShot(Hit.GetActor());
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Actor \"%s\" is not shootable!"), *Hit.GetActor()->GetName());
		}
	}
}