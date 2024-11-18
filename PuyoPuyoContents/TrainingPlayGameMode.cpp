#include "aepch.h"
#include "TrainingPlayGameMode.h"

#include "TrainingFrame.h"
#include "TrainingBackground.h"

ATrainingPlayGameMode::ATrainingPlayGameMode()
{
}

ATrainingPlayGameMode::~ATrainingPlayGameMode()
{
}

void ATrainingPlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayGameMode::BeginPlay();

	GetWorld()->SpawnActor<ATrainingFrame>();
	GetWorld()->SpawnActor<ATrainingBackground>();
}

void ATrainingPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

