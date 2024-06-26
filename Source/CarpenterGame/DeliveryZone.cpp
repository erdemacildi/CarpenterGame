// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryZone.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Order.h"

// Sets default values
ADeliveryZone::ADeliveryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADeliveryZone::OnOverlapBegin);


}

// Called when the game starts or when spawned
void ADeliveryZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeliveryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeliveryZone::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
    if (PlayerCharacter && PlayerCharacter->bIsCarryingItem)
    {
        for (UOrder* Order : PlayerCharacter->CurrentOrders)
        {
            if (PlayerCharacter->CarriedItem && PlayerCharacter->CarriedItem->GetName().Contains(Order->ItemName))
            {
                PlayerCharacter->CompleteOrder(Order);
                PlayerCharacter->CurrentOrders.Remove(Order);
                break;
            }
        }
    }
}

