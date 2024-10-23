// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TarotPlayerController.generated.h"

class UGameUserWidget;
class ATarotPlayerState;
enum class EPosition : uint8;
struct FCard;
/**
 * 
 */
UCLASS()
class TAROT_API ATarotPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	TObjectPtr<UGameUserWidget> GameWidget;
	FCard* CurrentCard;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameUserWidget> GameWidgetType;
	
	// get card from deck
	// is number => play
	// is arcane => play or stash/choose

	UFUNCTION()
	void OnSlotCardClicked(FVector CoordCard);
	
	void ShowGameBoard();
	
	/**
	 * Update UI : show card from deck
	 * @param DeckCard 
	 */
	UFUNCTION(Client, Reliable)
	void ShowCardFromDeck_UI(FCard DeckCard);
	
	/**
	 * Update UI : show panel to choose an arcane
	 */
	UFUNCTION(Client, Reliable)
	void ShowChoiceArcane_UI(FCard PocketArcane, FCard DeckArcane);

	/**
	 * Update UI : show modifications on line 
	 * @param BoardLine : line to update
	 */
	UFUNCTION(Client, Reliable)
	void UpdateBoardCards_UI(const TArray<FCard>& BoardLine);

	/**
	 * Card is Number : play on board (get coord from widget)
	 * @param line select line
	 * @param col select col
	 * @param Card card to play
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void RPCServerPlayCard(int32 line, int32 col, FCard Card);

	/**
	 * Card is Arcane : Stash or choose (get coord from widget)
	 * @param line 
	 * @param col 
	 * @param Card 
	 */
	UFUNCTION(Server, Reliable, WithValidation)
	void RPCServerStashArcane(int32 line, int32 col, FCard Card);

public:
	ATarotPlayerState* GetTarotPlayerState();
};
