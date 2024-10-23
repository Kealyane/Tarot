// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

enum class EPosition : uint8;

UCLASS()
class TAROT_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

	bool IsSlotInPlayerBoard(EPosition PlayerPos, int32 line, int32 col);
	bool IsSlotPlayerPocket(EPosition PlayerPos, int32 line, int32 col);
	bool IsSlotOccupied(int32 line, int32 col);
	bool PlaceCard(EPosition PlayerPos, int32 line, int32 col, FCard* Card);
	bool IsLineComplete(EPosition PlayerPos, int32 line);
	void ReplaceOpponentCards(EPosition OpponentPlayerPos, int32 line);
	
	// SCORE
	int32 ComputeScoreLine(EPosition PlayerPos, int32 line);
	
	// ARCANES
	
	// FOOL : switch on player board or opposant
	bool CanPlayFool(EPosition PlayerPos, int32 lineCard1, int32 colCard1, int32 lineCard2, int32 colCard2);
	TArray<FCard*> PlayFool(EPosition PlayerPos, int32 lineCard1, int32 colCard1, int32 lineCard2, int32 colCard2);
	// LOVERS : copy from my board
	bool CanPlayLover();
	void PlayLover();
	// NAMELESS : A -> B B-< A, sur slot vide
	bool CanPlayNameless();
	void PlayNameless();

	// EFFECTS
	bool IsLineAFamily(EPosition CurrentPLayer, int32 line, FCard* CurrentCard);
	bool IsLineAFamily(EPosition CurrentPLayer, int32 line);
	TArray<FCard*> FamilyEffect(EPosition CurrentPLayer, int32 line);
	TArray<FCard*> NumberEffect(EPosition CurrentPLayer,int32 line, FCard* CurrentCard);

private:
	TArray<TArray<FCard*>> BoardGame;

	// ARCANES
	
	// FOOL
	void SwitchCard(int32 lineCard1, int32 colCard1, int32 lineCard2, int32 colCard2);
	// LOVERS
	FCard DuplicateCard(FCard ArcaneLovers, int32 lineCardToDuplicate,int32 colCardToDuplicate, int32 lineCardSlot, int32 colCardSlot);
	// NAMELESS
	void MoveCard(int32 lineCardTaken, int32 colCardTaken, int32 lineCardSlot, int32 colCardSlot);
};
