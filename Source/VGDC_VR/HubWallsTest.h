// Fill out your copyright notice in the Description page of Project Settings.
using namespace UF;
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HubWallsTest.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VGDC_VR_API UHubWallsTest : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHubWallsTest(); // Sets default values for this component's properties

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Hub")
	static float KeepDegreesUnder180(float deg);
		
public:
	UFUNCTION(BlueprintPure, Category = "Hub")
	static bool NearlyEqualDegrees(float deg1,float deg2, float tolerance);
	
};
