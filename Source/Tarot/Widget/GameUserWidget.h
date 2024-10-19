// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickCardSlotSignature, FVector, ButtonPos);

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

	UFUNCTION(BlueprintCallable)
	void ButtonCardClicked(FVector ButtonPos) { OnClickCard.Broadcast(ButtonPos); }
};
