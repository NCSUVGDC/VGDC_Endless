// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VGDC_VRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VGDC_VR_API AVGDC_VRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game Mode Base")
	void ResetCurrentLevel();
	
	
};
