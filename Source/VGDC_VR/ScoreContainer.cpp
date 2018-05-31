// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreContainer.h"


void UScoreContainer::SetNameAndScore(FString _name, int32 _score)
{
	name = _name;
	score = _score;
}

FString UScoreContainer::ToString()
{
	return name + "," + FString::FromInt(score);
}


UScoreContainer* UScoreContainer::CreateScoreContainer(FString Name, int32 Score)
{
	UScoreContainer* newScore = NewObject<UScoreContainer>();
	newScore->SetNameAndScore(Name, Score);
	UE_LOG(LogTemp, Log, TEXT("Created new score container: %s"), *newScore->ToString());
	return newScore;
}
