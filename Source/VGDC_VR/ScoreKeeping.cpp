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

}

// Retrieves any existing high scores from file and readjusts them with the current high score in mind
// and rewrites them to the file
void AScoreKeeping::AddHighScore(FString filename, UScoreContainer* newEntry)
{
	FString savedDir = FPaths::GameSavedDir();

	FString pathToFile = savedDir + "/" + filename + ".csv";	
	
	// Retrieve all the current high scores
	GetHighScores(filename, leaderboard);
	
	// Add new leaderboard entry to list of high scores
	leaderboard.Add(newEntry);
	
	// Sorts leaderboard entries
	leaderboard.Sort();
	

	// If the number of entries in the leaderboard are more than its max
	if (leaderboard.Num() > leaderboardMax)
		// Remove the lowest score
		leaderboard.RemoveAt(leaderboardMax - 1);
	

	
}

void AScoreKeeping::AddHighScores(FString fileName, TArray<UScoreContainer*> newEntries)
{
	FString fileNameAndPath = FPaths::GameSavedDir() + "/" + fileName + ".csv";

	leaderboard.Append(newEntries);

	leaderboard.Sort();

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

UScoreContainer * AScoreKeeping::CreateLeaderboardEntry(FString username, int32 highscore)
{
	UScoreContainer* temp = NewObject<UScoreContainer>();
	temp->SetNameAndScore(username, highscore);
	return temp;
}

bool AScoreKeeping::isNewHighScore(int32 _score)
{
	// If no leaderboard entries
	if (leaderboard.Num() <= 0)
		// New High Score
		return true;
	// Else if there are leaderboard entries
	else
		// Check if current score is higher than any of the leaderboard scores
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



