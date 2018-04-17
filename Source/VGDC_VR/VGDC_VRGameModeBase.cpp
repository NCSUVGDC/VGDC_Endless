// Fill out your copyright notice in the Description page of Project Settings.

#include "VGDC_VRGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AVGDC_VRGameModeBase::ResetCurrentLevel()
{	
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}
