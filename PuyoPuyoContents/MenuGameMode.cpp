#include "aepch.h"
#include "MenuGameMode.h"
#include "CarbuncleMenu.h"
#include "MenuBackground.h"
#include <EnginePlatform/EngineInput.h>

AMenuGameMode::AMenuGameMode()
{
}

AMenuGameMode::~AMenuGameMode()
{
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelNames.push_back("SoloMenu");
	LevelNames.push_back("TogetherMenu");
	LevelNames.push_back("TrainingPlay");
	LevelNames.push_back("PuzzlePlay");
	LevelNames.push_back("Options");

	GetWorld()->GetInputSystem().BindAction(EKey::Esc, KeyEvent::Down, std::bind(&AMenuGameMode::MoveToScene, this, "Intro"));
	GetWorld()->GetInputSystem().BindAction(EKey::Rshift, KeyEvent::Down, std::bind(&AMenuGameMode::MoveToScene, this, "TogetherPlay"));
	GetWorld()->GetInputSystem().BindAction(EKey::Lshift, KeyEvent::Down, std::bind(&AMenuGameMode::MoveToScene, this, "SoloMenu"));
	GetWorld()->GetInputSystem().BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AMenuGameMode::SelectMenu, this));
	GetWorld()->GetInputSystem().BindAction(EKey::Left, KeyEvent::Down, std::bind(&AMenuGameMode::MoveMenu, this, 1));
	GetWorld()->GetInputSystem().BindAction(EKey::Right, KeyEvent::Down, std::bind(&AMenuGameMode::MoveMenu, this, -1));

	AMenuBackground* Background = GetWorld()->SpawnActor<AMenuBackground>();
	for (int i = 0; i < MenuSize; i++)
	{
		ACarbuncleMenu* Car = GetWorld()->SpawnActor<ACarbuncleMenu>();
		Car->SetupCarbuncleMenu(i);
		Car->SetActorLocation({ 200 + i*200, 200 });
		if (i != CurMenuIndex)
		{
			Car->SetMenuInactive();
		}
		Menus.push_back(Car);
	}
}

void AMenuGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//Todo: 임시(계속 이렇게 둘지 모름)
	InputDelay -= _DeltaTime;
}

void AMenuGameMode::MoveToScene(std::string _SceneName)
{
	UEngineAPICore::GetCore()->OpenLevel(_SceneName);
}

void AMenuGameMode::SelectMenu()
{
	if (InputDelay < 0)
	{
		UEngineAPICore::GetCore()->OpenLevel(LevelNames[CurMenuIndex]);
	}
}

void AMenuGameMode::MoveMenu(int _Dir)
{
	// 메뉴 최대값일때 더 못밀게
	if ((CurMenuIndex == 0 && _Dir == 1) || (CurMenuIndex == MenuSize-1 && _Dir == -1)) return;
	Menus[CurMenuIndex]->SetMenuInactive();
	CurMenuIndex -= _Dir;
	Menus[CurMenuIndex]->SetMenuActive();
	for (int i = 0; i < MenuSize; i++)
	{
		Menus[i]->AddActorLocation(FVector2D(208,0)*_Dir);
	}
}
