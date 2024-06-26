// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoppingMachine.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
AChoppingMachine::AChoppingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Küp mesh bileþenini oluþturma ve yapýlandýrma
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
        CubeMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh = SphereMeshAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
    if (ConeMeshAsset.Succeeded())
    {
        ConeMesh = ConeMeshAsset.Object;
    }

    ItemType = EItemType::Sphere;
}

// Called when the game starts or when spawned
void AChoppingMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChoppingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChoppingMachine::ProduceItem()
{
        if (ItemType == EItemType::Sphere)
    {
        // Sphere üretme
        FActorSpawnParameters SpawnParams;
        AActor* SpawnedSphere = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), GetActorLocation() + FVector(100, 0, 0), FRotator::ZeroRotator, SpawnParams);
        UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(SpawnedSphere);
        MeshComp->SetStaticMesh(SphereMesh);
        MeshComp->RegisterComponent();
        MeshComp->SetWorldLocation(SpawnedSphere->GetActorLocation());
        SpawnedSphere->AddInstanceComponent(MeshComp);
    }
    else if (ItemType == EItemType::Cone)
    {
        FActorSpawnParameters SpawnParams;
        AActor* SpawnedCone = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), GetActorLocation() + FVector(100, 0, 0), FRotator::ZeroRotator, SpawnParams);
        UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(SpawnedCone);
        MeshComp->SetStaticMesh(ConeMesh);
        MeshComp->RegisterComponent();
        MeshComp->SetWorldLocation(SpawnedCone->GetActorLocation());
        SpawnedCone->AddInstanceComponent(MeshComp);
    }
}

void AChoppingMachine::SpawnProduct(TSubclassOf<AActor> ProductClass)
{
    if (ProductClass)
    {
        FActorSpawnParameters SpawnParams;
        GetWorld()->SpawnActor<AActor>(ProductClass, GetActorLocation() + FVector(100, 0, 0), FRotator::ZeroRotator, SpawnParams);
    }
}

