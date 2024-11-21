#include "aepch.h"
#include "OptionsGameMode.h"

#include "OptionsBackground.h"

AOptionsGameMode::AOptionsGameMode()
{
}

AOptionsGameMode::~AOptionsGameMode()
{
}

void AOptionsGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<AOptionsBackground>();
}

void AOptionsGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
