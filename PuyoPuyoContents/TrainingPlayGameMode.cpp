#include "aepch.h"
#include "TrainingPlayGameMode.h"

#include "TrainingFrame.h"

#include "PuyoPlayerController.h"

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

	UAudioManager::ChangeBGM("LV5.MID");

	Frame->SetFrame(EPuyoGameMode::Training, 0);
	Background->SetBackground(EPuyoGameMode::Training, 0);
	BotBackgroundL->SetBackground(EPuyoGameMode::Training, 0);
	BotBackgroundR->SetBackground(EPuyoGameMode::Training, 1);

	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::G, EKey::H, EKey::S, EKey::A, EKey::D);

	ControllerP2 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP2->Possess(PuyoBoardP2);
	ControllerP2->SetKey(EKey::Slash, EKey::Period, EKey::Down, EKey::Left, EKey::Right);
}

void ATrainingPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

