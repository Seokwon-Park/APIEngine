#include "aepch.h"
#include "ResultUI.h"

AResultUI::AResultUI()
{
	LeftOffset = { 32,32 };
	RightOffset = { 412,32 };
}

AResultUI::~AResultUI()
{
}


int AResultUI::CalculateBonusScore(int _Time)
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

void AResultUI::SetupResult(long long _ElapsedTime, APuyoText* _PlayerScore)
{
	CurStep = EResultStep::Show;
	Elapsed = _ElapsedTime;
	Bonus = CalculateBonusScore(_ElapsedTime);
	StagePoint = _PlayerScore->GetScore();
	PlayerScore = _PlayerScore;
	RestPoint = GameSettings::GetInstance().RestToNextLevel;
}

void AResultUI::Idle()
{
	if (CheckPoint1 && CheckPoint2 && CheckPoint3)
		CurStep = EResultStep::Adjust;
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
			BonusScore->SetActive(true);
			BonusScore->SetText(Bonus);
			StageText1->SetActive(true);
			StageText2->SetActive(true);
			StagePointText->SetText(StagePoint);
			PtsText2->SetActive(true);
			RestText1->SetActive(true);
			RestText2->SetActive(true);
			RestPointText->SetText(RestPoint);
			PtsText3->SetActive(true);
			CheckPoint3 = true;
		});
	CurStep = EResultStep::Idle;

}

void AResultUI::AdjustScore()
{
	if (Bonus > 0)
	{
		
	}
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

	switch (CurStep)
	{
	case EResultStep::Idle:
		Idle();
		break;
	case EResultStep::Show:
		ShowText();
		break;
	case EResultStep::Adjust:
		AdjustScore();
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

	BonusScore = GetWorld()->SpawnActor<APuyoText>();
	BonusScore->SetActorLocation(LeftOffset + FVector2D(48, 208));
	BonusScore->SetupText(5, EPuyoBoardColor::Red, ETextAlign::Right);
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

	PtsText3 = GetWorld()->SpawnActor<ANameText>();
	PtsText3->SetActorLocation(RightOffset + FVector2D(128, 224));
	PtsText3->SetText("Pts");

	LevelUp = GetWorld()->SpawnActor<APuyoText>();
	LevelUp->SetActorLocation(RightOffset + FVector2D(32, 288));
	LevelUp->SetupText(7, EPuyoBoardColor::Red, ETextAlign::Right);
	LevelUp->SetText("Level Up");


	YouWin->SetActive(false);
	PlayTime->SetActive(false);
	ElapsedTime->SetActive(false);
	SecText->SetActive(false);
	BonusText->SetActive(false);
	PtsText->SetActive(false);
	BonusScore->SetActive(false);
	StageText1->SetActive(false);
	StageText2->SetActive(false);
	PtsText2->SetActive(false);
	RestText1->SetActive(false);
	RestText2->SetActive(false);
	PtsText3->SetActive(false);
	LevelUp->SetActive(false);
}
