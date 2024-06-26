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

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Budget")
    int32 Budget;

    UFUNCTION(BlueprintCallable, Category = "Game Budget")
    void IncreaseBudget(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Game Budget")
    void DecreaseBudget(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Orders")
    void CreateOrder();

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Points);
    
    UPROPERTY()
    TArray<UOrder*> CurrentOrders;

private:
    
    FTimerHandle OrderTimerHandle;

    UPROPERTY()
    UScoreManager* ScoreManager;
};
