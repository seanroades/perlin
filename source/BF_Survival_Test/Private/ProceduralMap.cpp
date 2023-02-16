#include "ProceduralMap.h"
#include "Math/UnrealMathUtility.h"

AProceduralMap::AProceduralMap()
{
    PrimaryActorTick.bCanEverTick = false;

    ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
    ProceduralMeshComponent->SetupAttachment(GetRootComponent());
}

void AProceduralMap::GenerateMesh(unsigned int XLength, unsigned int YLength)
{
    // Clear previous mesh in case we are regenerating
    ProceduralMeshComponent->ClearAllMeshSections();

    // Generate noise map for each layer
}

//
double AProceduralMap::CombinePerlinLayers(const TArray<FPerlinLayer>& NoiseLayers, double X, double Y)
{
    // Make sure we have at least one layer
    if (NoiseLayers.Num() == 0)
    {
		return 0.0;
	}

    // Get noise value for a combined x, y coordinate
    double noiseValue = 0.0;

    for (int i = 0; i < NoiseLayers.Num(); i++)
    {
		const FPerlinLayer& Layer = NoiseLayers[i];

        // Add noise value for each layer, can also be subtracted, multiplied, etc depending on application
		noiseValue += (double) FMath::PerlinNoise2D(FVector2D(X * Layer.frequency, Y * Layer.frequency)) * Layer.amplitude;
        return noiseValue;
	}
}

double AProceduralMap::GeneratePerlinNoise(FPerlinLayer Layer, double X, double Y) 
{
    for (int i = 0; i < Layer.octaveCount; i++)
    {
        double noiseValue = 0.0;

        // Change frequency and amplitude for each octave according ot lacunarity and persistence
        double frequency = pow(Layer.lacunarity, i);
		double amplitude = pow(Layer.persistence, i);

		noiseValue += (double) FMath::PerlinNoise2D(FVector2D(X * frequency, Y * frequency)) * amplitude;

        return noiseValue;
    }
}

