// Fill out your copyright notice in the Description page of Project Settings.


#include "Game.h"
#include "Grid.h"
#include "Core/Snake.h"
#include "Core/Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All);

using namespace SnakeGame;

Game::Game(const Settings& settings): c_settings(settings)
{
	m_grid = MakeShared<Grid>(settings.GridSize);
	checkf(m_grid->dim().width / 2 >= settings.snake.defaultSize, TEXT("Snake initial length [%i] doesn't fit grid width [%i]"),
		settings.snake.defaultSize, m_grid->dim().width);
	m_snake = MakeShared<Snake>(settings.snake);
	m_food = MakeShared<Food>();
	updateGrid();
	generateFood();
}

void SnakeGame::Game::update(float deltaSeconds, const Input& input)
{
	if (m_gameOver || !updateTime(deltaSeconds)) return;

	move(input);

	if (died())
	{
		m_gameOver = true;
		UE_LOG(LogGame, Display, TEXT("___________________ GAME OVER ___________________"));
		UE_LOG(LogGame, Display, TEXT("___________________ SCORE: %i ___________________"), m_score);
		return;
	}

	if (foodTaken())
	{
		++m_score;
		m_snake->increase();
		generateFood();
	}
}

void Game::move(const Input& input)
{
	m_snake->move(input);
	updateGrid();
}

void SnakeGame::Game::generateFood()
{
	Position foodPosition;
	if (m_grid->randomEmptyPosition(foodPosition))
	{
		m_food->setPosition(foodPosition);
		m_grid->update(m_food->position(), CellType::Food);
	}

	else
	{
		m_gameOver = true;
		UE_LOG(LogGame, Display, TEXT("___________________ GAME COMPLETED ___________________"));
		UE_LOG(LogGame, Display, TEXT("___________________ SCORE: %i ___________________"), m_score);
	}

}

bool Game::foodTaken() const
{
	return m_grid->hitTest(m_snake->head(), CellType::Food);
}

void Game::updateGrid()
{
	m_grid->update(m_snake->body(), CellType::Snake);
	m_grid->printDebug();
}

bool Game::updateTime(float deltaSeconds)
{

	m_moveSeconds += deltaSeconds;
	if(m_moveSeconds < c_settings.gameSpeed) return false;
	m_moveSeconds = 0.0f;
	return true;
}

bool SnakeGame::Game::died() const
{
	return m_grid->hitTest(m_snake->head(), CellType::Wall) || //
		m_grid->hitTest(m_snake->head(), CellType::Snake);
}

