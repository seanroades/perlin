#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralMap.generated.h"

class UProceduralMeshComponent;

USTRUCT(BlueprintType)
struct FPerlinLayer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int octaveCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double frequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double persistence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double amplitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        double lacunarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int seed;
};

UCLASS()
class BF_SURVIVAL_TEST_API AProceduralMap : public AActor
{
    GENERATED_BODY()

public:
    AProceduralMap();

    UFUNCTION(BlueprintCallable)
        void GenerateMesh(unsigned int XLength, unsigned int YLength);

    UFUNCTION(BlueprintCallable)
        void AddPerlinLayer(const FPerlinLayer& Layer);
    
    UFUNCTION(BlueprintCallable)
        void GeneratePerlinNoise(FPerlinLayer Layer, double X, double Y);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FPerlinLayer> PerlinNoiseLayers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        unsigned int XLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        unsigned int YLength;

    UProceduralMeshComponent* ProceduralMeshComponent;
};
