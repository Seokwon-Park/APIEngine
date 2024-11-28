#include "aepch.h"
#include "GameOverGameMode.h"

#include "GameOverBackground.h"
AGameOverGameMode::AGameOverGameMode()
{
}

AGameOverGameMode::~AGameOverGameMode()
{
}


void AGameOverGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AGameOverGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<AGameOverBackground>();
}
