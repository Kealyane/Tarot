// Fill out your copyright notice in the Description page of Project Settings.


#include "TarotGameMode.h"

#include "TarotGameState.h"
#include "Tarot/Deck.h"
#include "Tarot/Player/TarotPlayerController.h"
#include "Tarot/Player/TarotPlayerState.h"

void ATarotGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (GetNumPlayers() == 2)
	{
		StartGame();
	}
}

void ATarotGameMode::StartGame()
{
	TarotGameState = GetGameState<ATarotGameState>();
	TarotGameState->CurrentPlayerTurn = EPosition::LEFT;
	
}

void ATarotGameMode::StartTurn()
{
	FCard Card = Deck->DrawCard();

	for (auto& PlayerState : TarotGameState->PlayerArray)
	{
		if(ATarotPlayerState* TarotPlayerState =CastChecked<ATarotPlayerState>(PlayerState))
		{
			if (TarotPlayerState->PlayerPosition == TarotGameState->CurrentPlayerTurn)
			{
				if (ATarotPlayerController* PC = TarotPlayerState->GetTarotPC())
				{
					PC->ShowCardFromDeck_UI(Card);
					return;
				}
			}
		}
	}
}

void ATarotGameMode::EndTurn()
{
	TarotGameState->NextPlayer();
}

