// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUserWidget.h"
#include "Tarot/Deck.h"

void UGameUserWidget::ButtonCardClicked(FVector ButtonPos)
{
	OnClickCard.Broadcast(ButtonPos);
}

void UGameUserWidget::ShowDeckCard(EPosition PlayerPos, FCard Card)
{
	OnCardDrawFromDeck.Broadcast(PlayerPos, Card.ImageRecto);
}
