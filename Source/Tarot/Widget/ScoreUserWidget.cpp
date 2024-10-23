// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUserWidget.h"

#include "Components/TextBlock.h"

void UScoreUserWidget::UpdateScoreText(uint8 ScoreValue)
{
	FString ScoreString = FString::Printf(TEXT("%d"), ScoreValue);
	Score->SetText(FText::FromString(ScoreString));
	OnScoreUpdated.Broadcast();
}

void UScoreUserWidget::SetScoreParams(bool IsPlayer1, uint8 LineParam, bool bIsTotalScoreParam = false)
{
	if (IsPlayer1)
	{
		OwningPlayer = EPosition::LEFT;
	}
	else
	{
		OwningPlayer = EPosition::RIGHT;
	}
	Line = LineParam;
	bIsTotalScore = bIsTotalScoreParam;
	
	FString ScoreString = FString::Printf(TEXT("%d"), 0);
	Score->SetText(FText::FromString(ScoreString));
}
