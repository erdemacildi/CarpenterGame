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

    // Üretilecek küre mesh bileþenini yükleme
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh = SphereMeshAsset.Object;
    }
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

void AChoppingMachine::ProduceItem(FString ItemName)
{
    if (SphereMesh)
    {
        FActorSpawnParameters SpawnParams;
        AActor* SpawnedSphere = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), GetActorLocation() + FVector(100, 0, 200), FRotator::ZeroRotator, SpawnParams);
        UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(SpawnedSphere);
        MeshComp->SetStaticMesh(SphereMesh);
        MeshComp->RegisterComponent();
        MeshComp->SetWorldLocation(SpawnedSphere->GetActorLocation());
        SpawnedSphere->AddInstanceComponent(MeshComp);
        UE_LOG(LogTemp, Warning, TEXT("Produced Item: %s"), *ItemName);
    }
}

