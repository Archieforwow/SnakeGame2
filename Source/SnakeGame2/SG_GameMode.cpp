// Fill out your copyright notice in the Description page of Project Settings.


#include "SG_GameMode.h"
#include "Types.h"
#include "World\SG_Grid.h"
#include "SG_Pawn.h"
#include "Grid.h"

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	const Snake::Settings GS{ GridSize.X, GridSize.Y };
	Game = MakeUnique<Snake::Game>(GS);
	check(Game.IsValid());

	const FTransform GridOrigin = FTransform::Identity;
	check(GetWorld());
	GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
	check(GridVisual);
	GridVisual->SetModel(Game->grid(), CellSize);
	GridVisual->FinishSpawning(GridOrigin);

	auto* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	auto* Pawn = Cast<ASG_Pawn>(PC->GetPawn());
	check(Pawn);
	check(Game->grid().IsValid());
	Pawn->UpdateLocation(Game->grid()->dim(), CellSize, GridOrigin);
}
