// Fill out your copyright notice in the Description page of Project Settings.

#include "Shootable.h"


// Sets default values
AShootable::AShootable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (targetSet && totalTime <= 1.0f)
		this->SetActorLocation(LerpedFirePoint(DeltaTime));
	else if (totalTime > 1.0f)
		Destroy();
}

void AShootable::Fire(FVector startPoint, FVector endPoint)
{
	source = startPoint;
	target = endPoint;
	targetSet = true;
}

FVector AShootable::LerpedFirePoint(float delta)
{
	float fDistance = FVector::Distance(source, target);
	// Increment the time delta the scalar of the bullet speed
	// with respect to the distance between the two points 
	/*FOR EXAMPLE:
		time / distance = 1 mph

		THEREFORE,
		IF: 
		bulletSpeed = 5

		time / distance * bulletspeed = 5mph
	*/
	totalTime += delta / fDistance * bulletSpeed;
		
	return source + (target - source) * totalTime;

}
