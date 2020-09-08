// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

enum EColors {
	Red,
	Green,
	Blue 
};

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeNode.generated.h"



UCLASS()
class GONZALOULRICH_API ACubeNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeNode();

	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	int ID = 0;
	int line = 0;

	UFUNCTION()
	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	//class UMaterial* redColor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BoxMesh;

	UMaterial* ColorRed;
	UMaterial* ColorGreen;
	UMaterial* ColorBlue;

	
	void SetID(int num);
	void SetLine(int num);
	void SetColor(int num);
	int GetID();
	int GetLine();
	//UFUNCTION()
	//void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
