// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball/Ball.h"
#include "GameFramework/Actor.h"
#include "Item/Item.h"
#include "BrickTemplate.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API ABrickTemplate : public AActor
{
	

private:
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
	
	UPROPERTY(EditAnywhere, Category="Niagara")
	class UNiagaraSystem* DestroyParticle;

	UPROPERTY(EditAnywhere, Category="Item")
	class UClass* ItemToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:
	
	UFUNCTION()
	virtual void OnEndOverlap(AActor* MyActor, AActor* OtherActor);
	
	UFUNCTION()
	virtual void BeforeDestroy();

	UFUNCTION()
	void getDamage(int damage, ABall* Ball);

	UFUNCTION()
	void SetSpawnItem(UClass* Item);
};
