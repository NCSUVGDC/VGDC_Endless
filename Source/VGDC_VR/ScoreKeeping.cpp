// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreKeeping.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFilemanager.h"


// Sets default values
AScoreKeeping::AScoreKeeping()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Returns an array of FStrings representing players and their high scores
void AScoreKeeping::GetHighScores(FString filename, TArray<UScoreContainer*>& highScores)
{
	FString savedDir = FPaths::GameSavedDir();

	FString pathToFile = savedDir + "/" + filename + ".csv";

	FString leaderboardEntries;
	TArray<FString>namesAndScores;
	if (FPaths::FileExists(pathToFile))
	{
		//Get all highscores on file 
		FFileHelper::LoadFileToString(leaderboardEntries, *pathToFile);
		leaderboardEntries.ParseIntoArray(namesAndScores, TEXT("\n"));

		UE_LOG(LogTemp, Display, TEXT("The leaderboard entries are: %s"), *leaderboardEntries);
		

		// And then add them to the TMap
		for (int32 i = 0; i < namesAndScores.Num(); i++)
		{
			FString currentLine = namesAndScores[i];
			// Find comma location
			int32 commaIndex = currentLine.Find(","); 
			// Parse Player name and highscore from string
			FString playerName = currentLine.Left(commaIndex);
			int32 playerScore = FCString::Atoi(*currentLine.Right(commaIndex));
			// Make an leaderboard entry object
			UScoreContainer* entry = CreateLeaderboardEntry(playerName, playerScore);

			highScores.Add(entry);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to open leaderboard file: %s"), *filename);
	}

}

// Retrieves any existing high scores from file and readjusts them with the current high score in mind
// and rewrites them to the file
void AScoreKeeping::AddHighScore(FString filename, UScoreContainer* newEntry)
{
	FString savedDir = FPaths::GameSavedDir();

	FString pathToFile = savedDir + "/" + filename + ".csv";	
	
	// Retrieve all the current high scores
	// TODO: Should we be re-loading each time? Seems kinda overkill.
	//GetHighScores(filename, leaderboard);
	
	UE_LOG(LogTemp, Log, TEXT("Adding new high score: %s"), *newEntry->ToString());

	// Add new leaderboard entry to list of high scores
	leaderboard.Add(newEntry);
	
	// Sorts leaderboard entries
	leaderboard.Sort();
	
	// Remove low scores if leaderboard is full
	if (leaderboard.Num() > leaderboardMax)
	{
		UE_LOG(LogTemp, Log, TEXT("Board full! Popping lowest high score: %s"), *leaderboard[leaderboardMax - 1]->ToString());
		leaderboard.RemoveAt(leaderboardMax - 1);
	}
	

	
}

void AScoreKeeping::AddHighScores(FString fileName, TArray<UScoreContainer*> newEntries)
{
	for(UScoreContainer* newEntry : newEntries)
		AddHighScore(fileName, newEntry);


	// TODO: Here below is auto-writing the file. This should be moved to a separate function.
	
	FString fileNameAndPath = FPaths::GameSavedDir() + "/" + fileName + ".csv";

	FString leaderboardAsString = "";	

	// Convert leaderboard entries to string 
	for (int32 i = leaderboard.Num() - 1; i >= 0; i--)
	{
		UScoreContainer* currentEntry = leaderboard[i];

		leaderboardAsString += currentEntry->ToString() + "\n";
	}

	// If file exists
	if (FPaths::FileExists(fileNameAndPath))
		//Clear file
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*fileNameAndPath);

	// Save concatenated string to file
	FFileHelper::SaveStringToFile(leaderboardAsString, *fileNameAndPath);

	UE_LOG(LogTemp, Display, TEXT("Saved at %s"), *leaderboardAsString);
}

void AScoreKeeping::TestWrite(FString fileName, UScoreContainer* whatToWrite)
{
	FString fileNameAndPath = FPaths::GameSavedDir() + "/" + fileName + ".csv";
	
	FFileHelper::SaveStringToFile(whatToWrite->ToString(), *fileNameAndPath);
}

UScoreContainer* AScoreKeeping::CreateLeaderboardEntry(FString username, int32 highscore)
{
	UScoreContainer* newScore = NewObject<UScoreContainer>();
	newScore->SetNameAndScore(username, highscore);
	UE_LOG(LogTemp, Log, TEXT("Created new score entry: %s"), *newScore->ToString());
	return newScore;
}

bool AScoreKeeping::isNewHighScore(int32 _score)
{
	// High score by default if leaderboard isn't full
	if (leaderboard.Num() <= leaderboardMax)
		return true;
	else // Check if current score is higher than any of the leaderboard scores
		for (int i = leaderboard.Num() - 1; i >= 0; i--)
			if (leaderboard[i]->score < _score)
				return true;
	
	return false;
}

// Called when the game starts or when spawned
void AScoreKeeping::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AScoreKeeping::bFileExists(FString filename)
{
	return FPaths::FileExists(filename);
}

// Called every frame
void AScoreKeeping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



