// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UObject/Object.h"
#include "AUCBGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CASSEBRIQUE_RPMC_API AUCBGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
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
	void DecreaseTime(); //Retire 1 seconde
	UFUNCTION(BlueprintCallable)
	void AddTime(int timeToAdd); //Ajoute le temps donné a la variable timebank
	UFUNCTION(BlueprintCallable)
	void AddTimeSimpleChronometer(); //Ajoute le temps correspondant a un petit chronomètre
};


