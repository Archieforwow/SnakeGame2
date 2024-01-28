// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SG_HUD.h"
#include "UI/SG_GameplayWidget.h"
#include "UI/SG_GameOverWidget.h"
#include "Game.h"

ASG_HUD::ASG_HUD()
{
	PrimaryActorTick.TickInterval = 1.0f;
}

void ASG_HUD::BeginPlay()
{
	Super::BeginPlay();

	GameplayWidget = CreateWidget<USG_GameplayWidget>(GetWorld(), GameplayWidgetClass);
	check(GameplayWidget);
	GameWidgets.Add(EUIGameState::GameInProgress, GameplayWidget);

	GameOverWidget = CreateWidget<USG_GameOverWidget>(GetWorld(), GameOverWidgetClass);
	check(GameOverWidget);
	GameWidgets.Add(EUIGameState::GameOver, GameOverWidget);

	for (auto& GameWidget : GameWidgets)
	{
			GameWidget.Value->AddToViewport();
			GameWidget.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
	if (!InGame) return;

	using namespace SnakeGame;

	Game = InGame;

	SetUIMatchState(EUIGameState::GameInProgress);
	GameplayWidget->SetScore(InGame->score());
	GameOverWidget->SetScore(InGame->score());

	InGame->subscribeOnGameplayEvent(
		[&](GameplayEvent Event)
		{
			switch (Event)
			{
			case GameplayEvent::FoodTaken: //
				GameplayWidget->SetScore(InGame->score());
				break;

			case GameplayEvent::GameCompleted: [[fallthrough]];
			case GameplayEvent::GameOver: //
				GameOverWidget->SetScore(InGame->score());
				SetUIMatchState(EUIGameState::GameOver);
				break;
			}
		});
}

void ASG_HUD::SetInputKeyNames(const FString& ResetGameKeyName)
{
	GameplayWidget->SetResetGameKeyName(ResetGameKeyName);
	GameOverWidget->SetResetGameKeyName(ResetGameKeyName);
}

void ASG_HUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Game.IsValid() && MatchState == EUIGameState::GameInProgress)
	{
		GameplayWidget->SetGameTime(Game.Pin()->gameTime());
	}
}

void ASG_HUD::SetUIMatchState(EUIGameState InMatchState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GameWidgets.Contains(InMatchState))
	{
		CurrentWidget = GameWidgets[InMatchState];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}

	MatchState = InMatchState;
}


