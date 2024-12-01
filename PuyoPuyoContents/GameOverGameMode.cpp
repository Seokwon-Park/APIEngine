#include "aepch.h"
#include "GameOverGameMode.h"

#include "GameOverBackground.h"
#include "GameOverText.h"
#include "GameOverCounter.h"
#include "GameOverController.h"
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
	AGameOverBackground* BG = GetWorld()->SpawnActor<AGameOverBackground>();
	AGameOverText* Text = GetWorld()->SpawnActor<AGameOverText>();
	Text->SetActorLocation({ 80.0f,32.0f });
	AGameOverCounter* Counter = GetWorld()->SpawnActor<AGameOverCounter>();
	Counter->SetActorLocation({ 192.0f, 96.0f });
	Counter->SetupCounter(Text, BG);

	AGameOverController* Controller = GetWorld()->SpawnActor<AGameOverController>();
	Controller->Possess(Counter);
}
