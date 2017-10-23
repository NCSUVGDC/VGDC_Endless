// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "CrystalComponent.generated.h"

/**
 * A Crystal which tracks its own hit points and has an accompanying mesh.
 *
 * This was done in C++ rather than Blueprints because I could not find any 
 *   means of adding a mesh to a blueprint Scene Component.
 */
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VGDC_VR_API UCrystalComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	//UStaticMeshComponent* CrystalMesh;

	// Used to make sure we don't generate multiple crystals with the same name,
	//   which causes all sorts of undefined behavior.
	static int32 CrystalNumber;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UCrystalComponent();
	virtual void PostInitProperties() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Hit points left on this crystal
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Crystal",
		META = (UIMin = 0, UIMax = 16, ClampMin = 0))
		int32 HitPoints = 1;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Crystal")
	//	UStaticMeshComponent* CrystalMesh;

	// Mesh to use for this component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Crystal")
		UStaticMesh* MeshAsset;

	// Material to use for this component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Crystal")
		UMaterial* MaterialAsset;

	/**
	 * Use this to update the crystal's material 
	 * @param NewMaterial - Material to use
	 */
	UFUNCTION(BlueprintCallable, Category = "Crystal")
		void UpdateCrystalMaterial(UMaterialInterface* NewMaterial);

	/**
	 * A UE4 bug causes meshes attached to components to never be in the right 
	 *   spot. This function fixes that, and must be called every time the 
	 *   crystal is moved! 
	 */
	UFUNCTION(BlueprintCallable, Category = "Crystal")
		void ResetMeshTransform();

	/**
	 * Use this to spawn new crystals, as doing so in blueprints with Add
	 *   Component doesn't work as expected.
	 *
	 * @param OwningActor - Actor to "own" the new crystal. Usually a door.
	 * @param OwningComponent - Usually the door's mesh.
	 * @param InitialHP - Initial Hit Points of the new crystal
	 * @param CrystalClass - Class of crystal to use. This can be the base class, or any custom Blueprint classes.
	 * @Param AttachToSocket - Socket on the AttachToComponent this crystal should snap to.
	 * @return a new crystal with the given parameters
	 */
	UFUNCTION(BlueprintCallable, Category = "Crystal")
		static UCrystalComponent* SpawnCrystalComponent(
			AActor* OwningActor,
			USceneComponent* OwningComponent,
			int32 InitialHP,
			TSubclassOf<UCrystalComponent> CrystalClass,
			FName AttachToSocket = FName(""));
};
