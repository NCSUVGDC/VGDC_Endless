// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h"
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

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
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
	// Can't get UMotionControllerComponent to work with UPROPERTY. Looking into it.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UMotionControllerComponent* LeftController;

	// Motion controller for the right hand
	// Can't get UMotionControllerComponent to work with UPROPERTY. Looking into it.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UMotionControllerComponent* RightController;

	// How far out the beam should fly out from the controller
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Controllers")
		float TriggerBeamLength = 6000.0f;
};
