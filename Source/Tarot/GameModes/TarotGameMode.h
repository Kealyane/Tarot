// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TarotGameMode.generated.h"

class ATarotGameState;
class ADeck;
/**
 * 
 */
UCLASS()
class TAROT_API ATarotGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void PostLogin(APlayerController* NewPlayer) override;
	void StartGame();
	/**
	 * Pick card from deck
	 * Send card to current PC
	 */
	void StartTurn();
	
	/**
	 * Change currentPC
	 * Start turn
	 */
	void EndTurn();

private:
	TObjectPtr<ADeck> Deck;
	TObjectPtr<ATarotGameState> TarotGameState;
	
};
