// Fill out your copyright notice in the Description page of Project Settings.


#include "TarotPlayerController.h"
#include "Tarot/Deck.h"
#include "TarotPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Tarot/Widget/GameUserWidget.h"


void ATarotPlayerController::OnSlotCardClicked(FVector CoordCard)
{
	if (CurrentCard != nullptr)
	{
		if (CurrentCard->ArcaneType != EArcaneType::NONE)
		{
			RPCServerPlayCard(CoordCard.X, CoordCard.Y, *CurrentCard);
		}
		else
		{
			// TODO :
			// play arcane -> allow clicked on cards -> end turn
			// stash -> empty -> stock arcane -> end turn
			//		-> full -> choose between pocket and new arcane -> stock choice -> end turn
			//RPCServerStashArcane(CoordCard.X, CoordCard.Y, *CurrentCard);
		}
	}
}

void ATarotPlayerController::ShowGameBoard()
{
	GameWidget = CreateWidget<UGameUserWidget>(this, GameWidgetType);
	if (GameWidget)
	{
		GameWidget->AddToViewport();
		GameWidget->OnClickCard.AddDynamic(this, &ATarotPlayerController::OnSlotCardClicked);
	}
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(GameWidget->TakeWidget()); 
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode); 
	bShowMouseCursor = true;
	
}

void ATarotPlayerController::ShowCardFromDeck_UI_Implementation(FCard DeckCard)
{
	CurrentCard = &DeckCard;
	GameWidget->ShowDeckCard(GetPS()->PlayerPosition, DeckCard);
}

void ATarotPlayerController::ShowChoiceArcane_UI_Implementation(FCard PocketArcane, FCard DeckArcane)
{
}

void ATarotPlayerController::UpdateBoardCards_UI_Implementation(const TArray<FCard>& BoardLine)
{
}

// PLAY CARD

bool ATarotPlayerController::RPCServerPlayCard_Validate(int32 line, int32 col, FCard Card)
{
	if (ATarotPlayerState* PS = GetPS())
	{
		if (PS->PlayerPosition == EPosition::LEFT)
		{
			return line >= 0 && line < 3 && col >= 0 && col < 3;
		}
		return line >= 0 && line < 3 && col >= 3 && col < 6;
	}
	return false;
}

void ATarotPlayerController::RPCServerPlayCard_Implementation(int32 line, int32 col, FCard Card)
{
	
}

void ATarotPlayerController::RPCServerStashArcane_Implementation(int32 line, int32 col, FCard Card)
{
}

bool ATarotPlayerController::RPCServerStashArcane_Validate(int32 line, int32 col, FCard Card)
{
	return true;
}



ATarotPlayerState* ATarotPlayerController::GetPS()
{
	return CastChecked<ATarotPlayerState>(GetPlayerState<ATarotPlayerState>());
}
