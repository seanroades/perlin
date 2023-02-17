#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralMap.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class BF_SURVIVAL_TEST_API AProceduralMap : public AActor
{
	GENERATED_BODY()

public:
	AProceduralMap();

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int XSize = 0;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int YSize = 0;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float ZMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float Frequency = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float Scale = 100.0f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 0.0f;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UProceduralMeshComponent* ProceduralMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;

	void CreateVertices();
	void CreateTriangles();
	float GeneratePerlinNoise(int X, int Y);
};