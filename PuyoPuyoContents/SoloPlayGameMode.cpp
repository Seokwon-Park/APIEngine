#include "aepch.h"
#include "SoloPlayGameMode.h"

#include "PuyoAIController.h"
#include "PuyoPlayerController.h"
#include "EnemyImage.h"

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

	NameTextL->SetText("ARLE");
	NameTextR->SetText(EnemyNameShort[GameSettings::GetInstance().EnemyIndex]);

	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::X, EKey::Z, EKey::Down, EKey::Left, EKey::Right);

	ControllerP2 = GetWorld()->SpawnActor<APuyoAIController>();
	ControllerP2->Possess(PuyoBoardP2);

	APuyoText* StageText = GetWorld()->SpawnActor<APuyoText>();
	StageText->SetupText(10, EPuyoBoardColor::Green);
	std::string StageStr = "Stage " + std::to_string(GameSettings::GetInstance().CurStage);
	//StageStr = "Final Stage";
	StageText->SetText(StageStr);
	StageText->SetActorLocation({320-StageStr.size() * 8.0f,192.0f});
	
	MiniCar = GetWorld()->SpawnActor<AMiniCarbuncle>();
	MiniCar->SetActorLocation({ 256,384 });
	MiniCar->AddEvent([=]()
		{
			PuyoBoardP1->StartGame();
			PuyoBoardP2->StartGame();
		});

	AEnemyImage* Image = GetWorld()->SpawnActor<AEnemyImage>();
	Image->SetActorLocation({ 240, 224 });
}

void ASoloPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayGameMode::Tick(_DeltaTime);
}
