// Fill out your copyright notice in the Description page of Project Settings.


#include "TarotPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TarotPlayerController.h"

ATarotPlayerState::ATarotPlayerState()
{
	ScoreLine0 = 0;
	ScoreLine1 = 0;
	ScoreLine2 = 0;
	TotalScore = 0;
}

void ATarotPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATarotPlayerState, ScoreLine0);
	DOREPLIFETIME(ATarotPlayerState, ScoreLine1);
	DOREPLIFETIME(ATarotPlayerState, ScoreLine2);
	DOREPLIFETIME(ATarotPlayerState, TotalScore);
	
}

void ATarotPlayerState::ComputeTotalScore()
{
	TotalScore = ScoreLine0 + ScoreLine1 + ScoreLine2;
}

ATarotPlayerController* ATarotPlayerState::GetTarotPC()
{
	return CastChecked<ATarotPlayerController>(GetPlayerController());
}


void ATarotPlayerState::OnRep_ScoreLine0()
{
	OnScoreUpdated.Broadcast(PlayerPosition,0,ScoreLine0);
}

void ATarotPlayerState::OnRep_ScoreLine1()
{
	OnScoreUpdated.Broadcast(PlayerPosition,1,ScoreLine1);
}

void ATarotPlayerState::OnRep_ScoreLine2()
{
	OnScoreUpdated.Broadcast(PlayerPosition,2,ScoreLine2);
}

void ATarotPlayerState::OnRep_TotalScore()
{
	OnScoreUpdated.Broadcast(PlayerPosition,3,TotalScore);
}

void ATarotPlayerState::UpdatePocket_Implementation(EPosition Position, bool bHasArcane)
{
	OnPocketUpdate.Broadcast(Position, bHasArcane);
}