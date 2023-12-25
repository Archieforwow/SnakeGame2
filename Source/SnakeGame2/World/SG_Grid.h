// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "SG_Grid.generated.h"

namespace Snake
{
	class Grid;
}

UCLASS()
class SNAKEGAME2_API ASG_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_Grid();
	virtual void Tick(float DeltaTime) override;

	void SetModel(const TSharedPtr<Snake::Grid>& Grid, int32 CellSize);

protected:
	virtual void BeginPlay() override;

private:

	Snake::Dim GridDim;
	int32 CellSize;
	int32 WorldWidth;
	int32 WorldHeight;

	void DrawGrid();
};
