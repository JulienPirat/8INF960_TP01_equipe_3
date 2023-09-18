// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerInput.h"
#include "UObject/Object.h"
#include "AUCBGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CASSEBRIQUE_RPMC_API UAUCBGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> MappingContext;
	
};
