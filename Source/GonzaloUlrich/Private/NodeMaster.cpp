// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeMaster.h"


// Sets default values
ANodeMaster::ANodeMaster()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
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
void ANodeMaster::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	for (size_t i = 0; i < allCubes.Num(); i++) {
		if (allCubes[i]->GetEventFunc()) {
			DestroyAdjacentCubes(allCubes[i]->GetLine(), allCubes[i]->GetID(), allCubes[i]->GetColor());
			//SortCubes();
			allCubes[i]->SetEventFunc(false);
		}
	}
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

	int num = 0;
	//Crea la piramide
	if (maxNumberOfCubesH >= maxNumberOfCubesW) {
		for (size_t i = 0; i < maxNumberOfCubesW; i++) {
			for (size_t j = 0; j < maxNumberOfCubesH; j++) {

				ACubeNode* TempNode = GetWorld()->SpawnActor<ACubeNode>(auxPos, rot, spawnParams);
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
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Una piramide no puede ser mas alta que su ancho");
	}
}

void ANodeMaster::BalanceDeRandom() {

	int actualRandCheck = -1;
	int afterRandCheck = -1;
	int count = 0;
	//Llenamos el array de numeros random
	for (size_t i = 0; i < maxNumberOfCubesW * maxNumberOfCubesH; i++) {
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
				while (afterRandCheck != actualRandCheck) {
					actualRandCheck = FMath::RandRange(0, 2);
				}
			}
		}

		allRandomValues.Add(actualRandCheck);
	}

}

void ANodeMaster::DestroyAdjacentCubes(int line, int cubeID, int color) {



	
	//Me fijo en la linea de abajo;
	for (size_t i = 0; i < allCubes.Num(); i++) {
		if (allCubes[i]->GetLine() == line - 1) {
			if (allCubes[i]->GetID() == cubeID)
				if (allCubes[i]->GetColor() == color && allCubes[i]->GetActorDestroy() == false) {
					allCubes[i]->SetActorDestroy(true);
					allCubes[i]->Destroy();
					DestroyAdjacentCubes(line - 1, cubeID, color);
				}
			if (allCubes[i]->GetID() == cubeID + 1)
				if (allCubes[i]->GetColor() == color && allCubes[i]->GetActorDestroy() == false) {
					allCubes[i]->SetActorDestroy(true);
					allCubes[i]->Destroy();
					DestroyAdjacentCubes(line - 1, cubeID + 1, color);
				}
		}
		//Me fijo en la misma linea 
		if (allCubes[i]->GetLine() == line) {
			if (allCubes[i]->GetID() == cubeID - 1)
				if (allCubes[i]->GetColor() == color && allCubes[i]->GetActorDestroy()==false) {
					allCubes[i]->SetActorDestroy(true);
					allCubes[i]->Destroy();
					DestroyAdjacentCubes(line, cubeID - 1, color);
				}
			if (allCubes[i]->GetID() == cubeID + 1)
				if (allCubes[i]->GetColor() == color && allCubes[i]->GetActorDestroy() == false) {
					allCubes[i]->SetActorDestroy(true);
					allCubes[i]->Destroy();
					DestroyAdjacentCubes(line, cubeID + 1, color);
				}
		}
		//Me fijo en la linea de arriba
		if (allCubes[i]->GetLine() == line + 1) {
			if (allCubes[i]->GetID() == cubeID - 1)
				if (allCubes[i]->GetColor() == color && allCubes[i]->GetActorDestroy() == false) {
					allCubes[i]->SetActorDestroy(true);
					allCubes[i]->Destroy();
					DestroyAdjacentCubes(line + 1, cubeID - 1, color);
				}
			if (allCubes[i]->GetID() == cubeID)
				if (allCubes[i]->GetColor() == color && allCubes[i]->GetActorDestroy() == false) {
					allCubes[i]->SetActorDestroy(true);
					allCubes[i]->Destroy();
					DestroyAdjacentCubes(line + 1, cubeID, color);
				}
		}
	}
}


void ANodeMaster::SortCubes() {
	int auxLine = 0;
	int auxID = 0;
	FVector posAux;
		for (size_t i = 0; i < allCubes.Num(); i++) {
			if (allCubes[i]->GetActorDestroy()) {
				for (size_t j = i + 1; j < allCubes.Num(); j++)
				{
					if (allCubes[i]->GetLine() + 1 == allCubes[j]->GetLine())
					{
						if (allCubes[i]->GetID() == allCubes[j]->GetID() - 1 && allCubes[j]->GetActorDestroy() == false) {
							posAux = allCubes[j - 1]->GetActorLocation();
							allCubes[j - 1]->SetActorLocation(allCubes[i]->GetActorLocation());
							allCubes[i]->SetActorLocation(posAux);
							auxLine = allCubes[j - 1]->GetLine();
							allCubes[j - 1]->SetLine(allCubes[i]->GetLine());
							allCubes[i]->SetLine(auxLine);
							auxID = allCubes[j - 1]->GetID();
							allCubes[j - 1]->SetID(allCubes[i]->GetID());
							allCubes[i]->SetID(auxID);
							break;
						}

						if (allCubes[i]->GetID() == allCubes[j]->GetID() && allCubes[j]->GetActorDestroy() == false) {
							posAux = allCubes[j]->GetActorLocation();
							allCubes[j]->SetActorLocation(allCubes[i]->GetActorLocation());
							allCubes[i]->SetActorLocation(posAux);
							auxLine = allCubes[j]->GetLine();
							allCubes[j]->SetLine(allCubes[i]->GetLine());
							allCubes[i]->SetLine(auxLine);
							auxID = allCubes[j]->GetID();
							allCubes[j]->SetID(allCubes[i]->GetID());
							allCubes[i]->SetID(auxID);
							break;
						}
					}
				}
			}
		

	}
}

void ANodeMaster::SortCubes(int line, int cubeID, int numTarray) {
	
}