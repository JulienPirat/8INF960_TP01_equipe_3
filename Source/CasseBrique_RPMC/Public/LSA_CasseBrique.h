// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LSA_CasseBrique.generated.h"

/**
 * 
 */
UCLASS()
class CASSEBRIQUE_RPMC_API ALSA_CasseBrique : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	ACameraActor* MainCamera;
};
