#include "aepch.h"
#include "TogetherMenuGameMode.h"

#include "TogetherMenuBackground.h"

ATogetherMenuGameMode::ATogetherMenuGameMode()
{
}

ATogetherMenuGameMode::~ATogetherMenuGameMode()
{
}

void ATogetherMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	ATogetherMenuBackground* Bg = GetWorld()->SpawnActor<ATogetherMenuBackground>();
}

void ATogetherMenuGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

