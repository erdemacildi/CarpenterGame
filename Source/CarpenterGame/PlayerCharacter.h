// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Order.h"
#include "ChoppingMachine.h"
#include "CarpenterGameGameModeBase.h"
#include "PaintingStation.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CARPENTERGAME_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    APlayerCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void Interact();

    UFUNCTION()
    void PaintInteract();

    UFUNCTION()
    void ChangeProductionType();

    UFUNCTION()
    void ChangeColor();

    void MoveForward(float Value);
    void MoveRight(float Value);
    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);

    UFUNCTION(BlueprintCallable, Category = "Orders")
    void CompleteOrder(UOrder* Order);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Orders")
    TArray<UOrder*> CurrentOrders;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Carrying")
    AActor* CarriedItem;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Carrying")
    bool bIsCarryingItem;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Painting")
    bool bHasPaint;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Painting")
    FLinearColor PaintColor;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    float BaseTurnRate;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    float BaseLookUpRate;
};
