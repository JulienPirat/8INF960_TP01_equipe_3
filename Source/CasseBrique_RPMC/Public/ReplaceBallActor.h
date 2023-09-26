// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplaceBallActor.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API AReplaceBallActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AReplaceBallActor();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxCollision;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	virtual void OnBeginOverlap(AActor* MyActor, AActor* OtherActor);
};
