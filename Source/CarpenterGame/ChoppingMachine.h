// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChoppingMachine.generated.h"


// Enum tanýmlamasý
UENUM(BlueprintType)
enum class EProductType : uint8
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

	// Üretim fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "Production")
	void ProduceItem(FString ItemName);


	// Üretilecek obje referansý
	UPROPERTY(EditAnywhere, Category = "Production")
	TSubclassOf<AActor> ItemToProduce;
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	// Üretilecek küre mesh bileþeni
	UPROPERTY(EditAnywhere, Category = "Production")
	UStaticMesh* SphereMesh;
};
