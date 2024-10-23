// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUserWidget.h"

#include "Components/Image.h"
#include "Tarot/Deck.h"

void UGameUserWidget::ButtonCardClicked(FVector ButtonPos)
{
	OnClickCard.Broadcast(ButtonPos);
}

void UGameUserWidget::ShowDeckCard(EPosition PlayerPos, FCard Card)
{
	OnCardDrawFromDeck.Broadcast(PlayerPos, Card.ImageRecto);
}

void UGameUserWidget::ResetPlayerCardDeck(EPosition PlayerPos)
{
	if (PlayerPos == EPosition::LEFT)
	{
		//P1Deck_img->SetBrushFromTexture(UTexture2D::CreateTransient(1, 1));
	}
}
