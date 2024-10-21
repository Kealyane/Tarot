// Fill out your copyright notice in the Description page of Project Settings.


#include "TarotPlayerController.h"
#include "Tarot/Deck.h"
#include "TarotPlayerState.h"

void ATarotPlayerController::ShowCardFromDeck_UI_Implementation(FCard DeckCard)
{
}

void ATarotPlayerController::ShowChoiceArcane_UI_Implementation(FCard PocketArcane, FCard DeckArcane)
{
}

void ATarotPlayerController::UpdateBoardCards_UI_Implementation(const TArray<FCard>& BoardLine)
{
}

void ATarotPlayerController::RPCServerPlayCard_Implementation(int32 line, int32 col, FCard Card)
{
}

bool ATarotPlayerController::RPCServerPlayCard_Validate(int32 line, int32 col, FCard Card)
{
	if (ATarotPlayerState* PS = GetPS())
	{
		if (PS->PlayerPosition == EPosition::LEFT)
		{
			return line >= 0 && line < 3;
		}
	}
	return true;
}

void ATarotPlayerController::RPCServerStashArcane_Implementation(int32 line, int32 col, FCard Card)
{
}

bool ATarotPlayerController::RPCServerStashArcane_Validate(int32 line, int32 col, FCard Card)
{
	return true;
}

ATarotPlayerState* ATarotPlayerController::GetPS()
{
	return CastChecked<ATarotPlayerState>(GetPlayerState<ATarotPlayerState>());
}
