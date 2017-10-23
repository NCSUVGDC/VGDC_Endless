// Fill out your copyright notice in the Description page of Project Settings.

#include "CrystalComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

// Since we can't do this in the header...
int32 UCrystalComponent::CrystalNumber = 0;

// Sets default values for this component's properties
UCrystalComponent::UCrystalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	/// Crystal Mesh Setup
	// Crystal Mesh Boilerplate
	//CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal Mesh"));
	//CrystalMesh->AttachTo(this);
	//CrystalMesh->RegisterComponentWithWorld(GetWorld());
	//CrystalMesh->RegisterComponent();
}

void UCrystalComponent::PostInitProperties()
{
	Super::PostInitProperties();

	/*if (MeshAsset)
	{
		CrystalMesh->SetStaticMesh(MeshAsset);

		if (MaterialAsset)
			CrystalMesh->SetMaterial(0, MaterialAsset);
		else
			UE_LOG(LogTemp, Error, TEXT("Crystal has no material asset specified!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Crystal has no mesh asset specified!"));
	}*/
}

void UCrystalComponent::BeginPlay()
{
	Super::BeginPlay();

	// Transform must be updated after being generated because of a UE4 bug
	// TODO: Report this bug!
	ResetMeshTransform();
}

void UCrystalComponent::UpdateCrystalMaterial(UMaterialInterface* NewMaterial)
{
	//if (NewMaterial != nullptr)
		//CrystalMesh->SetMaterial(0, MaterialAsset);
	//else
	//	UE_LOG(LogTemp, Error, TEXT("New material is null!"));
}

void UCrystalComponent::ResetMeshTransform()
{
	//CrystalMesh->SetRelativeLocation(FVector(0.0001f));
	//CrystalMesh->SetRelativeRotation(FRotator(0.0001f));
	//CrystalMesh->SetRelativeScale3D(FVector(1.0001f));
}

UCrystalComponent* UCrystalComponent::SpawnCrystalComponent(AActor* OwningActor,
	USceneComponent* OwningComponent, int32 InitialHP,
	TSubclassOf<UCrystalComponent> CrystalClass, FName AttachToSocket)
{
	UCrystalComponent* Crystal = NewObject<UCrystalComponent>(
		OwningActor, CrystalClass, FName(*FString::Printf(TEXT("Crystal%d"), CrystalNumber++)));
	if (!Crystal)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn new crystal! "));
		return nullptr;
	}

	Crystal->RegisterComponent();
	//Crystal->AttachTo(OwningComponent);
	Crystal->AttachToComponent(OwningComponent,
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), AttachToSocket);
	Crystal->HitPoints = InitialHP;
	Crystal->ResetMeshTransform();

	return Crystal;
}

// Called every frame
void UCrystalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

