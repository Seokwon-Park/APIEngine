#include "aepch.h"
#include "SoloMenuGameMode.h"
#include "SoloMenuBackground.h"

ASoloMenuGameMode::ASoloMenuGameMode()
{
}

ASoloMenuGameMode::~ASoloMenuGameMode()
{
}

void ASoloMenuGameMode::BeginPlay()
{
	ASoloMenuBackground* Background = GetWorld()->SpawnActor<ASoloMenuBackground>();

}

void ASoloMenuGameMode::Tick(float _DeltaTime)
{
}
