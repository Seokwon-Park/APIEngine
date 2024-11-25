#include "aepch.h"
#include "EnemySelector.h"

#include "SoloPlayGameMode.h"


AEnemySelector::AEnemySelector()
{
}

AEnemySelector::~AEnemySelector()
{
}


void AEnemySelector::SetupSelector(int _Size, int _StartRange, ACharacterFrame* _Frame)
{
	Size = _Size;
	for (int i = _StartRange; i < _StartRange + Size; i++)
	{
		AEnemySelect* Temp = GetWorld()->SpawnActor<AEnemySelect>();
		Temp->Setup(i);
		Temp->SetOff();
		Temp->SetActorLocation(GetActorLocation() + FVector2D((i - _StartRange) * 48.0f, 0.0f));
		EnemyList.push_back(Temp);
	}
	Frame = _Frame;
	SelectTimer = RandomDevice.GetRandomFloat(5.0f, 8.0f);
}

void AEnemySelector::SelectEnemy()
{
	IsSelectEnd = true;
	Delay = 0.05f;
	Timer = 0.0f;
}

void AEnemySelector::StartPlay()
{
	GameSettings::GetInstance().GameMode = EPuyoGameMode::Solo;
	GameSettings::GetInstance().MapIndex = GameSettings::GetInstance().CurLevel - 1;
	GameSettings::GetInstance().EnemyIndex = EnemyList[CurIndex]->GetIndex();
	GameSettings::GetInstance().DestroyRule = 4;

	UEngineAPICore::GetCore()->ResetLevel<ASoloPlayGameMode, ADummyPawn>("SoloPlay");
	UEngineAPICore::GetCore()->OpenLevel("SoloPlay");//
}

void AEnemySelector::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Timer -= _DeltaTime;
	if (true == IsSelectEnd)
	{
		if (Timer < 0.0f)
		{
			Counter++;
			Timer = Delay;
		}
		if (Counter % 2 == 0)
		{
			EnemyList[CurIndex]->SetOff();
		}
		else
		{
			EnemyList[CurIndex]->SetOn();

		}
		//페이더 추가
		UEngineEventSystem::AddEvent(1.0f, std::bind(&AEnemySelector::StartPlay, this));
		return;
	}
	SelectTimer -= _DeltaTime;
	if (SelectTimer < 0.0f)
	{
		SelectEnemy();
	}
	if (Timer < 0.0f)
	{
		EnemyList[CurIndex]->SetOff();
		CurIndex++;
		if (CurIndex >= Size)
		{
			CurIndex %= Size;
			Delay *= 2.0f;
		}
		Frame->SetFrameStateEnemy("LV" + std::to_string(Level), CurIndex);
		EnemyList[CurIndex]->SetOn();
		Timer = Delay;
	}
}

void AEnemySelector::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyList[CurIndex]->SetOn();
	Level = GameSettings::GetInstance().CurLevel;

	Input = CreateDefaultSubobject<UInputComponent>("");
	Input->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AEnemySelector::SelectEnemy, this));
	Input->BindAction(EKey::Space, KeyEvent::Down, std::bind(&AEnemySelector::SelectEnemy, this));
}
