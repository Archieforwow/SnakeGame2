// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{

	class Food
	{
	public:
		Food() = default;

		void setPosition(const Position& position);
		Position position() const;

	private:
		Position m_position{ Position::Zero };
	};
}
