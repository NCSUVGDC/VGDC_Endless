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



