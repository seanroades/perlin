// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMap.h"
#include "ProceduralMeshComponent.h"
#include "Math/UnrealMathUtility.h"

AProceduralMap::AProceduralMap()
{
	PrimaryActorTick.bCanEverTick = false;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
	ProceduralMesh->SetupAttachment(GetRootComponent());

}

void AProceduralMap::BeginPlay()
{
	Super::BeginPlay();

	CreateVertices();
	CreateTriangles();

	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);

}

void AProceduralMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralMap::CreateVertices()
{
	for (int X = 0; X <= XSize; ++X)
	{
		for (int Y = 0; Y <= YSize; ++Y)
		{
			 float Z = GeneratePerlinNoise(X, Y);
			//float Z = FMath::PerlinNoise2D(FVector2D(X * Frequency + 0.1, Y * Frequency + 0.1)) * ZMultiplier;
			UE_LOG(LogTemp, Warning, TEXT("Z: %f"), Z)
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

float AProceduralMap::GeneratePerlinNoise(int X, int Y)
{
	int octaveCount = 1;
	float lacunarity = 100.0;
	float persistence = 0.5;
	float amplitude = 1000.0;

	for (int i = 0; i < octaveCount; i++)
	{
		float noiseValue = 0.0;

		// Change frequency and amplitude for each octave according to lacunarity and persistence
		//float frequency = pow(lacunarity, i);
		//float amplitude = pow(persistence, i);*/

		noiseValue += FMath::PerlinNoise2D(FVector2D(X * Frequency + 0.1, Y * Frequency + 0.1)) * amplitude;
		UE_LOG(LogTemp, Warning, TEXT("Noise Value: %f"), noiseValue)
		return noiseValue;
	}

	return 0.0f;
}

void AProceduralMap::CreateTriangles()
{
	int Vertex = 0;

	for (int X = 0; X < XSize; ++X)
	{
		for (int Y = 0; Y < YSize; ++Y)
		{
			Triangles.Add(Vertex);//Bottom left corner
			Triangles.Add(Vertex + 1);//Bottom right corner
			Triangles.Add(Vertex + YSize + 1);//Top left corner
			Triangles.Add(Vertex + 1);//Bottom right corner
			Triangles.Add(Vertex + YSize + 2);//Top right corner
			Triangles.Add(Vertex + YSize + 1);//Top left corner

			++Vertex;
		}
		++Vertex;
	}
}