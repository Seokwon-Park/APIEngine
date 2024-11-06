#include "aepch.h"
#include "MenuGameMode.h"
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

	AMenuBackground* Background = GetWorld()->SpawnActor<AMenuBackground>();

}

void AMenuGameMode::Tick(float _DeltaTime)
{
}

void AMenuGameMode::MoveToScene(std::string _SceneName)
{
	UEngineAPICore::GetCore()->OpenLevel(_SceneName);

}
