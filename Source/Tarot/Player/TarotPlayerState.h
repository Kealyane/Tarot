// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TarotPlayerState.generated.h"


struct FPocket;
class ATarotPlayerController;

UENUM(Blueprintable)
enum class EPosition : uint8
{
	LEFT,
	RIGHT
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FScoreUpdatedSignature, EPosition, Position, int32, ScoreLineIndex, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPocketUpdateSignature, EPosition, Position, bool, bHasArcane);

/**
 * 
 */
UCLASS()
class TAROT_API ATarotPlayerState : public APlayerState
{
	GENERATED_BODY()

	ATarotPlayerState();

protected:
	UFUNCTION()
	void OnRep_ScoreLine0();
	UFUNCTION()
	void OnRep_ScoreLine1();
	UFUNCTION()
	void OnRep_ScoreLine2();
	UFUNCTION()
	void OnRep_TotalScore();
	
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

public:
	EPosition PlayerPosition;
	FPocket* PlayerPocket;
	
	// SCORE
	UPROPERTY(ReplicatedUsing="OnRep_ScoreLine0")
	int32 ScoreLine0;
	UPROPERTY(ReplicatedUsing="OnRep_ScoreLine1")
	int32 ScoreLine1;
	UPROPERTY(ReplicatedUsing="OnRep_ScoreLine2")
	int32 ScoreLine2;
	UPROPERTY(ReplicatedUsing="OnRep_TotalScore")
	int32 TotalScore;
	
	UPROPERTY(BlueprintAssignable)
	FScoreUpdatedSignature OnScoreUpdated;

	UPROPERTY(BlueprintAssignable)
	FPocketUpdateSignature OnPocketUpdate;
	
	void ComputeTotalScore();
	
	void InitPosition(EPosition Position) { PlayerPosition = Position; }

	UFUNCTION(NetMulticast, Reliable)
	void UpdatePocket(EPosition Position, bool bHasArcane);

	ATarotPlayerController* GetTarotPC();
};
