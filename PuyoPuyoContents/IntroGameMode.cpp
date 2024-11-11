#include "aepch.h"
#include "IntroGameMode.h"
#include "IntroBackground.h"
#include <EnginePlatform/EngineInput.h>
//테스트 용
#include "PuyoBoomFX.h"

AIntroGameMode::AIntroGameMode()
{
}

AIntroGameMode::~AIntroGameMode()
{
}

void AIntroGameMode::BeginPlay()
{
	// Todo : PressAnyKey로 바꿀것
	GetWorld()->GetInputSystem().BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AIntroGameMode::MoveScene, this));
	APuyoBoomFX* BoomFX = GetWorld()->SpawnActor<APuyoBoomFX>();
	AIntroBackground* Background = GetWorld()->SpawnActor<AIntroBackground>();
	BoomFX->SetActorLocation({ 100,100 });

}

void AIntroGameMode::Tick(float _DeltaTime)
{
	
}

void AIntroGameMode::MoveScene()
{
	UEngineAPICore::GetCore()->OpenLevel("Menu");
}
