#include "aepch.h"
#include "SoloPlayGameMode.h"

#include "PuyoAIController.h"
#include "PuyoPlayerController.h"

ASoloPlayGameMode::ASoloPlayGameMode()
{
}

ASoloPlayGameMode::~ASoloPlayGameMode()
{
}

void ASoloPlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayGameMode::BeginPlay();

	GetWorld()->SpawnActor<ASoloFrame>();
	GetWorld()->SpawnActor<ASoloBackground>();
	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::Slash, EKey::Period, EKey::Down, EKey::Left, EKey::Right);

	ControllerP2 = GetWorld()->SpawnActor<APuyoAIController>();
	ControllerP2->Possess(PuyoBoardP2);
}

void ASoloPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayGameMode::Tick(_DeltaTime);
}
