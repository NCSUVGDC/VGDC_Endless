// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreContainer.h"
#include "ScoreKeeping.generated.h"




UCLASS()
class VGDC_VR_API AScoreKeeping : public AActor
{
	GENERATED_BODY()
	
public:	
	AScoreKeeping();

	virtual void BeginDestroy() override;

	// Loads the given file's list of scores into this leaderboard
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
		void LoadLeaderboard(FString inFilename = "");

	// Adds a new high score to the leaderboard
	// @return Whether or not this value was a new high score (or if it was just discarded!)
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
		bool AddHighScore(FString Name, int32 Score);

	// Adds a new high score to the leaderboard
	// @return Whether or not this value was a new high score (or if it was just discarded!)
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
		bool AddHighScoreContainer(UScoreContainer* NewEntry);

	// Saves leaderboard to file, overwriting old file by default
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
		void SaveLeaderboard(FString inFilename = "");

	// Sorts descending
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
		void Sort();

	// Checks if the given score is greater than the score at place HighScoreCount
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Score Keeping")
		bool IsNewHighScore(int32 Score) const;

	// Top N scores are considered high scores
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Score Keeping",
		META = (ClampMin = 1, ClampMax = 100, UIMax = 50))
		int HighScoreCount = 10;

	// Should this score keeper automatically save when destroyed?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Keeping")
		bool Autosave = true;

	// Name of file to autosave to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Keeping")
		FString Filename = "leaderboards";

	// Sorted array of scores
	// Read-Only b/c you should use the AddEntry method
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score Keeping")
		TArray<UScoreContainer*> Leaderboard;
	

	
};
