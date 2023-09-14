// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	//Value used only to test speed from editor
	UPROPERTY(EditInstanceOnly, Category="Ball properties")
	float ActualSpeed;
	
	UFUNCTION(BlueprintSetter)
	void SetSpeed(float s);

	UFUNCTION(BlueprintGetter)
	float GetSpeed() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	UPROPERTY(BlueprintGetter=GetSpeed, BlueprintSetter=SetSpeed)
	float Speed;
	
};
