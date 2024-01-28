// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameOverWidget.generated.h"

class UTextBlock;

UCLASS()
class USG_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScore(uint32 Score);
	void SetResetGameKeyName(const FString& ResetGameKeyName);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResetGameText;
};
