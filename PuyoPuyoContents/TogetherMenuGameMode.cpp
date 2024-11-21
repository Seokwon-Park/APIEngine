#include "aepch.h"
#include "TogetherMenuGameMode.h"



ATogetherMenuGameMode::ATogetherMenuGameMode()
{
}

ATogetherMenuGameMode::~ATogetherMenuGameMode()
{
}

void ATogetherMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<ATogetherMenuBackground>();
	Menu = GetWorld()->SpawnActor<ATogetherMenu>();
}

void ATogetherMenuGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

