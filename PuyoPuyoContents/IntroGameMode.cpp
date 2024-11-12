#include "aepch.h"
#include "IntroGameMode.h"
#include "IntroBackground.h"
#include <EnginePlatform/EngineInput.h>
//�׽�Ʈ ��
#include "PuyoBoomFX.h"

AIntroGameMode::AIntroGameMode()
{
}

AIntroGameMode::~AIntroGameMode()
{
}

void AIntroGameMode::BeginPlay()
{
	// Todo : PressAnyKey�� �ٲܰ�
	GetWorld()->GetInputSystem().BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AIntroGameMode::MoveScene, this));
	
	AIntroBackground* Background = GetWorld()->SpawnActor<AIntroBackground>();
	

}

void AIntroGameMode::Tick(float _DeltaTime)
{
	
}

void AIntroGameMode::MoveScene()
{
	UEngineAPICore::GetCore()->OpenLevel("Menu");
}
