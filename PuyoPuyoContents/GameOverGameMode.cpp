#include "aepch.h"
#include "GameOverGameMode.h"

#include "GameOverBackground.h"
#include "GameOverText.h"
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

	UAudioManager::ChangeBGM("GameOver.MID");
	GetWorld()->SpawnActor<AGameOverBackground>();
	AGameOverText* Text = GetWorld()->SpawnActor<AGameOverText>();
	Text->SetActorLocation({ 80.0f,32.0f });
}
