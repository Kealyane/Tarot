// Fill out your copyright notice in the Description page of Project Settings.


#include "CardUserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

void UCardUserWidget::SetSlotParams(bool IsPlayer1, uint8 LineParam, uint8 ColParam)
{
	if (IsPlayer1)
	{
		OwningPlayer = EPosition::LEFT;
	}
	else
	{
		OwningPlayer = EPosition::RIGHT;
	}

	Line = LineParam;
	Col = ColParam;
}

void UCardUserWidget::CardClicked()
{
	OnClick.Broadcast(OwningPlayer, Line, Col);
}

void UCardUserWidget::ValidateChoice(bool bIsValidate)
{
	if (bIsValidate)
	{
		// TODO
	}
	else
	{
		// TODO
	}
}

void UCardUserWidget::DeactivateButton()
{
	ButtonSlot->SetIsEnabled(false);
}

void UCardUserWidget::ActivateButton()
{
	ButtonSlot->SetIsEnabled(true);
}

void UCardUserWidget::PlaceCard(UTexture2D* CardImage)
{
	ImageCard->SetBrushFromTexture(CardImage);
	OnCardPlace.Broadcast();
}
