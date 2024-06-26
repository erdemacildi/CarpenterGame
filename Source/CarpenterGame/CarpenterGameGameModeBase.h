// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Order.h"
#include "ScoreManager.h"
#include "CarpenterGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CARPENTERGAME_API ACarpenterGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ACarpenterGameGameModeBase();

protected:
    virtual void BeginPlay() override;

public:

    // B�t�e de�i�kenini tan�ml�yoruz
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Budget")
    int32 Budget;

    // B�t�eyi art�rma fonksiyonu
    UFUNCTION(BlueprintCallable, Category = "Game Budget")
    void IncreaseBudget(int32 Amount);

    // B�t�eyi azaltma fonksiyonu
    UFUNCTION(BlueprintCallable, Category = "Game Budget")
    void DecreaseBudget(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Orders")
    void CreateOrder();

    // Skor y�netimi fonksiyonu
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Points);

private:
    // Timer handle tan�mlamas�
    FTimerHandle OrderTimerHandle;

    // Mevcut sipari�ler
    UPROPERTY()
    TArray<UOrder*> CurrentOrders;

    // Skor y�neticisi
    UPROPERTY()
    UScoreManager* ScoreManager;

    

};
