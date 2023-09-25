// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bricks/BrickTemplate.h"
#include "GameFramework/Actor.h"
#include "FileMap.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API AFileMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFileMap();

	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<ABrickTemplate> Brick;

	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AActor> SpeedItem; 

	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AActor> ScaleItem;
	
	UPROPERTY(EditAnywhere)
	float dimensionY = 150;

	UPROPERTY(EditAnywhere)
	float dimensionX = 300;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	static FString ReadTextFile(FString path);
};
