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
