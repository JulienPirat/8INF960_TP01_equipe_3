// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ScaleItem.h"


// Sets default values
AScaleItem::AScaleItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AScaleItem::BeginPlay()
{
	Super::BeginPlay();
	
}


void AScaleItem::EndNiagaraEffect()
{
	Super::EndNiagaraEffect();
	Ball->ClearNiagaraEffect();
}

void AScaleItem::StartNiagaraEffect()
{
	Super::StartNiagaraEffect();
	Ball->ScaleNiagaraEffect();
}

void AScaleItem::DoEffect(const float Value)
{
	Super::DoEffect(Value);
	Ball->SetActorScale3D(FVector(Value,Value,Value));
	
}

void AScaleItem::SetOldValue()
{
	Super::SetOldValue();

	OldValue = Ball->GetActorScale().X;
}

