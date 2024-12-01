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

	UAudioManager::ChangeBGM("LV12.MID");
	//GetWorld()->BindAction(EKey::Space, KeyEvent::Down, std::bind(&UEngineAPICore::OpenLevel, UEngineAPICore::GetCore(), "TogetherMenu"));

	Frame->SetFrame(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);
	Background->SetBackground(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);
	BotBackgroundL->SetBackground(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);
	BotBackgroundR->SetBackground(EPuyoGameMode::Versus, GameSettings::GetInstance().MapIndex);

	for (int i = 0; i < 6; i++)
	{
		BotFrameL[i]->SetFrame(EPuyoGameMode::Versus, 12 * (GameSettings::GetInstance().MapIndex) + i);
		BotFrameR[i]->SetFrame(EPuyoGameMode::Versus, 12 * (GameSettings::GetInstance().MapIndex) + i + 6);
	}

	//APuyoText* P1SelectLevel = GetWorld()->SpawnActor<APuyoText>();

	NameTextL->SetText(" P1");
	NameTextR->SetText(" P2");

	GameSettings::GetInstance().GameMode = EPuyoGameMode::Versus;

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
	P2Score;
}

void ATogetherPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
