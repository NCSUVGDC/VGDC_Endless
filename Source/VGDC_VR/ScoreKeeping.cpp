// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreKeeping.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFilemanager.h"
#include <functional> // For Sorting


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
	bool IsHighScore = IsNewHighScore(NewEntry->score);

	UE_LOG( LogTemp, Log, TEXT("Adding new %s: %s"), 
		IsHighScore ? TEXT("high score") : TEXT("(not high) score"), 
		*NewEntry->ToString() );

	// TODO THIS IS INSANELY INEFFICIENT
	Leaderboard.Add(NewEntry);
	Sort();
	
	return IsHighScore;
}

void AScoreKeeping::SaveLeaderboard(FString inFilename)
{
	// Default to actor filename if none specified
	if (inFilename.IsEmpty())
		inFilename = Filename;

	FString FullFilePath = FPaths::ProjectSavedDir() + "/" + inFilename + ".csv";

	FString LeaderboardAsString = "";	

	Sort();

	for (UScoreContainer* Entry : Leaderboard)
	{
		LeaderboardAsString += Entry->ToString() + "\n";
	}

	FFileHelper::SaveStringToFile(LeaderboardAsString, *FullFilePath);

	UE_LOG(LogTemp, Log, TEXT("Saved leaderboard with %d entries to file: %s"), Leaderboard.Num(), *FullFilePath);
}

void AScoreKeeping::Sort()
{
	Leaderboard.Sort<std::greater<UScoreContainer>>( std::greater<UScoreContainer>() );
}

bool AScoreKeeping::IsNewHighScore(int32 Score) const
{
	if (Leaderboard.Num() < HighScoreCount)
		return true;
	else
		return Score > Leaderboard[HighScoreCount - 1]->score;
}



