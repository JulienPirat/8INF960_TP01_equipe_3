﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CBPlayer.h"

#include <iostream>
#include <string>

#include "Ball/Ball.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ACBPlayer::ACBPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create BoxCollision for the Paddle
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");

	// Attache la box de collision en tant que Composant principal
	RootComponent = BoxCollision;

	// Create the mesh for the paddle
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle"));
	StaticMesh->SetupAttachment(BoxCollision);

	// Create Movement Component for the paddle
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = BoxCollision;
}

// Called when the game starts or when spawned
void ACBPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ACBPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

