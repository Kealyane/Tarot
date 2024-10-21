// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"

#include "Player/TarotPlayerState.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

bool ABoard::IsSlotInPlayerBoard(EPosition PlayerPos, int32 line, int32 col)
{
	if (line >= 0 && line <= 2)
	{
		if (PlayerPos == EPosition::LEFT)
		{
			return col >= 0 && col <= 2; 
		}
		return col >= 3 && col <= 5;
	}
	return false;
}

bool ABoard::IsSlotPlayerPocket(EPosition PlayerPos, int32 line, int32 col)
{
	return (PlayerPos == EPosition::LEFT && line == 3 && col == 1)
	|| (PlayerPos == EPosition::RIGHT && line == 3 && col == 2);
}

bool ABoard::PlaceCard(EPosition PlayerPos, int32 lineSlot, int32 colSlot, FCard* Card)
{
	if (PlayerPos == EPosition::LEFT)
	{
		for (int32 col = 2; col >= 0; col--)
		{
			if (BoardGame[lineSlot][col] == nullptr)
			{
				BoardGame[lineSlot][col] = Card;
				return true;
			}
		}
		return false;
	}
	for (int32 col = 3; col < 6; col++)
	{
		if (BoardGame[lineSlot][col] == nullptr)
		{
			BoardGame[lineSlot][col] = Card;
			return true;
		}
	}
	return false;
}

bool ABoard::IsLineComplete(int32 line)
{
	return BoardGame[line].Num() == 3;
}

int32 ABoard::ComputeScoreLine(EPosition PlayerPos, int32 line)
{
	TMap<int32,int32> Occurences;
	int32 score = 0;
	if (PlayerPos == EPosition::LEFT)
	{
		for (int32 col = 0; col < 3; col++)
		{
			if (BoardGame[line][col] != nullptr)
			{
				int32 scoreCard = BoardGame[line][col]->Score;
				if (Occurences.Contains(scoreCard))
					Occurences[scoreCard]++;
				Occurences.Add(scoreCard, 1);
			}
		}
	}
	if (PlayerPos == EPosition::RIGHT)
	{
		for (int32 col = 3; col < 6; col++)
		{
			if (BoardGame[line][col] != nullptr)
			{
				int32 scoreCard = BoardGame[line][col]->Score;
				if (Occurences.Contains(scoreCard))
					Occurences[scoreCard]++;
				Occurences.Add(scoreCard, 1);
			}
		}
	}
	if (Occurences.Num() == 0) return 0;
	for (auto elt : Occurences)
	{
		score += elt.Key * elt.Value;
	}
	return score;
}


bool ABoard::IsLineAFamily(EPosition CurrentPLayer, int32 line, FCard* CurrentCard)
{
	if (CurrentPLayer == EPosition::LEFT)
	{
		for (int32 col = 1; col < 3; col++)
		{
			if (CurrentCard->FamilyType != BoardGame[line][col]->FamilyType) return false;
		}
		return true;
	}
	if (CurrentPLayer == EPosition::RIGHT)
	{
		for (int32 col = 3; col < 5; col++)
		{
			if (CurrentCard->FamilyType != BoardGame[line][col]->FamilyType) return false;
		}
		return true;
	}
	return false;
}

TArray<FCard*> ABoard::FamilyEffect(EPosition CurrentPLayer, int32 line)
{
	TArray<FCard*> RemovedCard;

	if (CurrentPLayer == EPosition::LEFT)
	{
		// destroy opposite line
		for (int32 col = 3; col < 6; col++)
		{
			RemovedCard.Add(BoardGame[line][col]);
			BoardGame[line][col] = nullptr;
		}
	}
	if (CurrentPLayer == EPosition::RIGHT)
	{
		// destroy opposite line
		for (int32 col = 0; col < 3; col++)
		{
			RemovedCard.Add(BoardGame[line][col]);
			BoardGame[line][col] = nullptr;
		}
	}
	// TODO : reposition cards if holes in line
	return RemovedCard;
}

TArray<FCard*> ABoard::NumberEffect(EPosition CurrentPLayer, int32 line, FCard* CurrentCard)
{
	TArray<FCard*> RemovedCard;

	if (CurrentPLayer == EPosition::LEFT)
	{
		// destroy opposite card with same number
		for (int32 col = 3; col < 6; col++)
		{
			if (BoardGame[line][col] != nullptr && BoardGame[line][col]->Score == CurrentCard->Score)
			{
				RemovedCard.Add(BoardGame[line][col]);
				BoardGame[line][col] = nullptr;
			}
		}
	}
	if (CurrentPLayer == EPosition::RIGHT)
	{
		// destroy opposite card with same number
		for (int32 col = 0; col < 3; col++)
		{
			if (BoardGame[line][col] != nullptr && BoardGame[line][col]->Score == CurrentCard->Score)
			{
				RemovedCard.Add(BoardGame[line][col]);
				BoardGame[line][col] = nullptr;
			}
		}
	}
	// TODO : reposition cards if holes in line
	return RemovedCard;
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
}

