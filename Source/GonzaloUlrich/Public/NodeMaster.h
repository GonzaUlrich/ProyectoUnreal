// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeNode.h"
#include "GameFramework/Actor.h"
#include "NodeMaster.generated.h"

UCLASS()
class GONZALOULRICH_API ANodeMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeMaster();


	UPROPERTY(EditAnywhere)
		ACubeNode* SpawnCube;

	void SpawnAllNodes();

	UPROPERTY(EditAnywhere)
	int maxNumberOfCubesH=7;

	UPROPERTY(EditAnywhere)
	int maxNumberOfCubesW = 7;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	class ACubeNode* cNode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void BalanceDeRandom();
	TArray <ACubeNode*> allCubes;
	TArray <int> allRandomValues;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
