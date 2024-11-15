#include "aepch.h"
#include "PublisherLogo.h"
#include "OpeningPuyo.h"
#include "OpeningRoll.h"
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
	AOpeningRoll* OPRoll= GetWorld()->SpawnActor<AOpeningRoll>();
	Fader = GetWorld()->SpawnActor<AFader>();

	//인트로 애니메이션 설정 ㅋㅋ
	// 이렇게 해도 되는지는 모름.
	UEngineDelegate NewDelegate;
	NewDelegate += std::bind(&AFader::FadeIn, Fader, 1.0f);
	NewDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, false);
	NewDelegate += std::bind(&AIntroBackground::SetActive, Background, false);
	NewDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, false);
	NewDelegate += std::bind(&AOpeningRoll::SetActive, OPRoll, false);
	EventQueue.push({ 0.0f, NewDelegate });
	NewDelegate.Clear();

	//로고 화면 종료
	NewDelegate += std::bind(&AFader::FadeOut, Fader, 1.0f);
	EventQueue.push({ 2.0f, NewDelegate });
	NewDelegate.Clear();

	//오프닝 뿌요 나옴
	NewDelegate += std::bind(&AFader::SetActive, Fader, false);
	NewDelegate += std::bind(&APublisherLogo::SetActive, Logo, false);
	NewDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	NewDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, true);
	EventQueue.push({ 3.0f, NewDelegate });
	NewDelegate.Clear();

	//오프닝 뿌요 화면 종료1
	NewDelegate += std::bind(&AFader::SetActive, Fader, true);
	NewDelegate += std::bind(&AFader::FadeOut, Fader, .5f);
	EventQueue.push({ 3.5f, NewDelegate });
	NewDelegate.Clear();

	//오프닝 애들 나옴
	UEngineDelegate OPRollDelegate;
	OPRollDelegate += std::bind(&AFader::SetActive, Fader, false);
	OPRollDelegate += std::bind(&AIntroBackground::SetActive, Background, true);
	OPRollDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, false);
	OPRollDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, false);
	OPRollDelegate += std::bind(&AOpeningRoll::SetActive, OPRoll, true);
	EventQueue.push({ 5.0f, OPRollDelegate });
	//NewDelegate.Clear();
	
	//오프닝 애들 화면 종료2
	NewDelegate += std::bind(&AFader::SetActive, Fader, true);
	NewDelegate += std::bind(&AFader::FadeOut, Fader, .5f);
	EventQueue.push({ 6.0f, NewDelegate });
	NewDelegate.Clear();

	//다시 번쩍이2
	NewDelegate += std::bind(&AFader::SetActive, Fader, false);
	NewDelegate += std::bind(&AIntroBackground::SetActive, Background, false);
	NewDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	NewDelegate += std::bind(&AOpeningRoll::SetActive, OPRoll, false);
	EventQueue.push({ 7.0f, NewDelegate });
	NewDelegate.Clear();

	//다시 종료
	NewDelegate += std::bind(&AFader::SetActive, Fader, true);
	NewDelegate += std::bind(&AFader::FadeOut, Fader, .5f);
	EventQueue.push({ 8.0f, NewDelegate });
	NewDelegate.Clear();

	//오프닝 애들 2
	EventQueue.push({ 9.0f, OPRollDelegate });
	NewDelegate.Clear();

	//오프닝 애들 화면 종료3
	NewDelegate += std::bind(&AFader::SetActive, Fader, true);
	NewDelegate += std::bind(&AFader::FadeOut, Fader, .5f);
	EventQueue.push({ 10.0f, NewDelegate });
	NewDelegate.Clear();

	//번쩍이 3
	NewDelegate += std::bind(&AFader::SetActive, Fader, false);
	NewDelegate += std::bind(&AIntroBackground::SetActive, Background, false);
	NewDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	NewDelegate += std::bind(&AOpeningRoll::SetActive, OPRoll, false);
	EventQueue.push({11.0f, NewDelegate });
	NewDelegate.Clear();

	//다시 종료
	NewDelegate += std::bind(&AFader::SetActive, Fader, true);
	NewDelegate += std::bind(&AFader::FadeOut, Fader, .5f);
	EventQueue.push({ 12.0f, NewDelegate });
	NewDelegate.Clear();

	//오프닝 애들 라스트
	EventQueue.push({ 13.0f, OPRollDelegate });
	NewDelegate.Clear();
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
