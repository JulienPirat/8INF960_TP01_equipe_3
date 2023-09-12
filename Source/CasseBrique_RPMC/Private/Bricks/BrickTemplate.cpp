// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/BrickTemplate.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


// Sets default values
ABrickTemplate::ABrickTemplate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create BoxCollision for the Brick
	boxCollision = CreateDefaultSubobject<UBoxComponent>("BrickCollision");
	RootComponent = boxCollision;

	// Create the mesh for the Brick
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));
	staticMesh->SetupAttachment(boxCollision);
}

// Called when the game starts or when spawned
void ABrickTemplate::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this,&ABrickTemplate::OnOverlap);
}

void ABrickTemplate::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	//TODO Overlap when the ball is implemented
}

void ABrickTemplate::BeforeDestroy()
{
	if (IsValid(DestroyParticle))
	{
		// Transform --> Location, Rotation, Scale
		FTransform ParticleT;
		// Spawn Location
		ParticleT.SetLocation(this->GetActorLocation());
		// World Size Particule
		ParticleT.SetScale3D(FVector(2, 2, 2));
		
		// Spawn Particule
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, ParticleT, true);
	}
	this->Destroy();
}


