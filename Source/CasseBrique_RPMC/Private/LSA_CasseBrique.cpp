// Fill out your copyright notice in the Description page of Project Settings.


#include "LSA_CasseBrique.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void ALSA_CasseBrique::BeginPlay()
{
	Super::BeginPlay();

	//Find the actor that handles control for the local player.
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if(IsValid(MainCamera))
	{
		//Cut instantly to our actor on begin play.
		OurPlayerController->SetViewTarget(MainCamera);
		OurPlayerController->SetShowMouseCursor(false);
	}
}
