// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChoppingMachine.h"
#include "Order.generated.h"

/**
 * 
 */
UCLASS()
class CARPENTERGAME_API UOrder : public UObject
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Order")
    FString ItemName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Order")
    FLinearColor ItemColor;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Order")
    EItemType ItemType;
};
