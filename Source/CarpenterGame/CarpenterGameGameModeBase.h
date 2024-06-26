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

    // Bütçe deðiþkenini tanýmlýyoruz
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Budget")
    int32 Budget;

    // Bütçeyi artýrma fonksiyonu
    UFUNCTION(BlueprintCallable, Category = "Game Budget")
    void IncreaseBudget(int32 Amount);

    // Bütçeyi azaltma fonksiyonu
    UFUNCTION(BlueprintCallable, Category = "Game Budget")
    void DecreaseBudget(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Orders")
    void CreateOrder();

    // Skor yönetimi fonksiyonu
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Points);

private:
    // Timer handle tanýmlamasý
    FTimerHandle OrderTimerHandle;

    // Mevcut sipariþler
    UPROPERTY()
    TArray<UOrder*> CurrentOrders;

    // Skor yöneticisi
    UPROPERTY()
    UScoreManager* ScoreManager;

    

};
