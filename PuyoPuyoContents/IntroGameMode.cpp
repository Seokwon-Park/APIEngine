#include "aepch.h"
#include "PublisherLogo.h"
#include "OpeningPuyo.h"
#include "ThunderBackground.h"
#include "IntroGameMode.h"
#include "IntroBackground.h"
#include "Fader.h"
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

	APublisherLogo* Logo = GetWorld()->SpawnActor<APublisherLogo>();
	AIntroBackground* Background = GetWorld()->SpawnActor<AIntroBackground>();
	AThunderBackground* ThunderBackground = GetWorld()->SpawnActor<AThunderBackground>();
	AOpeningPuyo* OPPuyo= GetWorld()->SpawnActor<AOpeningPuyo>();
	Fader = GetWorld()->SpawnActor<AFader>();

	//이렇게 하는게 맞나?? 잘모르겠다
	EngineDelegate StartInitDelegate;
	StartInitDelegate += std::bind(&AFader::FadeIn, Fader, 1.0f);
	StartInitDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, false);
	StartInitDelegate += std::bind(&AIntroBackground::SetActive, Background, false);
	StartInitDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, false);
	EventQueue.push({ 0, StartInitDelegate });

	EngineDelegate LogoEventEndDelegate;
	LogoEventEndDelegate += std::bind(&AFader::FadeOut, Fader, 1.0f);
	EventQueue.push({ 2, LogoEventEndDelegate });

	EngineDelegate BigPuyoStartDelegate;
	BigPuyoStartDelegate += std::bind(&APublisherLogo::SetActive, Logo, false);
	BigPuyoStartDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	BigPuyoStartDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, true);
	EventQueue.push({ 3, BigPuyoStartDelegate });

	EngineDelegate BigPuyoEndDelegate;
	BigPuyoEndDelegate += std::bind(&AFader::FadeOut, Fader, 1.0f);
	EventQueue.push({ 4, BigPuyoEndDelegate });

}

void AIntroGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	EventTimer += _DeltaTime;
	if (!EventQueue.empty() && EventQueue.front().first < EventTimer)
	{
		EventQueue.front().second();
		EventQueue.pop();
	}

}

void AIntroGameMode::MoveScene()
{
	UEngineAPICore::GetCore()->OpenLevel("Menu");
}
