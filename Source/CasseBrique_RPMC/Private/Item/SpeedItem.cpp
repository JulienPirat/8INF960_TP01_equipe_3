// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SpeedItem.h"


// Sets default values
ASpeedItem::ASpeedItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpeedItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpeedItem::EndNiagaraEffect()
{
	Super::EndNiagaraEffect();
	Ball->ClearNiagaraEffect();
}

void ASpeedItem::StartNiagaraEffect()
{
	Super::StartNiagaraEffect();
	Ball->SpeedNiagaraEffect();
}

void ASpeedItem::DoEffect(const float Value)
{
	Super::DoEffect(Value);
	
	Ball->SetSpeed(Value);
	
}

void ASpeedItem::SetOldValue()
{
	Super::SetOldValue();

	OldValue = Ball->GetSpeed();
}




