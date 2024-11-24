#include "aepch.h"
#include "TogetherPlayGameMode.h"

#include "PuyoPlayerController.h"



ATogetherPlayGameMode::ATogetherPlayGameMode()
{
}

ATogetherPlayGameMode::~ATogetherPlayGameMode()
{

}

void ATogetherPlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayGameMode::BeginPlay();

	GetWorld()->BindAction(EKey::Space, KeyEvent::Down, std::bind(&UEngineAPICore::OpenLevel, UEngineAPICore::GetCore(), "TogetherMenu"));

	Frame->SetFrame(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);
	Background->SetBackground(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);
	BotBackgroundL->SetBackground(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);
	BotBackgroundR->SetBackground(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);

	for (int i = 0; i < 6; i++)
	{
		BotFrameL[i]->SetFrame(EPuyoGameMode::Versus, 12 * (GameSettings::GetInstance().MapIndex) + i);
		BotFrameR[i]->SetFrame(EPuyoGameMode::Versus, 12 * (GameSettings::GetInstance().MapIndex) + i + 6);
	}


	GameSettings::GetInstance().GameMode = EPuyoGameMode::Versus;

	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::G, EKey::H, EKey::S, EKey::A, EKey::D);

	ControllerP2 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP2->Possess(PuyoBoardP2);
	ControllerP2->SetKey(EKey::Slash, EKey::Period, EKey::Down, EKey::Left, EKey::Right);
}

void ATogetherPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
