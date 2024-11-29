#include "aepch.h"
#include "IntroController.h"

#include "MenuGameMode.h"

AIntroController::AIntroController()
{
	InputComponent->BindAction(EKey::AnyKey, KeyEvent::Down, std::bind(&AIntroController::SkipIntro, this));

}

AIntroController::~AIntroController()
{
}

void AIntroController::BeginPlay()
{
	Super::BeginPlay();
}

void AIntroController::SkipIntro()
{
	if (Timer > 2.5f)
	{
		UEngineAPICore::GetCore()->ResetLevel<AMenuGameMode, ADummyPawn>("Menu");
		UEngineAPICore::GetCore()->OpenLevel("Menu");
	}
}

void AIntroController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Timer += _DeltaTime;
}
