// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TarotGameState.generated.h"

struct FCard;
class ATarotPlayerController;
class ABoard;
enum class EPosition : uint8;
/**
 * 
 */
UCLASS()
class TAROT_API ATarotGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	EPosition CurrentPlayerTurn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABoard> BoardType;

	TObjectPtr<ABoard> Board;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void NextPlayer();
	void InitBoardGame();

	UFUNCTION(Client, Reliable)
	void SendCardToCurrentPlayer(FCard CardDeck);
};
