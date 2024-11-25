#include "aepch.h"
#include "MenuGameMode.h"

#include "MenuBackground.h"
#include "MenuManager.h"
#include <EngineCore/AudioManager.h>

AMenuGameMode::AMenuGameMode()
{
}

AMenuGameMode::~AMenuGameMode()
{
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	AMenuBackground* Background = GetWorld()->SpawnActor<AMenuBackground>();
	AMenuManager* Manager = GetWorld()->SpawnActor<AMenuManager>();
	Manager->SetActorLocation({ 32,160 });
	//UAudioManager::SoundPlay();
}

void AMenuGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	////Todo: �ӽ�(��� �̷��� ���� ��)
	//InputDelay -= _DeltaTime;
}

