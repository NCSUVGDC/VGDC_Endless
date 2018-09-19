// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "Runtime/UMG/Public/Components/WidgetInteractionComponent.h"
#include "VRPawn.generated.h"

/**
 * Basic VR-ready player pawn
 *
 * Contains all necessary code for head tracking, controller tracking and input,
 *   etc.
 */
UCLASS()
class VGDC_VR_API AVRPawn : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	AVRPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Acts as a root component for the camera and controllers
	// May not actually be necessary, but the VR template recommended it
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
		USceneComponent* VROrigin;

	// Player's camera
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
		UCameraComponent* Camera;

	// Motion controller for the left hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components|Left Hand")
		UMotionControllerComponent* LeftController;

	// Hand some weird crap happening with the engine not letting us assign meshes
	// Moved to purely BP
	// Mesh for player's the left hand
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components|Left Hand")
	//	USkeletalMeshComponent* LeftControllerMesh;

	// Component needed to allow the VR controllers to interact with 
	//   UMG widgets
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components|Left Hand")
		UWidgetInteractionComponent* LeftControllerInteractor;

	// Motion controller for the right hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components|Right Hand")
		UMotionControllerComponent* RightController;
	
	// Hand some weird crap happening with the engine not letting us assign meshes
	// Moved to purely BP
	// Mesh for player's the right hand
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components|Right Hand")
	//	USkeletalMeshComponent* RightControllerMesh;

	// Component needed to allow the VR controllers to interact with 
	//   UMG widgets
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components|Right Hand")
		UWidgetInteractionComponent* RightControllerInteractor;

	// If true, we'll draw lines from the player's controllers when firing
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug",
		META = (DisplayName = "Draw Weapon Rays"))
		bool DebugDrawWeaponRays = true;

	// If true, we'll draw spheres where the player's weapons hit
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug",
		META = (DisplayName = "Draw Weapon Hits"))
		bool DebugDrawWeaponHits = true;
};
