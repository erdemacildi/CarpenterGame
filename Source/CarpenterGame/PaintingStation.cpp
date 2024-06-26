// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingStation.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
APaintingStation::APaintingStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Creating Cylinder Mesh
    CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMesh"));
    RootComponent = CylinderMesh;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
    if (CylinderMeshAsset.Succeeded())
    {
        CylinderMesh->SetStaticMesh(CylinderMeshAsset.Object);
        CylinderMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void APaintingStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaintingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APaintingStation::ChangeItemColor(AActor* Item)
{
    if (Item)
    {
        UStaticMeshComponent* MeshComp = Item->FindComponentByClass<UStaticMeshComponent>();
        if (MeshComp)
        {
            UMaterialInstanceDynamic* DynamicMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
            if (DynamicMaterial)
            {
                DynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor::White);
                UE_LOG(LogTemp, Warning, TEXT("Changed Color of Item: %s to White"), *Item->GetName());
            }
        }
    }
}