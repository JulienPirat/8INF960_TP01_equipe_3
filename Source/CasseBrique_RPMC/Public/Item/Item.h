// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball/Ball.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere,Category = "Item effect")
	ABall* Ball;

	UPROPERTY(EditAnywhere, Category = "Item effect")
	float NewValue;
	
	UPROPERTY(EditAnywhere, Category = "Item effect")
	float EffectTime;

	UPROPERTY(EditAnywhere, Category = "Item effect")
	FLinearColor InnerColor;

	UPROPERTY(EditAnywhere, Category = "Item effect")
	FLinearColor OuterColor;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void SetOldValue();
	virtual void DoEffect(const float Value);

	virtual void StartNiagaraEffect();
	virtual void EndNiagaraEffect();

	float OldValue;

private:
	UFUNCTION()
	void EndEffect();
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void StartEffectTimer();
	void StartEffect();
	void ClearTimer();
	
	FTimerHandle EffectTimerHandle;

	
};
