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
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VGDC_VR_API UCrystalComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	// Must be found in constructor, but can't be used until PostInitProperties
	UStaticMesh* MeshAsset;
	UMaterialInterface* MaterialAsset;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UCrystalComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Hit points left on this crystal
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Crystal",
		META = (UIMin = 0, UIMax = 16, ClampMin = 0, ExposeOnSpawn = "true"))
		int32 HitPoints = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Crystal")
		UStaticMeshComponent* CrystalMesh;

	/**
	 * A UE4 bug causes meshes attached to components to never be in the right 
	 *   spot. This function fixes that, and must be called every time the 
	 *   crystal is moved! 
	 */
	UFUNCTION(BlueprintCallable, Category = "Crystal")
		void ResetMeshTransform();
};
