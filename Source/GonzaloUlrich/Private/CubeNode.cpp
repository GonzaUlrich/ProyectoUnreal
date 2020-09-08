// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeNode.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

// Sets default values
ACubeNode::ACubeNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	
	BoxMesh->SetCollisionProfileName("Trigger");
	RootComponent = BoxMesh;
	BoxMesh->OnComponentBeginOverlap.AddDynamic(this, &ACubeNode::BeginOverlap);
	
	
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	if (CubeAsset.Succeeded())
	{
		BoxMesh->SetStaticMesh(CubeAsset.Object);
		BoxMesh->AddRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		BoxMesh->SetWorldScale3D(FVector(1.0f));
		
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> redColor  (TEXT("Material'/Game/Piramide/M_Red.M_Red'"));
	ColorRed = (UMaterial*)redColor.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> greenColor(TEXT("Material'/Game/Piramide/M_Green.M_Green'"));
	ColorGreen = (UMaterial*)greenColor.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> blueColor (TEXT("Material'/Game/Piramide/M_Blue.M_Blue'"));
	ColorBlue = (UMaterial*)blueColor.Object;

}

// Called when the game starts or when spawned
void ACubeNode::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ACubeNode::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f,FColor::Green, "Holas");
	Destroy();
}


// Called every frame
void ACubeNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACubeNode::SetID(int num) {

	

	ID = num;
}

void ACubeNode::SetLine(int num) {
	line = num;
}

void ACubeNode::SetColor(int randColor)
{
	UMaterialInstanceDynamic* dynMat = UMaterialInstanceDynamic::Create(ColorRed, this);

	switch (randColor)
	{
	case Red:
		dynMat = UMaterialInstanceDynamic::Create(ColorRed, this);
		BoxMesh->SetMaterial(0, dynMat);
		break;

	case Green:
		dynMat = UMaterialInstanceDynamic::Create(ColorGreen, this);
		BoxMesh->SetMaterial(0, dynMat);
		break;

	case Blue:
		dynMat = UMaterialInstanceDynamic::Create(ColorBlue, this);
		BoxMesh->SetMaterial(0, dynMat);
		break;

	default:
		break;
	}
}

int ACubeNode::GetID()
{
	return ID;
}

int ACubeNode::GetLine()
{
	return line;
}
