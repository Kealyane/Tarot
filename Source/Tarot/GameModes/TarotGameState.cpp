// Fill out your copyright notice in the Description page of Project Settings.


#include "TarotGameState.h"

#include "Net/UnrealNetwork.h"
#include "Tarot/Board.h"
#include "Tarot/Player/TarotPlayerState.h"
#include "Tarot/Player/TarotPlayerController.h"

void ATarotGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATarotGameState, CurrentPlayerTurn);
}

void ATarotGameState::NextPlayer()
{
	CurrentPlayerTurn = CurrentPlayerTurn == EPosition::LEFT ? EPosition::RIGHT : EPosition::LEFT;
}

void ATarotGameState::InitBoardGame()
{
	if (UWorld* World = GetWorld())
	{
		Board = World->SpawnActor<ABoard>(BoardType);
	}
}

void ATarotGameState::SendCardToCurrentPlayer_Implementation(FCard CardDeck)
{
	for (auto& PlayerState : PlayerArray)
	{
		if(ATarotPlayerState* TarotPlayerState = CastChecked<ATarotPlayerState>(PlayerState))
		{
			if (TarotPlayerState->PlayerPosition == CurrentPlayerTurn)
			{
				if (ATarotPlayerController* PC = TarotPlayerState->GetTarotPC())
				{
					PC->ShowCardFromDeck_UI(CardDeck);
					return;
				}
				else
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Game mode : failed get PC")));
					}
				}
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Game mode : not current player")));
				}
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Game state : failed to cast player state")));
			}
		}
	}
}

