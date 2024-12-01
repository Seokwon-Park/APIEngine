#include "aepch.h"
#include "GameOverController.h"

#include "SoloMenuGameMode.h"
#include "IntroGameMode.h"

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
				if (Counter->GetGameOverEnd() == true)
				{
					GameSettings::Init();
					UAudioManager::StopBGM();
					UAudioManager::SetNoBGM();
					UEngineAPICore::GetCore()->ResetLevel<AIntroGameMode, ADummyPawn>("Intro");
					UEngineAPICore::GetCore()->OpenLevel("Intro");
				}
			}
		});

	InputComponent->BindAction(EKey::Enter, KeyEvent::Down, [=]()
		{
			if (Counter->GetCount() >= 0)
			{
				UEngineAPICore::GetCore()->ResetLevel<ASoloMenuGameMode, ADummyPawn>("SoloMenu");
				UEngineAPICore::GetCore()->OpenLevel("SoloMenu");
			}
			else
			{
				if (Counter->GetGameOverEnd() == true)
				{
					GameSettings::Init();
					UAudioManager::StopBGM();
					UAudioManager::SetNoBGM();
					UEngineAPICore::GetCore()->ResetLevel<AIntroGameMode, ADummyPawn>("Intro");
					UEngineAPICore::GetCore()->OpenLevel("Intro");
				}
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
