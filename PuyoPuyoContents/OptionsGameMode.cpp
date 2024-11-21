#include "aepch.h"
#include "OptionsGameMode.h"

#include "OptionsMenu.h"
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

	GetWorld()->SpawnActor<AOptionsMenu>();
	GetWorld()->SpawnActor<AOptionsBackground>();
}

void AOptionsGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
