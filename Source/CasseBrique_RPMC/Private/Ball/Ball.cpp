// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Ball.h"
#include "Components/SphereComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create SphereCollision for the Ball
	SphereCollision = CreateDefaultSubobject<USphereComponent>("BallCollision");
	SphereCollision->SetEnableGravity(false);
	RootComponent = SphereCollision;

	// Create the mesh for the Ball
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	StaticMesh->SetupAttachment(SphereCollision);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	//Set parmaters
	Speed = 2000.0f;
	ActualSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = 0.0f;
	ColorMixer = 0.0f;
	InnerColor = FLinearColor(1.0f,1.0f,1.0f,1.0f);
	OuterColor = FLinearColor(1.0f,1.0f,1.0f,1.0f);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	if(StaticMesh->GetMaterial(0))
	{
		DynMaterial = UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(0), this);
	}
	
	ProjectileMovementComponent->InitialSpeed = Speed;
	SetSpeed(0);
	SetSpeed(ProjectileMovementComponent->InitialSpeed);
	StartPosition = this->GetActorLocation();
}

void ABall::SetSpeed(float s)
{
	Speed = s;
	ActualSpeed = s;
	
	ProjectileMovementComponent->Velocity.Normalize();
		
	if(ProjectileMovementComponent->Velocity.IsZero())
	{
		ProjectileMovementComponent->Velocity = FVector(-1,0.5,0);
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
	
	//Reset speed direction
	const float SpeedBuffer = GetSpeed();
	SetSpeed(0.0f);
	
	SetSpeed(SpeedBuffer);
}

void ABall::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ABall, ActualSpeed))
	{
		SetSpeed(ActualSpeed);
	}
}

void ABall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	FVector SurfaceNormal = HitNormal.GetSafeNormal();
	FVector BounceDirection = ProjectileMovementComponent->Velocity.GetSafeNormal().MirrorByVector(SurfaceNormal);
	float BounceSpeed = GetSpeed();

	//Case when the ball is blocked
	while(BounceDirection == FVector::Zero())
		BounceDirection = FVector(FMath::RandRange(0.0f,1.0f),FMath::RandRange(0.0f,1.0f),0);
	ProjectileMovementComponent->Velocity =  BounceDirection * BounceSpeed;
	
	
}

void ABall::AddColor(FLinearColor InnerColorToAdd, FLinearColor OuterColorToAdd)
{
	
	if(StaticMesh->GetMaterial(0))
	{
		ColorMixer ++;
		if(ColorMixer == 1)
		{
			
			ActualInnerColor = InnerColorToAdd;
			ActualOuterColor = OuterColorToAdd;
		}
		else
		{
			ActualInnerColor = FMath::Lerp(ActualInnerColor,InnerColorToAdd,1/ColorMixer);
			ActualOuterColor = FMath::Lerp(ActualOuterColor,OuterColorToAdd,1/ColorMixer);
		}

		DynMaterial->SetVectorParameterValue(FName("Inner Color"),ActualInnerColor);
		DynMaterial->SetVectorParameterValue(FName("Outline Color"),ActualOuterColor);
		StaticMesh->SetMaterial(0, DynMaterial);
	}
}

void ABall::RemoveColor(FLinearColor InnerColorToRemove, FLinearColor OuterColorToRemove)
{

	if(StaticMesh->GetMaterial(0))
	{
		if(ColorMixer == 1)
		{
			ActualInnerColor = InnerColor;
			ActualOuterColor = OuterColor;
		}
		else
		{
			ActualInnerColor = (ActualInnerColor - InnerColorToRemove * 1/ColorMixer)/(1-(1/ColorMixer));
			ActualOuterColor =  (ActualOuterColor - OuterColorToRemove * 1/ColorMixer)/(1-(1/ColorMixer));
		}

		DynMaterial->SetVectorParameterValue(FName("Inner Color"),ActualInnerColor);
		DynMaterial->SetVectorParameterValue(FName("Outline Color"),ActualOuterColor);
		StaticMesh->SetMaterial(0, DynMaterial);
		ColorMixer --;
	}
	
}


void ABall::SpeedNiagaraEffect() const
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(SpeedEffect,SphereCollision,FName("None"),GetActorLocation(),GetActorRotation(),EAttachLocation::KeepWorldPosition,true,true);
}

void ABall::ScaleNiagaraEffect() const
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(ScaleEffect,SphereCollision,FName("None"),GetActorLocation(),GetActorRotation(),EAttachLocation::KeepWorldPosition,true,true);
}


void ABall::ClearNiagaraEffect() const
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(ClearEffect,SphereCollision,FName("None"),GetActorLocation(),GetActorRotation(),EAttachLocation::KeepWorldPosition,true,true);
}
