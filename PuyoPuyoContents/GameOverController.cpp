#include "aepch.h"
#include "GameOverController.h"

#include "SoloMenuGameMode.h"

AGameOverController::AGameOverController()
{
}

AGameOverController::~AGameOverController()
{
}

void AGameOverController::BeginPlay()
{
	Super::BeginPlay();


	Counter = GetActor<AGameOverCounter>();

	InputComponent->BindAction(EKey::Space, KeyEvent::Down, [=]()
		{
			if (Counter->GetCount() >= 0)
			{
				UEngineAPICore::GetCore()->ResetLevel<ASoloMenuGameMode, ADummyPawn>("SoloMenu");
				UEngineAPICore::GetCore()->OpenLevel("SoloMenu");
			}
			else
			{
				//UEngineAPICore::GetCore()->ResetLevel<ASoloMenuGameMode, ADummyPawn>("SoloMenu");
				//UEngineAPICore::GetCore()->OpenLevel("SoloMenu");
				//UAudioManager::StopBGM();
			}
		});

	InputComponent->BindAction(EKey::Esc, KeyEvent::Down, [=]()
		{
			Counter->SkipTime();
		});
}

void AGameOverController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
