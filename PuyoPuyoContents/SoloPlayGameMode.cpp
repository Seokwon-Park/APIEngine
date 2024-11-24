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

	Frame->SetFrame(EPuyoGameMode::Solo, GameSettings::GetInstance().CurLevel - 1);
	Background->SetBackground(EPuyoGameMode::Solo, GameSettings::GetInstance().CurLevel-1);
	BotBackgroundL->SetBackground(EPuyoGameMode::Solo, GameSettings::GetInstance().CurLevel-1);
	BotBackgroundR->SetBackground(EPuyoGameMode::Solo, GameSettings::GetInstance().CurLevel-1);

	for (int i = 0; i < 6; i++)
	{
		BotFrameL[i]->SetFrame(EPuyoGameMode::Solo, 12 * (GameSettings::GetInstance().CurLevel - 1) + i);
		BotFrameR[i]->SetFrame(EPuyoGameMode::Solo, 12 * (GameSettings::GetInstance().CurLevel - 1) + i + 6);
	}

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
