// Copyright Epic Games, Inc. All Rights Reserved.


#include "CarpenterGameGameModeBase.h"
#include "PlayerCharacter.h"
#include "Order.h"
#include "ScoreManager.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
//#include "Blueprint/UserWidget.h"

ACarpenterGameGameModeBase::ACarpenterGameGameModeBase()
{

    Budget = 1000;

    DefaultPawnClass = APlayerCharacter::StaticClass();

    PrimaryActorTick.bCanEverTick = true;
    ScoreManager = CreateDefaultSubobject<UScoreManager>(TEXT("ScoreManager"));

}

void ACarpenterGameGameModeBase::IncreaseBudget(int32 Amount)
{
    Budget += Amount;
}

void ACarpenterGameGameModeBase::DecreaseBudget(int32 Amount)
{
    Budget -= Amount;
}

void ACarpenterGameGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (ScoreManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("Game Started! Initial Score: %d, Initial Budget: %d"), ScoreManager->GetScore(), Budget);
    }

    GetWorldTimerManager().SetTimer(OrderTimerHandle, this, &ACarpenterGameGameModeBase::CreateOrder, 20.0f, true);
}

void ACarpenterGameGameModeBase::CreateOrder()
{
    UOrder* NewOrder = NewObject<UOrder>();

    FString Items[] = { TEXT("Sphere"), TEXT("Cone") };
    FLinearColor Colors[] = {  FLinearColor::Yellow, FLinearColor::Blue };

    int32 RandomItemIndex = FMath::RandRange(0, 1);
    int32 RandomColorIndex = FMath::RandRange(0, 1);

    NewOrder->ItemName = Items[RandomItemIndex];
    NewOrder->ItemColor = Colors[RandomColorIndex];
    NewOrder->ItemType = (RandomItemIndex == 0) ? EItemType::Sphere : EItemType::Cone;

    CurrentOrders.Add(NewOrder);

    if (NewOrder->ItemColor == FLinearColor::Yellow) {
        UE_LOG(LogTemp, Warning, TEXT("New Order Created: %s, Color: Yellow"), *NewOrder->ItemName);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("New Order Created: %s, Color: Blue"), *NewOrder->ItemName);
    }
}

void ACarpenterGameGameModeBase::AddScore(int32 Points)
{
    if (ScoreManager)
    {
        ScoreManager->AddScore(Points);
        UE_LOG(LogTemp, Warning, TEXT("Score Added: %d, Total Score: %d"), Points, ScoreManager->GetScore());
    }
}