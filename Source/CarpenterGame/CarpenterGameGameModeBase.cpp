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

    // Sipariþ oluþturmayý belirli aralýklarla tetiklemek için bir timer ayarlayýn
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

    // Baþlangýç skorunu ve bütçesini loga yazdýrýn
    if (ScoreManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("Game Started! Initial Score: %d, Initial Budget: %d"), ScoreManager->GetScore(), Budget);
    }

    // Sipariþ oluþturmayý belirli aralýklarla tetiklemek için bir timer ayarlayýn
    GetWorldTimerManager().SetTimer(OrderTimerHandle, this, &ACarpenterGameGameModeBase::CreateOrder, 10.0f, true);
}


/*void ACarpenterGameGameModeBase::CreateOrder()
{
    UOrder* NewOrder = NewObject<UOrder>();

    // Rastgele bir obje ve renk belirliyoruz
    FString Items[] = { TEXT("Chair"), TEXT("Table"), TEXT("Shelf") };
    FLinearColor Colors[] = { FLinearColor::Red, FLinearColor::Green, FLinearColor::Blue };

    int32 RandomItemIndex = FMath::RandRange(0, 2);
    int32 RandomColorIndex = FMath::RandRange(0, 2);

    NewOrder->ItemName = Items[RandomItemIndex];
    NewOrder->ItemColor = Colors[RandomColorIndex];

    // Sipariþi yönetmek için diðer iþlemler
    UE_LOG(LogTemp, Warning, TEXT("New Order Created: %s, Color: %s"), *NewOrder->ItemName, *NewOrder->ItemColor.ToString());
}*/

void ACarpenterGameGameModeBase::CreateOrder()
{
    UOrder* NewOrder = NewObject<UOrder>();

    // Rastgele bir obje ve renk belirliyoruz
    FString Items[] = { TEXT("Chair"), TEXT("Table"), TEXT("Shelf") };
    FLinearColor Colors[] = { FLinearColor::Red, FLinearColor::Green, FLinearColor::Blue };

    int32 RandomItemIndex = FMath::RandRange(0, 2);
    int32 RandomColorIndex = FMath::RandRange(0, 2);

    NewOrder->ItemName = Items[RandomItemIndex];
    NewOrder->ItemColor = Colors[RandomColorIndex];

    CurrentOrders.Add(NewOrder);

    // Sipariþi yönetmek için diðer iþlemler
    UE_LOG(LogTemp, Warning, TEXT("New Order Created: %s, Color: %s"), *NewOrder->ItemName, *NewOrder->ItemColor.ToString());
}

void ACarpenterGameGameModeBase::AddScore(int32 Points)
{
    /*if (ScoreManager)
    {
        ScoreManager->AddScore(Points);
        UE_LOG(LogTemp, Warning, TEXT("Score Added: %d, Total Score: %d"), Points, ScoreManager->GetScore());
    }*/
}