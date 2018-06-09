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

	// Checks if there is a new high score
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Score Keeping")
		bool IsNewHighScore(int32 Score) const;

	// Maximum leaderboard entries
	// Lowest scores will be popped off if necessary to make room for new ones
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Score Keeping")
		int MaxEntries = 10;

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
