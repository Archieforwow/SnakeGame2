// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
	class Grid
	{
	public:
		Grid(const Dim& dim);

		Dim dim() const { return c_dim; }
		void printDebug();
		void update(const TPositionPtr* links, CellType cellType);
		bool hitTest(const Position& position, CellType cellType) const;

	private:
		const Dim c_dim;
		TArray<CellType> m_cells;
		TMap < CellType, TArray<int32>> m_indByType = 
		{
			{CellType::Snake, {}},
			{CellType::Wall, {}},
		};

		void initWalls();
	
		FORCEINLINE int32 posToIndex(int32 x, int32 y) const;
		FORCEINLINE int32 posToIndex(const Position& position) const;
		void freeCellsByType(CellType cellType);
	};

}

