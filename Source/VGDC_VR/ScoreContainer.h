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
	UFUNCTION(BlueprintPure, Category = "Score Container")
		static UScoreContainer* CreateScoreContainer(FString Name, int32 Score);

	UFUNCTION( BlueprintPure, Category = "Score Container", META = (AdvancedDisplay="0") )
		static UScoreContainer* CreateRandomScoreContainer(
			int32 NameMinLength = 3, int32 NameMaxLength = 3, 
			int32 ScoreMin = 1000, int32 ScoreMax = 9999999);

	// Changes the character of the name at the given index
	UFUNCTION(BlueprintCallable, Category = "Score Container")
		void SetNameCharacter(int Index, FString Character);

	// Turns class into a string
	UFUNCTION(BlueprintPure, Category = "Score Container")
		FString ToString();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Score Container")
		FString name = "Bob";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Score Container", META = (ClampMin = 0, UIMin = 0, UIMax = 99999))
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
		return score == container.score && name.Equals(container.name);
	}


};
