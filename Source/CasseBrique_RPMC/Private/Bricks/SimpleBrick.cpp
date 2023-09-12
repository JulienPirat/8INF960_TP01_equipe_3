// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/SimpleBrick.h"


// Sets default values
ASimpleBrick::ASimpleBrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASimpleBrick::BeginPlay()
{
	Super::BeginPlay();
	
}

