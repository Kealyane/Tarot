// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"

#include "GameModes/TarotGameMode.h"
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

bool ABoard::IsSlotOccupied(int32 line, int32 col)
{
	return BoardGame[line][col] != nullptr;
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

bool ABoard::IsLineComplete(EPosition PlayerPos, int32 line)
{
	if (PlayerPos == EPosition::LEFT)
	{
		for (int i = 0; i < 3; i++)
		{
			if (BoardGame[line][i] == nullptr) return false;
		}
		return true;
	}
	if (PlayerPos == EPosition::RIGHT)
	{
		for (int i = 3; i < 6; i++)
		{
			if (BoardGame[line][i] == nullptr) return false;
		}
		return true;
	}
	return false;
}

void ABoard::ReplaceOpponentCards(EPosition OpponentPlayerPos, int32 line)
{
	if (OpponentPlayerPos == EPosition::LEFT)
	{
		for (int col = 2; col >= 0; col--)
		{
			if (BoardGame[line][col] == nullptr) 
			{
				for (int32 i = col - 1; i >= 0; i--)
				{
					if (BoardGame[line][i] != nullptr)
					{
						BoardGame[line][col] = BoardGame[line][i];
						BoardGame[line][i] = nullptr; 
						break; 
					}
				}
			}
		}
	}
	if (OpponentPlayerPos == EPosition::RIGHT)
	{
		for (int col = 3; col < 6; col++)
		{
			if (BoardGame[line][col] == nullptr) 
			{
				for (int32 i = col + 1; i < 6; i++)
				{
					if (BoardGame[line][i] != nullptr)
					{
						BoardGame[line][col] = BoardGame[line][i];
						BoardGame[line][i] = nullptr; 
						break; 
					}
				}
			}
		}
	}
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

// ARCANES

bool ABoard::CanPlayFool(EPosition PlayerPos, int32 lineCard1, int32 colCard1, int32 lineCard2, int32 colCard2)
{
	return IsSlotInPlayerBoard(PlayerPos, lineCard1, colCard1) &&
		IsSlotInPlayerBoard(PlayerPos, lineCard2, colCard2) &&
		IsSlotOccupied(lineCard1, colCard1) &&
		IsSlotOccupied(lineCard2, colCard2);
}

TArray<FCard*> ABoard::PlayFool(EPosition PlayerPos, int32 lineCard1, int32 colCard1, int32 lineCard2, int32 colCard2)
{
	SwitchCard(lineCard1, colCard1, lineCard2, colCard2);
	
	TArray<FCard*> RemoveCards;
	
	if (IsLineAFamily(PlayerPos, lineCard1))
	{
		RemoveCards.Append(FamilyEffect(PlayerPos, lineCard1));
	}
	if (IsLineAFamily(PlayerPos, lineCard2))
	{
		RemoveCards.Append(FamilyEffect(PlayerPos, lineCard2));
	}
	RemoveCards.Append(NumberEffect(PlayerPos, lineCard1, BoardGame[lineCard1][colCard1]));
	RemoveCards.Append(NumberEffect(PlayerPos, lineCard2, BoardGame[lineCard2][colCard2]));
	
	return RemoveCards;
}


// EFFECTS

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

bool ABoard::IsLineAFamily(EPosition CurrentPLayer, int32 line)
{
	if (IsLineComplete(CurrentPLayer,line))
	{
		int32 col = 0;
		if (CurrentPLayer == EPosition::RIGHT)
		{
			col = 3;
		}
		FCard* Card = BoardGame[line][col];
		return IsLineAFamily(CurrentPLayer, line, Card);
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
		// move cards toward center if holes
		if (RemovedCard.Num() != 0)
		{
			ReplaceOpponentCards(EPosition::RIGHT, line);
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
		// move cards toward center if holes
		if (RemovedCard.Num() != 0)
		{
			ReplaceOpponentCards(EPosition::LEFT, line);
		}
	}
	return RemovedCard;
}

// ARCANES

void ABoard::SwitchCard(int32 lineCard1, int32 colCard1, int32 lineCard2, int32 colCard2)
{
	FCard* TmpCard = BoardGame[lineCard1][colCard1];
	BoardGame[lineCard1][colCard1] = BoardGame[lineCard2][colCard2];
	BoardGame[lineCard2][colCard2] = TmpCard;
}

FCard ABoard::DuplicateCard(FCard ArcaneLovers,
							int32 lineCardToDuplicate, int32 colCardToDuplicate,
							int32 lineCardSlot, int32 colCardSlot)
{
	FCard* CardToDuplicate = BoardGame[lineCardToDuplicate][colCardToDuplicate];
	ArcaneLovers.Score = CardToDuplicate->Score;
	ArcaneLovers.FamilyType = CardToDuplicate->FamilyType;
	ArcaneLovers.ImageRecto = CardToDuplicate->ImageRecto;
	return ArcaneLovers;
	//	PlaceCard(PlayerPos, lineCardSlot, colCardSlot, &ArcaneLovers);
}

void ABoard::MoveCard(int32 lineCardTaken, int32 colCardTaken,
					int32 lineCardSlot,	int32 colCardSlot)
{
	BoardGame[lineCardSlot][colCardSlot] = BoardGame[lineCardTaken][colCardTaken];
	BoardGame[lineCardTaken][colCardTaken] = nullptr;
}
