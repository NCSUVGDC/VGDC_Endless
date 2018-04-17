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
	// Sets default values for this actor's properties
	AScoreKeeping();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns an array of FStrings representing players and their high scores
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
	void GetHighScores(FString filename, TArray<UScoreContainer*>& highScores);

	// Retrieves any existing high scores from file and readjusts them with the current high score in mind
	// and rewrites them to the file
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
	void AddHighScore(FString filename, UScoreContainer* newEntry);

	// Adds Leaderboard to file
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
	void AddHighScores(FString fileName, TArray<UScoreContainer*> newEntries);

	// Test function to write to a file
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
	void TestWrite(FString fileName, UScoreContainer* whatToWrite);

	// Creates a ScoreContainer UObject representing the player's name and score
	UFUNCTION(BlueprintPure, Category = "Score Keeping")
	UScoreContainer* CreateLeaderboardEntry(FString _name, int32 _score);

	// Checks if file exists
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
	bool bFileExists(FString filename);

	// Checks if there is a new high score
	UFUNCTION(BlueprintCallable, Category = "Score Keeping")
	bool isNewHighScore(int32 _score);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Maximum leaderboard entries
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Score Keeping")
	int leaderboardMax = 5;

	// Contains Players' Name and Score
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score Keeping")
	TArray<UScoreContainer*> leaderboard;
	

	
};
