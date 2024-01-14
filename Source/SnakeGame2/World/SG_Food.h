// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Food.h"
#include "SG_Food.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME2_API ASG_Food : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Food();

	void SetModel(const TSharedPtr<SnakeGame::Food>& Food, int32 CellSize, const SnakeGame::Dim& Dims);
	void UpdateColors(const FLinearColor& Color);

protected:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FoodMesh;

public:	
	virtual void Tick(float DeltaTime) override;

private:

	TWeakPtr<SnakeGame::Food> Food;
	int32 CellSize;
	SnakeGame::Dim Dims;

};
