// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SPDamageInterface.h"
//D:\UE_5.3\Engine\Source\Runtime\Experimental\GeometryCollectionEngine\Public\GeometryCollection\GeometryCollectionObject.h
//#include "GeometryCollection\GeometryCollectionObject.h"GeometryCollectionEngine
#include "Protocol.pb.h"
#include "SPObject.generated.h"

UCLASS()
class SPECTRUM_API ASPObject : public AActor , public ISPDamageInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPObject();
	virtual ~ASPObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnExplosionHit(float Damage);


	//TObjectPtr<class UGeometryCollection> GeometryCollection ;

public:
	class Protocol::PositionInfo* ObjectInfo; // 현재 위치
	class Protocol::PositionInfo* DestInfo;	// 가려는 위치

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	//UPROPERTY(EditAnywhere);
	//TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHasBeenCalled;

	void SetPostionInfo(const Protocol::PositionInfo& Info);
	void SetDestInfo(const Protocol::PositionInfo& Info);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "ture"))
	TObjectPtr<UStaticMeshComponent> ObjectMesh ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "ture"))
	FVector ObjectLocation;

protected:// chaos distruction
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UGeometryCollection> GeometryCollection;
};
