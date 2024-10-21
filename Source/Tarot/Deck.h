// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Deck.generated.h"

UENUM(BlueprintType)
enum class EFamilyType : uint8
{
	NONE,
	CROW,
	DEER,
	CAT,
	WOLF,
};

UENUM(BlueprintType)
enum class EArcaneType : uint8
{
	NONE,
	LOVERS,
	FOOL,
	NAMELESS,
};

USTRUCT(BlueprintType)
struct FCard
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Card/Datas")
	EFamilyType FamilyType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Card/Datas", meta=(ClampMin="0", ClampMax="6"))
	int32 Score;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Card/Datas/Arcane")
	EArcaneType ArcaneType = EArcaneType::NONE;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Card/Textures")
	TObjectPtr<UTexture2D> ImageRecto;

	bool operator==(const FCard& Other) const
	{
		return FamilyType == Other.FamilyType && Score == Other.Score && ArcaneType == Other.ArcaneType;
	}
};

UCLASS()
class TAROT_API ADeck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCard> Deck;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Deck")
	TObjectPtr<UTexture2D> ImageVerso;

	UFUNCTION(BlueprintCallable)
	FCard DrawCard();

	UFUNCTION(BlueprintCallable)
	void BackToDeck(FCard Card);
};
