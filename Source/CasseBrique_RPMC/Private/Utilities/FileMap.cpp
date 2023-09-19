// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/FileMap.h"


// Sets default values
AFileMap::AFileMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
}

// Called when the game starts or when spawned
void AFileMap::BeginPlay()
{
	Super::BeginPlay();

	FString RelativePath = FPaths::ProjectContentDir();
	FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
	FullPath += "CasseBrique_RPMC/Map.txt";
	
	FString ResText = ReadTextFile(FullPath);
	
	TArray<FString> LinesFile;
	ResText.ParseIntoArrayLines(LinesFile);
	FVector SpawnLocation(0.0f, 0.0f, 50.0f);
	FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
	
	for (int32 i = 0; i < LinesFile.Num(); i++)
	{
		SpawnLocation.Y = i * dimensionY;
		SpawnLocation.X = 0.0f;
		
		for (int32 j = 0; j < LinesFile[i].Len(); j++)
		{
			wchar_t WallLettre = *"X";
			wchar_t DestructibleWallLettre = *"O";
			SpawnLocation.X = j * dimensionY;
			
			if(LinesFile[i][j] == WallLettre)
			{
				UE_LOG(LogTemp, Display, TEXT("X"));
				SpawnLocation.X = j * dimensionX;
				GetWorld()->SpawnActor<ABrickTemplate>(Brick, SpawnLocation, SpawnRotation);
			}
			if(LinesFile[i][j] == DestructibleWallLettre)
			{
				UE_LOG(LogTemp, Display, TEXT("O"));
				//GetWorld()->SpawnActor<Stati>(DestructibleWall, SpawnLocation, SpawnRotation);
			}
		}
	}
}

FString AFileMap::ReadTextFile(FString path)
{
	bool bOutSuccess = false;
	if(!FPlatformFileManager::Get().GetPlatformFile().FileExists(*path))
	{
		bOutSuccess = false;
		return "false";
	}

	FString RetString = "";

	if(!FFileHelper::LoadFileToString(RetString, *path))
	{
		bOutSuccess = false;
		return "false";
	}

	bOutSuccess = true;
	return RetString;
}


