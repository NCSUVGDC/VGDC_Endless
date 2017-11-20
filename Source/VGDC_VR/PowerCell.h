// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerCell.generated.h"

UENUM(BlueprintType)
enum class EColorsEnum : uint8
{
	VE_RED    UMETA(DisplayName="Red"),
	VE_GREEN  UMETA(DisplayName="Green"),
	VE_BLUE   UMETA(DisplayName="Blue"),
	VE_YELLOW UMETA(DisplayName="Yellow")
};

UCLASS()
class VGDC_VR_API APowerCell : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APowerCell();
	// "Destroys" this power cell
	void DestroyCell();
	// Applies damage to the power cell
	void DamagePowerCell(int hitsOfDamage);
	// Updates Color of power cell based on its health
	UFUNCTION(BlueprintCallable, Category = "PowerCell", meta=(Keywords="Change Color of Cell Health"))
	void UpdateColorOfCell();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Enumeration variable used to change power cell color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EColorsEnum colorsEnum;
	// Material instance of the power cell
	TSubclassOf<UMaterialInstance> material;
private:
	int cellHealthPoints = 3;
	
};
