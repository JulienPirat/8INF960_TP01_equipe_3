// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"

#include "Ball/Ball.h"
#include "Components/SphereComponent.h"


// Sets default values
AItem::AItem()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	SphereCollision->SetEnableGravity(false);
	RootComponent = SphereCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetupAttachment(SphereCollision);

	NewValue = 0.0f;
	EffectTime = 15.0f;
	InnerColor = FLinearColor(1.0f,1.0f,1.0f,1.0f);
	OuterColor = FLinearColor(1.0f,1.0f,1.0f,1.0f);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	this->SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlap);
	
}

void AItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(const auto NewBall = Cast<ABall>(OtherActor))
	{
		Ball = NewBall;
		this->SphereCollision->DestroyComponent();
		this->StaticMesh->GetChildComponent(0)->DestroyComponent();
		this->StaticMesh->DestroyComponent();
		StartEffect();
	}
}

void AItem::StartEffect()
{
	SetOldValue();
	DoEffect(NewValue);
	Ball->AddColor(InnerColor,OuterColor);
	StartNiagaraEffect();
	StartEffectTimer();
}

void AItem::ClearTimer()
{
	GWorld->GetTimerManager().ClearTimer(EffectTimerHandle);
	EndEffect();
}

void AItem::SetOldValue()
{
}

void AItem::DoEffect(const float Value)
{
}

void AItem::StartNiagaraEffect()
{
}

void AItem::EndNiagaraEffect()
{
}



void AItem::EndEffect()
{
	DoEffect(OldValue);
	Ball->RemoveColor(InnerColor,OuterColor);
	EndNiagaraEffect();
	Destroy();
	
}

void AItem::StartEffectTimer()
{
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("EndEffect"));
	GetWorld()->GetTimerManager().SetTimer(EffectTimerHandle, TimerDel,EffectTime,false);
}
