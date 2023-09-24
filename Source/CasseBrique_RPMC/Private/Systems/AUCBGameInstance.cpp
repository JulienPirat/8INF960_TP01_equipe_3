// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/AUCBGameInstance.h"


void UAUCBGameInstance::AddScore(int scoreToAdd)
{
	score += scoreToAdd;
	OnScoreChangedDelegate.Broadcast(score);
}

void UAUCBGameInstance::AddScoreSimpleBrick()
{
	score += 10;
	OnScoreChangedDelegate.Broadcast(score);
}

void UAUCBGameInstance::AddScoreMediumBrick()
{
	score += 20;
	OnScoreChangedDelegate.Broadcast(score);
}

void UAUCBGameInstance::AddScoreBigBrick()
{
	score += 50;
	OnScoreChangedDelegate.Broadcast(score);
}

void UAUCBGameInstance::StartTimer()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::DecreaseTime, 1, true);
}

void UAUCBGameInstance::DecreaseTime()
{
	timeBank -= 1;
	OnTimeChangedDelegate.Broadcast(timeBank);

	if (timeBank == 0)
	{
		OnLoseByTime.Broadcast();
	}
}

void UAUCBGameInstance::AddTime(int timeToAdd)
{
	timeBank += timeToAdd;
}

void UAUCBGameInstance::AddTimeSimpleChronometer()
{
	timeBank += 20;
}