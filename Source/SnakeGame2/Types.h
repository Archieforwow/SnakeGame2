// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace Snake
{

	struct Dim
	{
		uint32 width;
		uint32 height;
	};

	enum class CellType
	{
		Empty = 0,
		Wall,
		//Food
		//Snake
	};

	struct Settings
	{
		Dim gridSize;
	};
}
