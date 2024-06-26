// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"

UScoreManager::UScoreManager()
{
    PlayerScore = 0;
}

void UScoreManager::AddScore(int32 Points)
{
    PlayerScore += Points;
}

int32 UScoreManager::GetScore() const
{
    return PlayerScore;
}