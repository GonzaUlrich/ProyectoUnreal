// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeMaster.h"


// Sets default values
ANodeMaster::ANodeMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	
}

// Called when the game starts or when spawned
void ANodeMaster::BeginPlay()
{
	Super::BeginPlay();
	SpawnAllNodes();
}

// Called every frame
void ANodeMaster::Tick(float DeltaTime){
	Super::Tick(DeltaTime);


}

//Spawnea los cubos de distintos colores
void ANodeMaster::SpawnAllNodes() {

	FRotator rot = GetActorRotation();
	FVector pos = GetActorLocation();
	FVector posAux = GetActorLocation();
	FVector auxPos = pos;
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	BalanceDeRandom();

	//Calcula el ancho del cubo
	FVector origin;
	FVector boxExtent;
	
	int num=0;
	//Crea la piramide
	if (maxNumberOfCubesH>= maxNumberOfCubesW){
		for (size_t i = 0; i < maxNumberOfCubesW; i++) {
			for (size_t j = 0; j < maxNumberOfCubesH; j++) {

				ACubeNode* TempNode = GetWorld()->SpawnActor<ACubeNode>( auxPos,rot,spawnParams);
				TempNode->GetActorBounds(false, origin, boxExtent);
				TempNode->SetLine(i);
				TempNode->SetID(j);
				TempNode->SetColor(allRandomValues[num]);
				allCubes.Add(TempNode);

				auxPos.Y += boxExtent.Y * 2;
				num++;
			}
			auxPos = pos;
			auxPos.Y += boxExtent.Y;
			auxPos.Z += boxExtent.Z * 2;
			pos = auxPos;
			maxNumberOfCubesH--;
		}
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Una piramide no puede ser mas alta que su ancho");
	}
}

void ANodeMaster::BalanceDeRandom() {
	
	int actualRandCheck=-1;
	int afterRandCheck=-1;
	int count = 0;
	//Llenamos el array de numeros random
	for (size_t i = 0; i < maxNumberOfCubesW * maxNumberOfCubesH; i++)
	{
		actualRandCheck = FMath::RandRange(0, 2);
		
		if (actualRandCheck != afterRandCheck) {
			afterRandCheck = actualRandCheck;
			count = 0;
		}
		else {
			count++;
			if (count == 2) {
				actualRandCheck = FMath::RandRange(0, 2);
			}
			if (count == 3) {
				actualRandCheck = FMath::RandRange(0, 2);
				while (afterRandCheck != actualRandCheck)
				{
					actualRandCheck = FMath::RandRange(0, 2);
				}
			}
		}
		
		allRandomValues.Add(actualRandCheck);
	}

}