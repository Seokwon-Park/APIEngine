#include "aepch.h"
#include "TitleGameMode.h"
#include <EnginePlatform/EngineInput.h>

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	UEngineInput::GetInstance().BindAction(Key::Enter, KeyEvent::Down, std::bind(&ATitleGameMode::MoveScene, this));
}

void ATitleGameMode::MoveScene()
{
	UEngineAPICore::GetCore()->OpenLevel("Play");
}
