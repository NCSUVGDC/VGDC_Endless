// Fill out your copyright notice in the Description page of Project Settings.

#include "CrystalComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

// Sets default values for this component's properties
UCrystalComponent::UCrystalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	/// Crystal Mesh Setup
	// Crystal Mesh Boilerplate
	CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal Mesh"));
	CrystalMesh->SetupAttachment(this);
	CrystalMesh->RegisterComponentWithWorld(GetWorld());

}

void UCrystalComponent::BeginPlay()
{
	Super::BeginPlay();

	// Transform must be updated after being generated because of a UE4 bug
	// TODO: Report this bug!
	CrystalMesh->SetRelativeLocation(FVector(0.0001f));
	CrystalMesh->RegisterComponentWithWorld(GetWorld());
}


// Called every frame
void UCrystalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

