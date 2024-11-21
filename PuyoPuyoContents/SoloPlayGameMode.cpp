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

	Background->SetBackground(EPuyoGameMode::Solo, 0);

	GetWorld()->SpawnActor<ASoloFrame>();
	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::X, EKey::Z, EKey::Down, EKey::Left, EKey::Right);

	ControllerP2 = GetWorld()->SpawnActor<APuyoAIController>();
	ControllerP2->Possess(PuyoBoardP2);
}

void ASoloPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayGameMode::Tick(_DeltaTime);
}
