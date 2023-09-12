// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/AUCBGameStateBase.h"

void AUCBGameStateBase::AddScore(int scoreToAdd)
{
	score += scoreToAdd;
}

void AUCBGameStateBase::AddScoreSimpleBrick()
{
	score += 10;
}

void AUCBGameStateBase::AddScoreMediumBrick()
{
	score += 20;
}

void AUCBGameStateBase::AddScoreBigBrick()
{
	score += 50;
}

void AUCBGameStateBase::DecreaseTime()
{
	timeBank -= 1;
}

void AUCBGameStateBase::AddTime(int timeToAdd)
{
	timeBank += timeToAdd;
}

void AUCBGameStateBase::AddTimeSimpleChronometer()
{
	timeBank += 20;
}
