#pragma once

#include "CoreMinimal.h"
#include "Pocket.generated.h"

struct FCard;

USTRUCT(Blueprintable)
struct FPocket
{
	GENERATED_BODY()

	FCard* StoredArcane;
	bool bHasArcane;

	FPocket() : StoredArcane(), bHasArcane(false) {}

	void StoreInPocket(FCard* ArcaneCard)
	{
		StoredArcane = ArcaneCard;
		bHasArcane = true;
	}

	FCard* PlayArcaneFromPocket()
	{
		FCard* CardPlayed = StoredArcane;
		StoredArcane = nullptr;
		bHasArcane = false;
		return CardPlayed;
	}
};
