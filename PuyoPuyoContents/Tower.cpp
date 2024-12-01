#include "aepch.h"
#include "Tower.h"

ATower::ATower()
{
}

ATower::~ATower()
{
}


void ATower::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ATower::BeginPlay()
{
	Super::BeginPlay();
	int CurLevel = GameSettings::GetInstance().CurLevel;
	int TowerHeight = 8 - CurLevel;
	for (int i = 0; i < TowerHeight; i++)
	{
		Test = GetWorld()->SpawnActor<ATowerUnit>();
		Test->SetActorLocation(GetActorLocation() + FVector2D(0, -80*i));
		Test->SetupPillar(TowerSize[i+ CurLevel-1], i+ CurLevel-1);
	}
}
