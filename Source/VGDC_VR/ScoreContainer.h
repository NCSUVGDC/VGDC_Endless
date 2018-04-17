// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreContainer.generated.h"
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup="Custom Classes")
class VGDC_VR_API UScoreContainer: public UObject
{

	GENERATED_BODY()

public:
	// Sets the score and name for the ScoreContainer object
	UFUNCTION(BlueprintCallable, Category = "Score Container")
	void SetNameAndScore(FString _name, int32 _score);
	// Turns class into a string
	UFUNCTION(BlueprintPure, Category = "Score Container")
	FString ToString();


public:
	FString name = "Bob";
	int32 score = 500;
	FORCEINLINE bool operator>(const UScoreContainer& container) const
	{
		if (score == container.score)
			return name > container.name;
		else
			return score > container.score;
	}

	FORCEINLINE bool operator<(const UScoreContainer& container) const
	{
		if (score == container.score)
			return name < container.name;
		else
			return score < container.score;
	}

	FORCEINLINE bool operator==(const UScoreContainer & container) const
	{
		return score == container.score && name == container.name;
	}


};
