// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaintingStation.generated.h"

UCLASS()
class CARPENTERGAME_API APaintingStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintingStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Renk de�i�tirme fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "Painting")
	void ChangeItemColor(AActor* Item);

private:
	// Silindir mesh bile�eni
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CylinderMesh;

	// Mesh bile�eni
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};
