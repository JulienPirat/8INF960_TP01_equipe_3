// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/SimpleBrick.h"

#include "Systems/AUCBGameInstance.h"
#include "Systems/AUCBGameStateBase.h"


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
	this->OnActorEndOverlap.AddDynamic(this,&ASimpleBrick::OnEndOverlap);
}

void ASimpleBrick::OnEndOverlap(AActor* MyActor, AActor* OtherActor)
{
	Super::OnEndOverlap(MyActor, OtherActor);
	
	if (auto Ball = Cast<ABall>(OtherActor)) {
		Super::getDamage(1, Ball);
	}
	
}

void ASimpleBrick::BeforeDestroy()
{
	Super::BeforeDestroy();
	//TODO Appeler Le Add Score
	auto _gameInstance = GetGameInstance();
	if (auto GameInstance = Cast<UAUCBGameInstance>(_gameInstance))
	{
		GameInstance->AddScoreSimpleBrick();
	}
}

