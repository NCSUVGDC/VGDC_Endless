// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreKeeping.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFilemanager.h"


// Sets default values
AScoreKeeping::AScoreKeeping()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AScoreKeeping::BeginDestroy()
{
	Super::BeginDestroy();

	if (Autosave)
	{
		if (Leaderboard.Num() <= 0)
		{
			UE_LOG(LogTemp, Log, TEXT("NOT autosaving leaderboard (zero entries!)"));
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("Autosaving leaderboard!"));
		SaveLeaderboard();
	}
}

// Returns an array of FStrings representing players and their high scores
void AScoreKeeping::LoadLeaderboard(FString inFilename)
{
	// Default to actor filename if none specified
	if (inFilename.IsEmpty())
		inFilename = Filename;

	FString PathToFile = FPaths::ProjectSavedDir() + "/" + inFilename + ".csv";

	if (FPaths::FileExists(PathToFile))
	{
		FString RawText;
		TArray<FString> CSVEntries;

		//Get all highscores on file 
		FFileHelper::LoadFileToString(RawText, *PathToFile);
		RawText.ParseIntoArray(CSVEntries, TEXT("\n"));

		UE_LOG(LogTemp, Log, TEXT("Loading %d entries from file %s..."), CSVEntries.Num(), *PathToFile);
		
		// And then add them to the TMap
		for (FString CSVEntry : CSVEntries)
		{
			TArray<FString> EntryValues;
			CSVEntry.ParseIntoArray(EntryValues, TEXT(","));

			// Parse Player name and highscore from string
			FString PlayerName = EntryValues[0];
			int32 PlayerScore = FCString::Atoi(*EntryValues[1]);
			
			AddHighScore(PlayerName, PlayerScore);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to open leaderboard file: %s"), *PathToFile);
	}

}

bool AScoreKeeping::AddHighScore(FString Name, int32 Score)
{
	return AddHighScoreContainer(UScoreContainer::CreateScoreContainer(Name, Score));
}

bool AScoreKeeping::AddHighScoreContainer(UScoreContainer* NewEntry)
{
	if (!IsNewHighScore(NewEntry->score))
	{
		UE_LOG(LogTemp, Log, TEXT("New score %d not a high score!"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Adding new high score: %s"), *NewEntry->ToString());

	Leaderboard.Add(NewEntry);
	
	Leaderboard.Sort();
	
	// Remove low score(s) if leaderboard is full
	while (Leaderboard.Num() > MaxEntries)
	{
		// TODO Pop removes the highest score. Work on sorting and popping and make sure order is making sense.
		UE_LOG(LogTemp, Log, TEXT("Board full! Popping lowest high score: %s"), *Leaderboard.Pop()->ToString());
	}

	return true;
}

void AScoreKeeping::SaveLeaderboard(FString inFilename)
{
	// Default to actor filename if none specified
	if (inFilename.IsEmpty())
		inFilename = Filename;

	FString FullFilePath = FPaths::ProjectSavedDir() + "/" + inFilename + ".csv";

	FString LeaderboardAsString = "";	

	Leaderboard.Sort();

	for (UScoreContainer* Entry : Leaderboard)
	{
		LeaderboardAsString += Entry->ToString() + "\n";
	}

	FFileHelper::SaveStringToFile(LeaderboardAsString, *FullFilePath);

	UE_LOG(LogTemp, Log, TEXT("Saved leaderboard with %d entries to file: %s"), Leaderboard.Num(), *FullFilePath);
}

bool AScoreKeeping::IsNewHighScore(int32 Score) const
{
	// High score by default if leaderboard isn't full
	if (Leaderboard.Num() <= MaxEntries)
		return true;
	else // Check if current score is higher than any of the leaderboard scores
		for (UScoreContainer* Entry : Leaderboard)
			if (Entry->score < Score)
				return true;
	
	return false;
}

/*bool AScoreKeeping::bFileExists(FString filename)
{
	return FPaths::FileExists(filename);
}*/



