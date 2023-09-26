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

	ItemToSpawn = nullptr;
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
		//BallVelocity.Y *= -1;
		//Ball->StaticMesh->SetPhysicsLinearVelocity(BallVelocity);
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
	if(ItemToSpawn)
	{
		GetWorld()->SpawnActor<AItem>(ItemToSpawn, GetActorLocation(),GetActorRotation());
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

		//float TimerDelay = 0.1;
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("BeforeDestroy"));
		GetWorldTimerManager().SetTimer(TimerHandle,TimerDel, 0.01 , false);
		
	}
}

void ABrickTemplate::SetSpawnItem(UClass* Item)
{
	ItemToSpawn = Item;
}

