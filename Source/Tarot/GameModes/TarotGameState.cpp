// Fill out your copyright notice in the Description page of Project Settings.


#include "TarotGameState.h"

#include "Net/UnrealNetwork.h"
#include "Tarot/Player/TarotPlayerState.h"

void ATarotGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATarotGameState, CurrentPlayerTurn);
}

void ATarotGameState::NextPlayer()
{
	CurrentPlayerTurn = CurrentPlayerTurn == EPosition::LEFT ? EPosition::RIGHT : EPosition::LEFT;
}

