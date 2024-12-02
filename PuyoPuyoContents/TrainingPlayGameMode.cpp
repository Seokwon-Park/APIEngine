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

	for (int i = 0; i < 6; i++)
	{
		BotFrameL[i]->SetFrame(EPuyoGameMode::Solo, 0);
		BotFrameR[i]->SetFrame(EPuyoGameMode::Solo, 1);
	}

	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::G, EKey::H, EKey::S, EKey::A, EKey::D);

	ControllerP2 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP2->Possess(PuyoBoardP2);
	ControllerP2->SetKey(EKey::Slash, EKey::Period, EKey::Down, EKey::Left, EKey::Right);

	MiniCar = GetWorld()->SpawnActor<AMiniCarbuncle>();
	MiniCar->SetActorLocation({ 336,272 });
	MiniCar->AddPopEvent([=]()
		{
			PuyoBoardP1->StartGame();
			PuyoBoardP2->StartGame();
		});
	P1Score->SetText("1P SCORE");
	P2Score->SetText("2P SCORE");
}

void ATrainingPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

