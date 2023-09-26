﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ScaleItem.generated.h"

UCLASS()
class CASSEBRIQUE_RPMC_API AScaleItem : public AItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AScaleItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndNiagaraEffect() override;
	
	virtual void StartNiagaraEffect() override;
	
	virtual void DoEffect(const float Value) override;

	virtual void SetOldValue() override;
};
