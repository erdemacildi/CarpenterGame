// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChoppingMachine.h"
#include "PaintingStation.h"
#include "Order.h"
#include "CarpenterGameGameModeBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Kamera bileþeni oluþturma ve yapýlandýrma
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(RootComponent);
    FollowCamera->bUsePawnControlRotation = true;

    // Hareket hýzlarý
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Taþýma deðiþkenlerini baþlatma
    CarriedItem = nullptr;
    bIsCarryingItem = false;
    bHasPaint = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Taþýnan objeyi oyuncunun önünde tutma
    if (bIsCarryingItem && CarriedItem)
    {
        FVector NewLocation = FollowCamera->GetComponentLocation() + FollowCamera->GetForwardVector() * 200.0f;
        CarriedItem->SetActorLocation(NewLocation);
    }

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
    PlayerInputComponent->BindAction("ChangeProductionType", IE_Pressed, this, &APlayerCharacter::ChangeProductionType);
    PlayerInputComponent->BindAction("PaintInteract", IE_Pressed, this, &APlayerCharacter::PaintInteract);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::Interact()
{
    if (bIsCarryingItem && CarriedItem)
    {
        // Objeyi býrakma iþlemi
        UStaticMeshComponent* MeshComponent = CarriedItem->FindComponentByClass<UStaticMeshComponent>();
        if (MeshComponent)
        {
            MeshComponent->SetSimulatePhysics(true);
            MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        }
        CarriedItem = nullptr;
        bIsCarryingItem = false;
        return;
    }

    FHitResult HitResult;
    FVector Start = FollowCamera->GetComponentLocation();
    FVector ForwardVector = FollowCamera->GetForwardVector();
    FVector End = ((ForwardVector * 200.f) + Start);
    FCollisionQueryParams CollisionParams;

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {
        AActor* InteractedActor = HitResult.GetActor();
        if (InteractedActor)
        {
            // ChoppingMachine interaksiyonu
            AChoppingMachine* ChoppingMachine = Cast<AChoppingMachine>(InteractedActor);
            if (ChoppingMachine)
            {
                ChoppingMachine->ProduceItem();
                return;
            }

            // PaintingStation interaksiyonu
            APaintingStation* PaintingStation = Cast<APaintingStation>(InteractedActor);
            if (PaintingStation && CarriedItem)
            {
                PaintingStation->ChangeItemColor(CarriedItem);
                return;
            }

            // Üretilen objeyi taþýma iþlemi
            UStaticMeshComponent* MeshComponent = InteractedActor->FindComponentByClass<UStaticMeshComponent>();
            if (MeshComponent)
            {
                // Objeyi taþýma iþlemi
                MeshComponent->SetSimulatePhysics(false);
                CarriedItem = InteractedActor;
                bIsCarryingItem = true;
            }
            UE_LOG(LogTemp, Warning, TEXT("Interacted with: %s"), *InteractedActor->GetName());
        }
    }
}

void APlayerCharacter::PaintInteract()
{
    FHitResult HitResult;
    FVector Start = FollowCamera->GetComponentLocation();
    FVector ForwardVector = FollowCamera->GetForwardVector();
    FVector End = ((ForwardVector * 200.f) + Start);
    FCollisionQueryParams CollisionParams;

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {
        AActor* InteractedActor = HitResult.GetActor();
        if (InteractedActor)
        {
            if (!bHasPaint)
            {
                // PaintingStation interaksiyonu
                APaintingStation* PaintingStation = Cast<APaintingStation>(InteractedActor);
                if (PaintingStation)
                {
                    bHasPaint = true;
                    UE_LOG(LogTemp, Warning, TEXT("Paint Acquired"));
                    return;
                }
            }
            else
            {
                // Üretilen objeyi boyama iþlemi
                UStaticMeshComponent* MeshComponent = InteractedActor->FindComponentByClass<UStaticMeshComponent>();
                if (MeshComponent)
                {
                    MeshComponent->SetVectorParameterValueOnMaterials("BaseColor", FVector(1.0f, 1.0f, 1.0f));
                    bHasPaint = false;
                    UE_LOG(LogTemp, Warning, TEXT("Object Painted"));
                    return;
                }
            }
        }
    }
}


void APlayerCharacter::ChangeProductionType()
{
    FHitResult HitResult;
    FVector Start = FollowCamera->GetComponentLocation();
    FVector ForwardVector = FollowCamera->GetForwardVector();
    FVector End = ((ForwardVector * 200.f) + Start);
    FCollisionQueryParams CollisionParams;

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {
        AChoppingMachine* ChoppingMachine = Cast<AChoppingMachine>(HitResult.GetActor());
        if (ChoppingMachine)
        {
            if (ChoppingMachine->ItemType == EItemType::Sphere)
            {
                ChoppingMachine->ItemType = EItemType::Cone;
                UE_LOG(LogTemp, Warning, TEXT("Production Type Changed to Cone"));
            }
            else
            {
                ChoppingMachine->ItemType = EItemType::Sphere;
                UE_LOG(LogTemp, Warning, TEXT("Production Type Changed to Sphere"));
            }
        }
    }
}


void APlayerCharacter::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void APlayerCharacter::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void APlayerCharacter::TurnAtRate(float Rate)
{
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::CompleteOrder(UOrder* Order)
{
    if (Order)
    {
        // Sipariþi kontrol etme ve tamamlama iþlemleri
        if (CarriedItem && CarriedItem->GetName().Contains(Order->ItemName))
        {
            // Sipariþ tamamlandý
            UE_LOG(LogTemp, Warning, TEXT("Order Completed: %s"), *Order->ItemName);

            // Oyuncunun taþýdýðý objeyi serbest býrak
            CarriedItem = nullptr;
            bIsCarryingItem = false;

            // Sipariþi CurrentOrders listesinden çýkar
            CurrentOrders.Remove(Order);

            // Skor ekle
            ACarpenterGameGameModeBase* GameMode = Cast<ACarpenterGameGameModeBase>(GetWorld()->GetAuthGameMode());
            if (GameMode)
            {
                GameMode->AddScore(10);
            }
        }
    }
}