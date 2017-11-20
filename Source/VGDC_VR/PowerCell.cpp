// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerCell.h"


// Sets default values
APowerCell::APowerCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Damages Power cell, causing it to change color
// and eventually become destroyed
void APowerCell::DamagePowerCell(int hitsOfDamage)
{
	// if power cell has no more health points
	if (cellHealthPoints <= hitsOfDamage)
	{
		// "Destroy" it
		cellHealthPoints = 0;

		DestroyCell();
	}
	else
	{
		cellHealthPoints -= hitsOfDamage;
		// Update Power cell color
		UpdateColorOfCell();
	}
}

// "Destroys" Power Cell
void APowerCell::DestroyCell()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void APowerCell::UpdateColorOfCell()
{
	FName powerCellName = FName(TEXT("PowerCell"));
	UStaticMeshComponent* powerCellMesh = (UStaticMeshComponent*)GetOwner()->GetDefaultSubobjectByName(powerCellName);
	

	colorsEnum = (EColorsEnum)cellHealthPoints;

	// Set Material to Red
	if (colorsEnum == EColorsEnum::VE_RED)
		material->SetVectorParameterByIndexInternal(0, FColor(1.0f, 0, 0, 1.0f));

	// Set Material to Blue
	if (colorsEnum == EColorsEnum::VE_BLUE)
		material->SetVectorParameterByIndexInternal(0, FColor(0, 0, 1.0f, 1.0f));

	// Set Material to Green
	if (colorsEnum == EColorsEnum::VE_GREEN)
		material->SetVectorParameterByIndexInternal(0, FColor(0, 1.0f, 0, 1.0f));

	// Set Material to Red
	if (colorsEnum == EColorsEnum::VE_YELLOW)
		material->SetVectorParameterByIndexInternal(0, FColor(1.0f, 1.0f, 0, 1.0f));
}