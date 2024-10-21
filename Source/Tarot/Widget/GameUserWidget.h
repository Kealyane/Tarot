// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CopyTextureShaders.h"
#include "Blueprint/UserWidget.h"
#include "Tarot/Player/TarotPlayerState.h"
#include "GameUserWidget.generated.h"

struct FCard;
enum class EPosition : uint8;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickCardSlotSignature, FVector, ButtonPos);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FShowDeckCardSignature, EPosition, PlayerPos, UTexture2D*, CardRecto);
/**
 * 
 */
UCLASS()
class TAROT_API UGameUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable)
	FClickCardSlotSignature OnClickCard;

	UPROPERTY(BlueprintAssignable)
	FShowDeckCardSignature OnCardDrawFromDeck;

	UFUNCTION(BlueprintCallable)
	void ButtonCardClicked(FVector ButtonPos);

	UFUNCTION(BlueprintCallable)
	void ShowDeckCard(EPosition PlayerPos, FCard Card);

	// UFUNCTION(BlueprintCallable)
	// void StashArcane();
	
};
