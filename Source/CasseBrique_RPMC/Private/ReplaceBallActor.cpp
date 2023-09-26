// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplaceBallActor.h"

#include "Ball/Ball.h"
#include "Components/BoxComponent.h"


// Sets default values
AReplaceBallActor::AReplaceBallActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create BoxCollision for the Brick
	boxCollision = CreateDefaultSubobject<UBoxComponent>("BrickCollision");
	RootComponent = boxCollision;
}

// Called when the game starts or when spawned
void AReplaceBallActor::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this,&AReplaceBallActor::OnBeginOverlap);
}

void AReplaceBallActor::OnBeginOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Ball = Cast<ABall>(OtherActor)) {
		
		Ball->ReplaceBall();
	}
}
