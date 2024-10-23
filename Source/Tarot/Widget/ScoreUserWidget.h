// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreChangedSignature);

class UTextBlock;
enum class EPosition : uint8;
/**
 * 
 */
UCLASS()
class TAROT_API UScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	EPosition OwningPlayer = EPosition::LEFT;
	UPROPERTY(BlueprintReadWrite)
	uint8 Line = 0;
	UPROPERTY(BlueprintReadWrite)
	bool bIsTotalScore = false;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Score;

	UFUNCTION()
	void UpdateScoreText(uint8 ScoreValue);

	UFUNCTION(BlueprintCallable)
	void SetScoreParams(bool IsPlayer1, uint8 LineParam, bool bIsTotalScoreParam);
	
	UPROPERTY(BlueprintAssignable)
	FScoreChangedSignature OnScoreUpdated;
};
