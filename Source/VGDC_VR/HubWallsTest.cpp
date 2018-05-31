// Fill out your copyright notice in the Description page of Project Settings.

#include "HubWallsTest.h"


// Sets default values for this component's properties
UHubWallsTest::UHubWallsTest()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHubWallsTest::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHubWallsTest::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*float UHubWallsTest::KeepDegreesUnder180(float deg)
{
	while (deg > 180)
		deg = deg - 360;
	while (deg < -180)
		deg = deg + 360;
	if (deg > -180.1f && deg < -179.9f) // (x > -180) and (x < -180)?  
		deg = 180.0000f;
	return deg;
}*/

/*
bool UHubWallsTest::NearlyEqualDegrees(float deg1, float deg2, float tolerance)
{
	if (deg2 > (deg1 - tolerance) && deg2 < (deg1 + tolerance))
	{
		return true;
	}
	else
	if (deg1 > 179.9f && deg1 < 180.1f)
	{
		return UHubWallsTest::NearlyEqualDegrees(-180.0f, deg2, tolerance);
	}
		
	return false;
}*/