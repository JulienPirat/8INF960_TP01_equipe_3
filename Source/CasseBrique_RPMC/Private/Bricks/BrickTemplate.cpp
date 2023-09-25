// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/BrickTemplate.h"

#include "Ball/Ball.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


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
	this->OnActorEndOverlap.AddDynamic(this,&ABrickTemplate::OnEndOverlap);
}

void ABrickTemplate::OnEndOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Ball = Cast<ABall>(OtherActor)) {
		
		FVector BallVelocity = Ball->StaticMesh->GetPhysicsLinearVelocity();
		if (HitSound) {

			UGameplayStatics::PlaySound2D( GetWorld(), HitSound);
		}
	}
}

void ABrickTemplate::BeforeDestroy()
{
	if (IsValid(DestroyParticle))
	{
		// Spawn Particule
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),DestroyParticle,this->GetActorLocation(),this->GetActorRotation(), FVector(3),true,true);
	}
	
	this->Destroy();
}

void ABrickTemplate::getDamage(int damage, ABall* Ball)
{
	nbLife -= damage;
	//Particule Ball
	if(this->nbLife <= 0)
	{
		if (DestructionSound) {

			UGameplayStatics::PlaySound2D( GetWorld(), DestructionSound);
		}
		BeforeDestroy();
	}
}


