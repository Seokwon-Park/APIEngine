#include "aepch.h"
#include "MenuManager.h"

#include "SoloMenuGameMode.h"
#include "TogetherMenuGameMode.h"
#include "TrainingPlayGameMode.h"
#include "PuzzleGameMode.h"
#include "OptionsGameMode.h"

#include "CarbuncleMenu.h"

AMenuManager::AMenuManager()
{
	LevelNames.push_back("SoloMenu");
	LevelNames.push_back("TogetherMenu");
	LevelNames.push_back("TrainingPlay");
	LevelNames.push_back("PuzzlePlay");
	LevelNames.push_back("Options");

	Input = CreateDefaultSubobject<UInputComponent>("MenuInput");
}

AMenuManager::~AMenuManager()
{
}

void AMenuManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	InputTimer += _DeltaTime;
}

void AMenuManager::BeginPlay()
{
	Super::BeginPlay();
	//지워야할거
	//Input->BindAction(EKey::Esc, KeyEvent::Down, std::bind(&AMenuManager::MoveToScene, this, "Intro"));
	//Input->BindAction(EKey::Rshift, KeyEvent::Down, std::bind(&AMenuManager::MoveToScene, this, "TogetherPlay"));
	//Input->BindAction(EKey::Lshift, KeyEvent::Down, std::bind(&AMenuManager::MoveToScene, this, "SoloPlay"));

	//기능
	Input->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AMenuManager::SelectMenu, this));
	Input->BindAction(EKey::Left, KeyEvent::Press, std::bind(&AMenuManager::MoveMenu, this, 1));
	Input->BindAction(EKey::Right, KeyEvent::Press, std::bind(&AMenuManager::MoveMenu, this, -1));

	for (int i = 0; i < MenuSize; i++)
	{
		ACarbuncleMenu* Car = GetWorld()->SpawnActor<ACarbuncleMenu>();
		Car->SetupCarbuncleMenu(i);
		Car->SetActorLocation(GetActorLocation() + FVector2D(96 + i * 192, 0));
		if (i != CurMenuIndex)
		{
			Car->SetMenuInactive();
		}
		Menus.push_back(Car);
	}
}

void AMenuManager::MoveToScene(std::string _SceneName)
{
	UEngineAPICore::GetCore()->OpenLevel(_SceneName);
}

void AMenuManager::SelectMenu()
{
	if (InputTimer > InputDelay)
	{
		for (int i = 0; i < MenuSize; i++)
		{
			if (CurMenuIndex == i)
				continue;
			Menus[i]->PlayCloseAnimation();
			LockControl = true;
		}
		UAudioManager::SoundPlay("PuyoSelect.wav");

		UEngineAPICore::GetCore()->ResetLevel<ASoloMenuGameMode, ADummyPawn>("SoloMenu");
		UEngineAPICore::GetCore()->ResetLevel<ATogetherMenuGameMode, ADummyPawn>("TogetherMenu");
		UEngineAPICore::GetCore()->ResetLevel<ATrainingPlayGameMode, ADummyPawn>("TrainingPlay");
		UEngineAPICore::GetCore()->ResetLevel<APuzzleGameMode, ADummyPawn>("PuzzlePlay");
		UEngineAPICore::GetCore()->ResetLevel<AOptionsGameMode, ADummyPawn>("Options");
		UEngineEventSystem::AddEvent(0.4f, std::bind(&UEngineAPICore::OpenLevel, UEngineAPICore::GetCore(), LevelNames[CurMenuIndex]));
		InputTimer = 0.0f;
	}
}

void AMenuManager::MoveMenu(int _Dir)
{
	if (InputTimer < InputDelay)return;
	if (LockControl == true) return;
	for (int i = 0; i < MenuSize; i++)
	{
		IsMoving |= Menus[i]->GetIsMoving();
	}
	// 메뉴 최대값일때 더 못밀게
	if ((CurMenuIndex == 0 && _Dir == 1) || (CurMenuIndex == MenuSize - 1 && _Dir == -1)) return;
	if (IsMoving == true) return;
	UAudioManager::SoundPlay("PuyoMoveMenu.wav");
	Menus[CurMenuIndex]->SetMenuInactive();
	CurMenuIndex -= _Dir;
	Menus[CurMenuIndex]->SetMenuActive();
	for (int i = 0; i < MenuSize; i++)
	{
		Menus[i]->MoveTo(96.0f,_Dir);
	}
	InputTimer = 0.0f;
}

