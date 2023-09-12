// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrickTemplate.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API ABrickTemplate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrickTemplate();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, Category = "StatsBrick")
	int nbLife;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundBase* DestructionSound;
	
	UPROPERTY(EditAnywhere, Category="Particles")
	class UParticleSystem* DestroyParticle;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UFUNCTION()
	virtual void OnOverlap(AActor* MyActor, AActor* OtherActor);
	
	UFUNCTION()
	void BeforeDestroy();
};
