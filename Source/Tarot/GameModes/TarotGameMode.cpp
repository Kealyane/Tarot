// Fill out your copyright notice in the Description page of Project Settings.


#include "TarotGameMode.h"

#include "TarotGameState.h"
#include "Tarot/Deck.h"
#include "Tarot/Player/TarotPlayerController.h"
#include "Tarot/Player/TarotPlayerState.h"

void ATarotGameMode::StartGame()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Game mode : StartGame")));
	}
	if (UWorld* World = GetWorld())
	{
		Deck = World->SpawnActor<ADeck>(DeckType);
	}
	TarotGameState = GetGameState<ATarotGameState>();
	TarotGameState->CurrentPlayerTurn = EPosition::LEFT;
	TarotGameState->InitBoardGame();
	StartTurn();
}

void ATarotGameMode::StartTurn()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Game mode : StartTurn")));
	}
	FCard Card = Deck->DrawCard();
	TarotGameState->SendCardToCurrentPlayer(Card);
}

void ATarotGameMode::EndTurn()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Game mode : EndTurn")));
	}
	TarotGameState->NextPlayer();
}

void ATarotGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Game mode : BeginPlay")));
	}
	
	TarotGameState = GetGameState<ATarotGameState>();
	TarotGameState->CurrentPlayerTurn = EPosition::LEFT;
	TarotGameState->InitBoardGame();
	if (UWorld* World = GetWorld())
	{
		Deck = World->SpawnActor<ADeck>(DeckType);
	}
	
	for (auto& PlayerState : TarotGameState->PlayerArray)
	{
		if(ATarotPlayerState* TarotPlayerState = CastChecked<ATarotPlayerState>(PlayerState))
		{
			if (ATarotPlayerController* TPC = TarotPlayerState->GetTarotPC())
			{
				TPC->ShowGameBoard();
			}
		}
	}
	StartTurn();
}

