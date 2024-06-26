// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChoppingMachine.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Sphere UMETA(DisplayName = "Sphere"),
	Cone UMETA(DisplayName = "Cone")
};

UCLASS()
class CARPENTERGAME_API AChoppingMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChoppingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Production")
	void ProduceItem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Production")
	EItemType ItemType;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere, Category = "Production")
	UStaticMesh* SphereMesh;

	UPROPERTY(EditAnywhere, Category = "Production")
	UStaticMesh* ConeMesh;

	void SpawnProduct(TSubclassOf<AActor> ProductClass);
};
