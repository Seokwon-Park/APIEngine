#include "aepch.h"
#include "EnemySelector.h"



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
}

void AEnemySelector::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Timer -= _DeltaTime;
	if (Timer < 0.0f)
	{
		EnemyList[CurIndex]->SetOff();
		CurIndex++;
		if (CurIndex >= Size)
		{
			CurIndex %= Size;
			Delay *= 2.0f;
		}
		Frame->SetFrameState("LV" + std::to_string(Level), CurIndex);
		EnemyList[CurIndex]->SetOn();
		Timer = Delay;
	}
}

void AEnemySelector::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyList[CurIndex]->SetOn();
	Level = GameSettings::GetInstance().CurLevel;
}
