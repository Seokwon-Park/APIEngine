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

	GetWorld()->GetInputSystem().BindAction(EKey::Esc, KeyEvent::Down, std::bind(&AMenuGameMode::MoveToScene, this, "Intro"));
	GetWorld()->GetInputSystem().BindAction(EKey::Rshift, KeyEvent::Down, std::bind(&AMenuGameMode::MoveToScene, this, "TogetherPlay"));
	GetWorld()->GetInputSystem().BindAction(EKey::Lshift, KeyEvent::Down, std::bind(&AMenuGameMode::MoveToScene, this, "SoloMenu"));

	AMenuBackground* Background = GetWorld()->SpawnActor<AMenuBackground>();
	for (int i = 0; i < 5; i++)
	{
		ACarbuncleMenu* Car = GetWorld()->SpawnActor<ACarbuncleMenu>();
		Car->SetActorLocation({ i*200, 200 });
	}


}

void AMenuGameMode::Tick(float _DeltaTime)
{
}

void AMenuGameMode::MoveToScene(std::string _SceneName)
{
	UEngineAPICore::GetCore()->OpenLevel(_SceneName);

}
