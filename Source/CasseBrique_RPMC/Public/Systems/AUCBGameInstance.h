// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AUCBGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, int, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoseByTime);

/**
 * 
 */
UCLASS()
class CASSEBRIQUE_RPMC_API UAUCBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnTimeChanged OnTimeChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnLoseByTime OnLoseByTime;
	
	UPROPERTY(BlueprintReadOnly)
	int score = 0; //Le score du joueur dans la partie
	UPROPERTY(BlueprintReadOnly)
	int timeBank = 60; //Le temps qu'il reste pour jouer (en secondes)

	UFUNCTION(BlueprintCallable)
	void AddScore(int scoreToAdd); //Ajoute un score donné
	UFUNCTION(BlueprintCallable)
	void AddScoreSimpleBrick(); //Ajoute le score correspondant a une brique de base
	UFUNCTION(BlueprintCallable)
	void AddScoreMediumBrick(); //Ajoute le score correspondant a une brique de medium (qui se brise en 2 coups)
	UFUNCTION(BlueprintCallable)
	void AddScoreBigBrick(); //Ajoute le score correspondant a une grosse briaue (qui se brise en 5 coups)

	UFUNCTION(BlueprintCallable)
	void StartTimer();	
	
	UFUNCTION(BlueprintCallable)
	void DecreaseTime(); //Retire 1 seconde
	UFUNCTION(BlueprintCallable)
	void AddTime(int timeToAdd); //Ajoute le temps donné a la variable timebank
	UFUNCTION(BlueprintCallable)
	void AddTimeSimpleChronometer(); //Ajoute le temps correspondant a un petit chronomètre
};
