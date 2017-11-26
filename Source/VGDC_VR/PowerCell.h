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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Enum)
	EColorsEnum colorsEnum;
	// Sets default values for this actor's properties
	APowerCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
