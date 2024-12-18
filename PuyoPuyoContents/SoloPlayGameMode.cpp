#include "aepch.h"
#include "SoloPlayGameMode.h"

#include "PuyoAIController.h"
#include "PuyoPlayerController.h"
#include "EnemyImage.h"
#include "ResultFrame.h"
#include "ResultUI.h"

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

	int Level = GameSettings::GetInstance().CurLevel;

	UAudioManager::ChangeBGM(LevelBGM[Level]);
	Frame->SetFrame(EPuyoGameMode::Solo, Level - 1);
	Background->SetBackground(EPuyoGameMode::Solo, Level - 1);
	BotBackgroundL->SetBackground(EPuyoGameMode::Solo, Level - 1);
	BotBackgroundR->SetBackground(EPuyoGameMode::Solo, Level - 1);

	for (int i = 0; i < 6; i++)
	{
		BotFrameL[i]->SetFrame(EPuyoGameMode::Solo, 12 * (Level - 1) + i);
		BotFrameR[i]->SetFrame(EPuyoGameMode::Solo, 12 * (Level - 1) + i + 6);
	}

	NameTextL->SetText("ARLE");
	NameTextR->SetText(EnemyNameShort[GameSettings::GetInstance().EnemyIndex]);

	PuyoBoardP1->SetSinglePlayer();

	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::X, EKey::Z, EKey::Down, EKey::Left, EKey::Right);

	ControllerP2 = GetWorld()->SpawnActor<APuyoAIController>();
	ControllerP2->Possess(PuyoBoardP2);
	ControllerP2->SetThinkDelay(FEngineMath::Max(0.05f, 0.2f - Level * 0.03f));

	P1Score->SetScoreAndUpdate(GameSettings::GetInstance().CurExp);

	APuyoText* StageText = GetWorld()->SpawnActor<APuyoText>();
	StageText->SetupText(10, EPuyoBoardColor::Green);
	std::string StageStr = "Stage " + std::to_string(GameSettings::GetInstance().CurStage);
	//StageStr = "Final Stage";
	StageText->SetText(StageStr);
	StageText->SetActorLocation({ 320 - StageStr.size() * 8.0f,192.0f });

	MiniCar = GetWorld()->SpawnActor<AMiniCarbuncle>();
	MiniCar->SetActorLocation({ 256,384 });
	MiniCar->AddPopEvent([=]()
		{
			PuyoBoardP1->StartGame();
			PuyoBoardP2->StartGame();
			Timer = 0.0f;
		});

	EnemyImage = GetWorld()->SpawnActor<AEnemyImage>();
	EnemyImage->SetActorLocation({ 240, 224 });


	AResultFrame* Result1 = GetWorld()->SpawnActor<AResultFrame>();
	Result1->SetActorLocation(PuyoBoardP1->GetActorLocation() + FVector2D(0, 32));
	Result1->SetActive(false);
	AResultFrame* Result2 = GetWorld()->SpawnActor<AResultFrame>();
	Result2->SetActorLocation(PuyoBoardP2->GetActorLocation() + FVector2D(0, 32));
	Result2->SetActive(false);

	Result = GetWorld()->SpawnActor<AResultUI>();
	//Result->SetupResult(static_cast<long long>(std::ref(Timer)), P1Score);
	UEngineEventSystem::AddEvent(0.5f,
		[=]() 
		{
			UAudioManager::SoundPlay("SoloStart.wav");
		});

	PuyoBoardP1->PuyoGameWinDelegate += [=]()
		{
			Result1->SetActive(true);
			Result1->OpenFrame();
			UAudioManager::SoundPlay("Yaho.wav");
			UAudioManager::ChangeBGM("SoloWin.MID");
			UEngineEventSystem::AddEvent(1.0f, [=]()
				{
					Result2->SetActive(true);
					Result2->OpenFrame();
					Result->SetupResult(static_cast<long long>(std::ref(Timer)), P1Score);
				});
		};

	PuyoBoardP2->PuyoGameWinDelegate += [=]()
		{
			UAudioManager::StopBGM();
			UAudioManager::SoundPlay("ARLE_Lose.wav");
			UEngineEventSystem::AddEvent(1.0f, [=]()
				{
					GameOverText = GetWorld()->SpawnActor<APuyoText>();
					GameOverText->SetupText(9, EPuyoBoardColor::Red);
					GameOverText->SetWave();
					GameOverText->SetText("Game Over");
					GameOverText->SetActorLocation({ 64, 480 });
				});
		};
}

void ASoloPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayGameMode::Tick(_DeltaTime);

	if (GameOverText != nullptr)
	{
		if (GameOverText->GetActorLocation().Y > 128.0f)
		{
			GameOverText->AddActorLocation(FVector2D::UP * _DeltaTime * 70.0f);
		}
	}
	if (PuyoBoardP2->GetCurStep() == EPuyoLogicStep::PuyoGameOver)
	{
		EnemyImage->SetLose();

	}
	if (PuyoBoardP1->GetCurStep() == EPuyoLogicStep::PuyoGameOver)
	{
		EnemyImage->SetWin();
	}
	else
	{
		Timer += _DeltaTime;
	}
}
