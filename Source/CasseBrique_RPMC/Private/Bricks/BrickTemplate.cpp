// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/BrickTemplate.h"

#include "Ball/Ball.h"
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
	if (auto Ball = Cast<ABall>(OtherActor)) {
		
		FVector BallVelocity = Ball->StaticMesh->GetPhysicsLinearVelocity();
		BallVelocity.Y *= -1;
		Ball->StaticMesh->SetPhysicsLinearVelocity(BallVelocity);
		if (HitSound) {

			UGameplayStatics::PlaySound2D( GetWorld(), HitSound);
		}
	}
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

void ABrickTemplate::getDamage(int damage, ABall* Ball)
{
	nbLife -= damage;
	//Particule Ball
	if(this->nbLife <= 0)
	{
		//Ball->addScore(1);
		if (DestructionSound) {

			UGameplayStatics::PlaySound2D( GetWorld(), DestructionSound);
		}
		BeforeDestroy();
	}
}


