// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SPPortalInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USPPortalInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPECTRUM_API ISPPortalInterface
{
	GENERATED_BODY()

public:
	virtual void OverlapPortal(const FVector& Location) = 0;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
