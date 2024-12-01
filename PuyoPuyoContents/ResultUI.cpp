#include "aepch.h"
#include "ResultUI.h"

#include "SoloMenuGameMode.h"

AResultUI::AResultUI()
{
	LeftOffset = { 32,32 };
	RightOffset = { 412,32 };

	Input = CreateDefaultSubobject<UInputComponent>("");
	Input->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AResultUI::NextGame, this));
}

AResultUI::~AResultUI()
{
}


long long AResultUI::CalculateBonusScore(int _Time)
{
	if (_Time >= 140)
	{
		return 0;
	}
	else if (_Time >= 90)
	{
		return 500 - (_Time - 90) * 10;
	}
	else if (_Time >= 60)
	{
		return 3500 - (_Time - 60) * 100;
	}
	else if (_Time >= 40)
	{
		return 9500 - (_Time - 40) * 300;
	}
	else
	{
		return 29000 - (_Time) * 500;
	}
}

void AResultUI::SetupResult(int _ElapsedTime, APuyoText* _PlayerScore)
{
	CurStep = EResultStep::Show;
	Elapsed = _ElapsedTime;
	Bonus = CalculateBonusScore(_ElapsedTime);
	StagePoint = _PlayerScore->GetScore() - GameSettings::GetInstance().CurExp;
	PlayerScore = _PlayerScore;
	RestPoint = GameSettings::GetInstance().RestToNextLevel;
}

void AResultUI::Idle()
{
	if (CheckPoint1 && CheckPoint2 && CheckPoint3)
	{
		DBonus = FEngineMath::Max(1LL, static_cast<long long>(Bonus * UEngineAPICore::GetEngineDeltaTime()));
		StagePoint += Bonus;
		DExp = FEngineMath::Max(1LL, static_cast<long long>(StagePoint * UEngineAPICore::GetEngineDeltaTime()));
		CurStep = EResultStep::Adjust;
	}
}

void AResultUI::ShowText()
{
	UEngineEventSystem::AddEvent(1.0f, [=]()
		{
			CheckPoint1 = true;
			YouWin->SetActive(true);
		});
	UEngineEventSystem::AddEvent(2.0f, [=]()
		{
			PlayTime->SetActive(true);
			ElapsedTime->SetActive(true);
			ElapsedTime->SetText(Elapsed);
			SecText->SetActive(true);
			CheckPoint2 = true;

		});
	UEngineEventSystem::AddEvent(3.0f, [=]()
		{
			BonusText->SetActive(true);
			PtsText->SetActive(true);
			BonusScoreText->SetActive(true);
			BonusScoreText->SetScore(Bonus);
			StageText1->SetActive(true);
			StageText2->SetActive(true);
			StagePointText->SetScore(StagePoint);
			PtsText2->SetActive(true);
			RestText1->SetActive(true);
			RestText2->SetActive(true);
			RestPointText->SetActive(true);
			RestPointText->SetScoreAndUpdate(GameSettings::GetInstance().RestToNextLevel);
			PtsText3->SetActive(true);
			CheckPoint3 = true;
		});
	CurStep = EResultStep::Idle;

}

void AResultUI::AdjustScore()
{
	if (Bonus > 0)
	{
		Bonus -= DBonus;
		BonusScoreText->AddScoreAndUpdate(-DBonus);
		PlayerScore->AddScoreAndUpdate(DBonus);
		StagePointText->AddScoreAndUpdate(DBonus);
		if (Bonus <= 0)
		{
			GameSettings::GetInstance().CurExp += StagePoint;
			StagePointText->SetScoreAndUpdate(StagePoint);
			PlayerScore->SetScoreAndUpdate(GameSettings::GetInstance().CurExp);
			BonusScoreText->SetScoreAndUpdate(0);
		}
		return;
	}
	// 스테이지 포인트 계산
 	if (StagePoint > 0)
	{
		StagePoint -= DExp;
		RestPoint -= DExp;
		if (RestPoint > 0)
		{
			RestPointText->AddScoreAndUpdate(-DExp);
		}
		StagePointText->AddScoreAndUpdate(-DExp);
		//stage 포인트 정산 끝남
		if (StagePoint <= 0)
		{
			if (RestPoint > 0)
			{
				RestPointText->SetScoreAndUpdate(ScoreToNextLevel[GameSettings::GetInstance().CurLevel] - GameSettings::GetInstance().CurExp);
			}
			StagePointText->SetScoreAndUpdate(0);
		}
		return;
	}
	//레벨 업 했을때
	if (RestPoint <= 0)
	{
		GameSettings::GetInstance().CurLevel += 1;
		LevelUpText->SetActive(true);
	}
	CurStep = EResultStep::Wait;
}

void AResultUI::NextGame()
{
	if (CurStep != EResultStep::Wait)
	{
		return;
	}

	if (ScoreToNextLevel[GameSettings::GetInstance().CurLevel] <= GameSettings::GetInstance().CurExp)
	{
		GameSettings::GetInstance().RestToNextLevel = 1;
		GameSettings::GetInstance().NeedToNextLevel = GameSettings::GetInstance().CurExp + 1;
	}
	else
	{
		GameSettings::GetInstance().RestToNextLevel = ScoreToNextLevel[GameSettings::GetInstance().CurLevel] - GameSettings::GetInstance().CurExp;
		GameSettings::GetInstance().NeedToNextLevel = ScoreToNextLevel[GameSettings::GetInstance().CurLevel];
	}

	int CurEnemyIndex = GameSettings::GetInstance().EnemyIndex;
	GameSettings::GetInstance().CurStage += 1;
	GameSettings::GetInstance().IsCleared[CurEnemyIndex] = true;

	UEngineAPICore::GetCore()->ResetLevel<ASoloMenuGameMode, ADummyPawn>("SoloMenu");
	UEngineAPICore::GetCore()->OpenLevel("SoloMenu");
}

void AResultUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (CheckPoint1 == true)
	{
		FlickTimer -= _DeltaTime;
		if (FlickTimer < 0)
		{
			FlickTimer = FlickDelay;
			YouWin->SetActive(!YouWin->IsActivated());

		}
	}

	if (RestPoint < 0)
	{
		FlickTimer2 -= _DeltaTime;
		if (FlickTimer2 < 0)
		{
			FlickTimer2 = FlickDelay2;
			RestPointText->SwitchColor(EPuyoBoardColor::Blue, EPuyoBoardColor::Red, "Clear");
		}
	}

	CountingTimer -= _DeltaTime;

	switch (CurStep)
	{
	case EResultStep::Idle:
		Idle();
		break;
	case EResultStep::Show:
		ShowText();
		break;
	case EResultStep::Adjust:
		if (CountingTimer < 0.0f)
		{
			UAudioManager::SoundPlay("CountingSound.wav");
			CountingTimer = 0.05f;
		}

		AdjustScore();
		break;
	case EResultStep::Wait:
		break;
	default:
		break;
	}
}
void AResultUI::BeginPlay()
{
	Super::BeginPlay();

	YouWin = GetWorld()->SpawnActor<APuyoText>();
	YouWin->SetupText(7, EPuyoBoardColor::Green);
	YouWin->SetText("you win");
	YouWin->SetActorLocation(LeftOffset + FVector2D(32, 32));

	PlayTime = GetWorld()->SpawnActor<ANameText>();
	PlayTime->SetActorLocation(LeftOffset + FVector2D(16, 96));
	PlayTime->SetText("Play Time");

	ElapsedTime = GetWorld()->SpawnActor<APuyoText>();
	ElapsedTime->SetActorLocation(LeftOffset + FVector2D(64, 128));
	ElapsedTime->SetupText(4, EPuyoBoardColor::Red, ETextAlign::Right);
	//ElapsedTime->SetText(static_cast<long long>(Timer));

	SecText = GetWorld()->SpawnActor<ANameText>();
	SecText->SetActorLocation(LeftOffset + FVector2D(128, 144));
	SecText->SetText("Sec");

	BonusText = GetWorld()->SpawnActor<ANameText>();
	BonusText->SetActorLocation(LeftOffset + FVector2D(16, 176));
	BonusText->SetText("Bonus");

	PtsText = GetWorld()->SpawnActor<ANameText>();
	PtsText->SetActorLocation(LeftOffset + FVector2D(128, 224));
	PtsText->SetText("Pts");

	BonusScoreText = GetWorld()->SpawnActor<APuyoText>();
	BonusScoreText->SetActorLocation(LeftOffset + FVector2D(48, 208));
	BonusScoreText->SetupText(5, EPuyoBoardColor::Red, ETextAlign::Right);
	//BonusScore->SetText(CalculateBonusScore(static_cast<long long>(Timer)));

	StageText1 = GetWorld()->SpawnActor<ANameText>();
	StageText1->SetActorLocation(RightOffset + FVector2D(32, 32));
	StageText1->SetText("Stage");

	StageText2 = GetWorld()->SpawnActor<ANameText>();
	StageText2->SetActorLocation(RightOffset + FVector2D(80, 64));
	StageText2->SetText("Point");

	StagePointText = GetWorld()->SpawnActor<APuyoText>();
	StagePointText->SetActorLocation(RightOffset + FVector2D(16, 96));
	StagePointText->SetupText(7, EPuyoBoardColor::Red, ETextAlign::Right);


	PtsText2 = GetWorld()->SpawnActor<ANameText>();
	PtsText2->SetActorLocation(RightOffset + FVector2D(128, 112));
	PtsText2->SetText("Pts");

	RestText1 = GetWorld()->SpawnActor<ANameText>();
	RestText1->SetActorLocation(RightOffset + FVector2D(32, 144));
	RestText1->SetText("rest");

	RestText2 = GetWorld()->SpawnActor<ANameText>();
	RestText2->SetActorLocation(RightOffset + FVector2D(80, 176));
	RestText2->SetText("point");

	RestPointText = GetWorld()->SpawnActor<APuyoText>();
	RestPointText->SetActorLocation(RightOffset + FVector2D(16, 208));
	RestPointText->SetupText(7, EPuyoBoardColor::Red, ETextAlign::Right);
	RestPointText->SetText(RestPoint);


	PtsText3 = GetWorld()->SpawnActor<ANameText>();
	PtsText3->SetActorLocation(RightOffset + FVector2D(128, 224));
	PtsText3->SetText("Pts");

	LevelUpText = GetWorld()->SpawnActor<APuyoText>();
	LevelUpText->SetActorLocation(RightOffset + FVector2D(32, 288));
	LevelUpText->SetupText(8, EPuyoBoardColor::Green, ETextAlign::Right);
	LevelUpText->SetText("Level Up");


	YouWin->SetActive(false);
	PlayTime->SetActive(false);
	ElapsedTime->SetActive(false);
	SecText->SetActive(false);
	BonusText->SetActive(false);
	PtsText->SetActive(false);
	BonusScoreText->SetActive(false);
	StageText1->SetActive(false);
	StageText2->SetActive(false);
	PtsText2->SetActive(false);
	RestText1->SetActive(false);
	RestText2->SetActive(false);
	RestPointText->SetActive(false);
	PtsText3->SetActive(false);
	LevelUpText->SetActive(false);
}
