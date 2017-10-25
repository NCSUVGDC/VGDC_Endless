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

private:
	/**
	 * Helper function that handles the tracing and damage of a weapon when
	 *   fired from a controller.
	 * Has an optional parameter for how hard the trigger was pulled down. If
	 *   sensitivity is not given, it defaults to 1.0
	 *
	 * @param Controller - Controller to fire from (Left or Right)
	 * @param Sensitivity - How hard the trigger was pulled [0..1]
	 */
	void WeaponTracing(UMotionControllerComponent* Controller, float Sensitivity = 1.0f);

	// How far from the controller we start tracing
	// Helps prevent us from hitting the controller
	float TracingOffset = 5.0f;

	// Set to true when the player pulls the trigger past the threshold,
	//   set to false when the player releases the trigger past the threshold
	// This way the player only fires once per trigger pull
	bool isHoldingRightTrigger = false;
	bool isHoldingLeftTrigger = false;

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

	/**
	 * Called when the right hand trigger is pulled at all
	 * 
	 * @param Val - How far the trigger is held down
	 */
	UFUNCTION(BlueprintCallable, Category = "Input")
		void RightTrigger(float Val);

	/**
	 * Called when the left hand trigger is pulled at all
	 *
	 * @param Val - How far the trigger is held down
	 */
	UFUNCTION(BlueprintCallable, Category = "Input")
		void LeftTrigger(float Val);

	// Acts as a root component for the camera and controllers
	// May not actually be necessary, but the VR template recommended it
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USceneComponent* VROrigin;

	// Player's camera
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UCameraComponent* Camera;

	// Motion controller for the left hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UMotionControllerComponent* LeftController;

	// Component needed to allow the VR controllers to interact with 
	//   UMG widgets
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UWidgetInteractionComponent* LeftControllerInteractor;

	// Motion controller for the right hand
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UMotionControllerComponent* RightController;

	// Component needed to allow the VR controllers to interact with 
	//   UMG widgets
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UWidgetInteractionComponent* RightControllerInteractor;

	// How far the player has to pull on the trigger to fire
	// Once this threshold is crossed, the weapon fires once
	// When the trigger is loosened below this value, the gun can be fired again
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon",
		META = (ClampMin = 0.0001f, ClampMax = 1.0f))
		float WeaponSensitivity = 0.25f;

	// How far we'll track the player's fire
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon",
		META = (UIMin = 100.0f, UIMax = 10000000.0f))
		float WeaponRange = 6000.0f;

	// If true, we'll draw lines from the player's controllers when firing
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug",
		META = (DisplayName = "Draw Weapon Rays"))
		bool DebugDrawWeaponRays = true;

	// If true, we'll draw spheres where the player's weapons hit
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug",
		META = (DisplayName = "Draw Weapon Hits"))
		bool DebugDrawWeaponHits = true;
};
