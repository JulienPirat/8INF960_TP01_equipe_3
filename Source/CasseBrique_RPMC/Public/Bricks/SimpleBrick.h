// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrickTemplate.h"
#include "GameFramework/Actor.h"
#include "SimpleBrick.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API ASimpleBrick : public ABrickTemplate
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimpleBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlap(AActor* MyActor, AActor* OtherActor) override;
};
