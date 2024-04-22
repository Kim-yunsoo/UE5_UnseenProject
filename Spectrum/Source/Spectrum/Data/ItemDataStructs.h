#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemType : uint8
{
	Potion UMETA(DisplayName= "Potion"),
	IngredientPotion UMETA(DisplayName= "IngredientPotion")
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	FText Description; //고민
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh; //필요 없을수도!
};


USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData ItemTextData;
	
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData ItemNumericData;
	
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData ItemAssetData;
};