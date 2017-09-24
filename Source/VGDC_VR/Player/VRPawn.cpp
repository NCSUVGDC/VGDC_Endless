// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Runtime/Engine/Classes/Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
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
	UStaticMeshComponent* LeftControllerMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Controller Mesh"));
	LeftControllerMeshComp->SetupAttachment(LeftController);
	LeftControllerMeshComp->SetRelativeLocation(FVector(0.0f));
	LeftControllerMeshComp->SetStaticMesh(ControllerMesh.Object);

	// Initialize right controller mesh
	UStaticMeshComponent* RightControllerMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Controller Mesh"));
	RightControllerMeshComp->SetRelativeScale3D(FVector(1.0f, -1.0f, 1.0f)); // So that we don't have two left hands
	RightControllerMeshComp->SetupAttachment(RightController);
	RightControllerMeshComp->SetRelativeLocation(FVector(0.0f));
	RightControllerMeshComp->SetStaticMesh(ControllerMesh.Object);

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
	UE_LOG(LogTemp, Log, TEXT("%f"), Val);

	if (Val > 0.01f)
	{
		DrawDebugLine(GetWorld(), RightController->GetComponentLocation(),
			RightController->GetComponentLocation() + RightController->GetForwardVector() * TriggerBeamLength,
			FColor(0, 255 * Val, 0), false, -1.0f, 0, 2.5f);
		
	}
}

void AVRPawn::LeftTrigger(float Val)
{
	if (Val > 0.01f)
	{
		DrawDebugLine(GetWorld(), LeftController->GetComponentLocation(),
			LeftController->GetComponentLocation() + LeftController->GetForwardVector() * TriggerBeamLength,
			FColor(0, 0, 255 * Val), false, -1.0f, 0, 2.5f);
	}
}