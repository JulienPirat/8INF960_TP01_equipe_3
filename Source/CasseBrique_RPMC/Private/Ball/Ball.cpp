// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Ball.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create BoxCollision for the Ball
	SphereCollision = CreateDefaultSubobject<USphereComponent>("BallCollision");
	SphereCollision->SetEnableGravity(false);
	RootComponent = SphereCollision;

	// Create the mesh for the Ball
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	StaticMesh->SetupAttachment(SphereCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	Speed = 2000;
	ActualSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = 0;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovementComponent->InitialSpeed = Speed;

	StartPosition = this->GetActorLocation();
}

void ABall::SetSpeed(float s)
{
	Speed = s;
	
	ProjectileMovementComponent->Velocity.Normalize();
		
	if(ProjectileMovementComponent->Velocity.IsZero())
	{
		ProjectileMovementComponent->Velocity = FVector(1,0,0);
	}
		
	ProjectileMovementComponent->Velocity *= Speed;
}

float ABall::GetSpeed() const
{
	return Speed;
}

void ABall::ReplaceBall()
{
	this->SetActorLocation(StartPosition);
	ProjectileMovementComponent->InitialSpeed = Speed;
}

void ABall::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ABall, ActualSpeed))
	{
		SetSpeed(ActualSpeed);
	}
}
