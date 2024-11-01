#include "aepch.h"
#include "IntroGameMode.h"
#include <EnginePlatform/EngineInput.h>

AIntroGameMode::AIntroGameMode()
{
}

AIntroGameMode::~AIntroGameMode()
{
}

void AIntroGameMode::BeginPlay()
{
	UEngineInput::GetInstance().BindAction(Key::Enter, KeyEvent::Down, std::bind(&AIntroGameMode::MoveScene, this));
}

void AIntroGameMode::Tick(float _DeltaTime)
{
	
}

void AIntroGameMode::MoveScene()
{
	UEngineAPICore::GetCore()->OpenLevel("Play");
}
