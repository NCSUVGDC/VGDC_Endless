// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PowerCell.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shootable.generated.h"

UCLASS()
class VGDC_VR_API AShootable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootable();

private:	
	// If true lets tick function move bullet
	bool targetSet = false;
	// Starting point of the bullet
	FVector source;
	// Ending point the bullet is moving towards
	FVector target;
	// Total time passed since bullet has been fired
	float totalTime = 0;
	// if set power will take damage
	APowerCell* powerCellToDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Moves bullet towards target from the source parameter
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Fire Shoot Pew"))
	FVector LerpedFirePoint(float delta);

	// Fires bullet towards target from source
	// TODO: Have this function call particle effects for initial blast
	void Fire(FVector startPoint, FVector endPoint);

	void Fire(FVector startPoint, FVector endPoint, APowerCell* pcTarget);

	// Handles Garbage Collection on bullet
	void DestroyBullet();

	// Determines how fast bullet will travel
	// Equation used: Speed = distance/time
	// This fulfills the time parameter
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float bulletSpeed = 2500.0f;
	
	
};
