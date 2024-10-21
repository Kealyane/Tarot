// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deck.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

enum class EPosition : uint8;
class UGameUserWidget;

UCLASS()
class TAROT_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

	bool IsSlotInPlayerBoard(EPosition PlayerPos, int32 line, int32 col);
	bool IsSlotPlayerPocket(EPosition PlayerPos, int32 line, int32 col);
	bool PlaceCard(EPosition PlayerPos, int32 line, int32 col, FCard* Card);
	bool IsLineComplete(int32 line);
	
	// SCORE
	int32 ComputeScoreLine(EPosition PlayerPos, int32 line);
	
	// ARCANES
	void SwitchCard(int32 lineCard1, int32 colCard1, int32 lineCard2, int32 colCard2); // FOOL
	void DuplicateCard(int32 line, int32 col); // LOVERS
	void MoveCard(int32 lineCardTaken, int32 colCardTaken, int32 lineCardSlot, int32 colCardSlot); // NAMELESS

	// EFFECTS
	bool IsLineAFamily(EPosition CurrentPLayer, int32 line, FCard* CurrentCard);
	TArray<FCard*> FamilyEffect(EPosition CurrentPLayer, int32 line);
	TArray<FCard*> NumberEffect(EPosition CurrentPLayer,int32 line, FCard* CurrentCard);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<TArray<FCard*>> BoardGame;
};
