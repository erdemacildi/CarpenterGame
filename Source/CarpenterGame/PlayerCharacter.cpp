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
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(RootComponent);
    FollowCamera->bUsePawnControlRotation = true;

    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    CarriedItem = nullptr;
    bIsCarryingItem = false;
    bHasPaint = false;

    PaintColor = FLinearColor::Yellow;
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
    PlayerInputComponent->BindAction("ChangeColor", IE_Pressed, this, &APlayerCharacter::ChangeColor);

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
            AChoppingMachine* ChoppingMachine = Cast<AChoppingMachine>(InteractedActor);
            if (ChoppingMachine)
            {
                ChoppingMachine->ProduceItem();
                return;
            }

            APaintingStation* PaintingStation = Cast<APaintingStation>(InteractedActor);
            if (PaintingStation && CarriedItem)
            {
                PaintingStation->ChangeItemColor(CarriedItem);
                return;
            }

            UStaticMeshComponent* MeshComponent = InteractedActor->FindComponentByClass<UStaticMeshComponent>();
            if (MeshComponent)
            {
                MeshComponent->SetSimulatePhysics(false);
                MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
                UStaticMeshComponent* MeshComponent = InteractedActor->FindComponentByClass<UStaticMeshComponent>();
                if (MeshComponent)
                {
                    UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
                    if (DynamicMaterial)
                    {
                        DynamicMaterial->SetVectorParameterValue("BaseColor", PaintColor);
                        bHasPaint = false;
                        UE_LOG(LogTemp, Warning, TEXT("Object Painted"));
                    }
                    return;
                }
            }
        }
    }
}

void APlayerCharacter::ChangeColor()
{
    if (PaintColor == FLinearColor::Yellow)
    {
        PaintColor = FLinearColor::Blue;
        UE_LOG(LogTemp, Warning, TEXT("Color Changed to Blue"));
    }
    else
    {
        PaintColor = FLinearColor::Yellow;
        UE_LOG(LogTemp, Warning, TEXT("Color Changed to Yellow"));
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
        if (CarriedItem && CarriedItem->GetName().Contains(Order->ItemName))
        {
            UE_LOG(LogTemp, Warning, TEXT("Order Completed: %s"), *Order->ItemName);

            CarriedItem = nullptr;
            bIsCarryingItem = false;

            CurrentOrders.Remove(Order);

            ACarpenterGameGameModeBase* GameMode = Cast<ACarpenterGameGameModeBase>(GetWorld()->GetAuthGameMode());
            if (GameMode)
            {
                GameMode->AddScore(10);
            }
        }
    }
}