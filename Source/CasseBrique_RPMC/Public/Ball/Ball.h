// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	//Value used only to test speed from editor
	UPROPERTY(EditInstanceOnly, Category="Ball properties")
	float ActualSpeed;
	
	UFUNCTION(BlueprintSetter)
	void SetSpeed(float s);

	UFUNCTION(BlueprintGetter)
	float GetSpeed() const;
	
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* SpeedEffect;

	UFUNCTION(BlueprintCallable)
	void ReplaceBall();
	
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ScaleEffect;
	
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ClearEffect;
	
	UPROPERTY(EditAnywhere)
	FLinearColor InnerColor;

	UPROPERTY(EditAnywhere)
	FLinearColor OuterColor;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	UFUNCTION()
	void AddColor(FLinearColor InnerColorToAdd, FLinearColor OuterColorToAdd);

	UFUNCTION()
	void RemoveColor(FLinearColor InnerColorToRemove, FLinearColor OuterColorToRemove);

	void SpeedNiagaraEffect() const;
	void ScaleNiagaraEffect() const;
	void ClearNiagaraEffect() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	UPROPERTY(BlueprintGetter=GetSpeed, BlueprintSetter=SetSpeed)

	float Speed;
	FVector StartPosition;
	
	float ColorMixer;

	FLinearColor ActualInnerColor;
	FLinearColor ActualOuterColor;

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterial;


	

	
};
