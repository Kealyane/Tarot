// Fill out your copyright notice in the Description page of Project Settings.


#include "Deck.h"
#include "Algo/RandomShuffle.h"

// Sets default values
ADeck::ADeck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADeck::BeginPlay()
{
	Super::BeginPlay();
}

FCard ADeck::DrawCard()
{
	Algo::RandomShuffle(Deck);

	const FCard CardDrawn = Deck[0];
	
	if (CardDrawn.ArcaneType != EArcaneType::NONE)
	{
		Deck.Remove(CardDrawn);
	}

	return CardDrawn;
}

void ADeck::BackToDeck(FCard Card)
{
	if (Card.ArcaneType != EArcaneType::NONE)
	{
		Deck.Add(Card);
	}
}




