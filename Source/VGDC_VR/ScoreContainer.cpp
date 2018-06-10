// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreContainer.h"


FString UScoreContainer::ToString()
{
	return name + "," + FString::FromInt(score);
}

UScoreContainer* UScoreContainer::CreateScoreContainer(FString Name, int32 Score)
{
	UScoreContainer* newScore = NewObject<UScoreContainer>();
	newScore->name = Name;
	newScore->score = Score;
	return newScore;
}

UScoreContainer* UScoreContainer::CreateRandomScoreContainer(
	int32 NameMinLength, int32 NameMaxLength,  int32 ScoreMin, int32 ScoreMax)
{
	// Generate random A-Z name
	int32 NameLength = FMath::RandRange(NameMinLength, NameMaxLength);
	char* NameArray = new char[NameLength + 1];

	for (int i = 0; i <= NameLength; i++)
	{
		NameArray[i] = FMath::RandRange(65, 90); // Random A-Z (see ASCII table)
	}

	NameArray[NameLength] = '\0'; // Have to manually add terminator this way

	return UScoreContainer::CreateScoreContainer(FString(ANSI_TO_TCHAR(NameArray)), 
		FMath::RandRange(ScoreMin, ScoreMax));
}
