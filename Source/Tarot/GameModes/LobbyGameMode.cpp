// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Tarot/Player/TarotPlayerController.h"
#include "Tarot/Player/TarotPlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	
	if (ATarotPlayerController* TPC = CastChecked<ATarotPlayerController>(NewPlayer))
	{
		if (ATarotPlayerState* PlayerState = TPC->GetTarotPlayerState())
		{
			if (NumberOfPlayers == 1)
			{
				PlayerState->PlayerPosition = EPosition::LEFT;
			}
			else if (NumberOfPlayers == 2)
			{
				PlayerState->PlayerPosition = EPosition::RIGHT;
			}
		}
	}
	
	if (NumberOfPlayers == 2)
	{
		if (UWorld* World = GetWorld())
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/MapFanny?listen"));
		}
	}
}
