// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/Pawn.h"
#include "CBPlayer.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API ACBPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACBPlayer();

	/**
	 * Box de collision du Paddle
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

	/**
	 * StaticMesh qui représente la paddle
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	/**
	 * Composant qui permet le mouvement du paddle
	 */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPawnMovementComponent> MovementComponent;
	
	/**
	 * Variable représentant la vitesse de déplacement du paddle
	 */
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 100.f;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> MappingContext;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	/**
	 * Fonction qui gère l'overlap
	 * @param MyActor Self
	 * @param OtherActor Overlaped Actor
	 */
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);
};
