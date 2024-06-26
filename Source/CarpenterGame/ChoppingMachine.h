// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChoppingMachine.generated.h"


// Enum tan�mlamas�
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

	/*// �retim fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "Production")
	void ProduceItem(FString ItemName);


	// �retilecek obje referans�
	UPROPERTY(EditAnywhere, Category = "Production")
	TSubclassOf<AActor> ItemToProduce;*/

	// �retim fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "Production")
	void ProduceItem();

	// �retim tipi de�i�keni
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Production")
	EItemType ItemType;

	/*/ Mesh bile�enleri
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ConeMesh;*/

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere, Category = "Production")
	UStaticMesh* SphereMesh;

	UPROPERTY(EditAnywhere, Category = "Production")
	UStaticMesh* ConeMesh;

	/*// �retilecek k�re mesh bile�eni
	UPROPERTY(EditAnywhere, Category = "Production")
	UStaticMesh* SphereMesh;*/

	void SpawnProduct(TSubclassOf<AActor> ProductClass);
};
