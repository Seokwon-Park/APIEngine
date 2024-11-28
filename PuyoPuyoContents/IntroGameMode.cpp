#include "aepch.h"
#include "PublisherLogo.h"
#include "OpeningPuyo.h"
#include "OpeningRoll.h"
#include "OpeningCar.h"
#include "OpeningArle.h"
#include "OpeningCoin.h"
#include "ThunderBackground.h"
#include "IntroGameMode.h"
#include "IntroBackground.h"
#include "Fader.h"
#include <EnginePlatform/EngineInputSystem.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/AudioManager.h>
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
	GetWorld()->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AIntroGameMode::MoveScene, this));
	//GetWorld()->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&UEngineSound::Stop, UAudioManager::GetInstance().FindSound("OPTheme.MP3")));

	APublisherLogo* Logo = GetWorld()->SpawnActor<APublisherLogo>();
	AIntroBackground* Background = GetWorld()->SpawnActor<AIntroBackground>();
	AThunderBackground* ThunderBackground = GetWorld()->SpawnActor<AThunderBackground>();
	AOpeningPuyo* OPPuyo = GetWorld()->SpawnActor<AOpeningPuyo>();
	AOpeningRoll* OPRoll = GetWorld()->SpawnActor<AOpeningRoll>();
	AOpeningCar* OPCar = GetWorld()->SpawnActor<AOpeningCar>();
	AOpeningArle* OPArle = GetWorld()->SpawnActor<AOpeningArle>();
	AOpeningCoin* OPCoin = GetWorld()->SpawnActor<AOpeningCoin>();
	Fader = GetWorld()->SpawnActor<AFader>();

	// 인트로 애니메이션 설정
	// 이렇게 해도 되는지는 모름.
	// 
	// 페이드 아웃 델리게이트
	UEngineDelegate FadeOutDelegate;
	FadeOutDelegate += std::bind(&AFader::SetActive, Fader, true);
	FadeOutDelegate += std::bind(&AFader::FadeOut, Fader, 0.5f);

	// 페이드 인 델리게이트
	UEngineDelegate FadeInDelegate;
	FadeInDelegate += std::bind(&AFader::SetActive, Fader, true);
	FadeInDelegate += std::bind(&AFader::FadeIn, Fader, 0.5f);

	UEngineDelegate FaderActivate;
	FadeInDelegate += std::bind(&AFader::SetActive, Fader, true);

	UEngineDelegate InitDelegate;
	InitDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, false);
	InitDelegate += std::bind(&AIntroBackground::SetActive, Background, false);
	InitDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, false);
	InitDelegate += std::bind(&AOpeningRoll::SetActive, OPRoll, false);
	InitDelegate += std::bind(&AOpeningCar::SetActive, OPCar, false);
	InitDelegate += std::bind(&AOpeningArle::SetActive, OPArle, false);
	InitDelegate += std::bind(&AOpeningCoin::SetActive, OPCoin, false);
	InitDelegate += std::bind(&APublisherLogo::SetActive, Logo, false);

	UEngineDelegate OPPuyoDelegate;
	OPPuyoDelegate += std::bind(&AFader::SetActive, Fader, false);
	OPPuyoDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	OPPuyoDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, true);
	OPPuyoDelegate += std::bind(&AOpeningPuyo::Init, OPPuyo);
	OPPuyoDelegate += std::bind(&UAudioManager::ChangeBGM, "PUYO2000.MID");
	OPPuyoDelegate += std::bind(&UAudioManager::PlayBGM);

	UEngineDelegate OPCarDelegate;
	OPCarDelegate += std::bind(&AFader::SetActive, Fader, false);
	OPCarDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	OPCarDelegate += std::bind(&AOpeningPuyo::SetActive, OPCar, true);

	UEngineDelegate OPArleDelegate;
	OPArleDelegate += std::bind(&AFader::SetActive, Fader, false);
	OPArleDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	OPArleDelegate += std::bind(&AOpeningPuyo::SetActive, OPArle, true);

	UEngineDelegate OPRollDelegate;
	OPRollDelegate += std::bind(&AFader::SetActive, Fader, false);
	OPRollDelegate += std::bind(&AIntroBackground::SetActive, Background, true);
	OPRollDelegate += std::bind(&AOpeningRoll::SetActive, OPRoll, true);

	UEngineDelegate OPRoll1 = OPRollDelegate;
	OPRoll1 += std::bind(&AOpeningRoll::SetupRoll, OPRoll, FVector2D(0.0f,-128.0f), 0.0f, 200.0f);

	UEngineDelegate OPRoll2 = OPRollDelegate;
	OPRoll2 += std::bind(&AOpeningRoll::SetupRoll, OPRoll, FVector2D(0.0f, -88.0f), 128.0f, 200.0f);

	UEngineDelegate OPRoll3 = OPRollDelegate;
	OPRoll3 += std::bind(&AOpeningRoll::SetupRoll, OPRoll, FVector2D(0.0f, -24.0f), 104.0f, 200.0f);

	UEngineDelegate OPCoinDelegate;
	OPCoinDelegate += std::bind(&AIntroBackground::SetActive, Background, true);
	OPCoinDelegate += std::bind(&AOpeningCoin::SetupCoin, OPCoin, FVector2D(304,504), FVector2D(304, 160));
	OPCoinDelegate += std::bind(&AOpeningCoin::SetActive, OPCoin, true);

	//게임 켰을때 페이드인하고 화면 초기화
	UEngineEventSystem::AddEvent(0.0f, std::bind(&AFader::FadeIn, Fader, 1.0f));
	UEngineEventSystem::AddEvent(0.0f, InitDelegate);
	UEngineEventSystem::AddEvent(0.0f, std::bind(&APublisherLogo::SetActive, Logo, true));
	//로고 화면 종료
	UEngineEventSystem::AddEvent(1.5f, FadeOutDelegate);

	//오프닝 뿌요 나옴	
	UEngineEventSystem::AddEvent(2.0f, InitDelegate);
	UEngineEventSystem::AddEvent(2.0f, OPPuyoDelegate);
	//오프닝 뿌요 화면 종료
	UEngineEventSystem::AddEvent(3.0f, FadeOutDelegate);

	//오프닝 롤 나옴
	UEngineEventSystem::AddEvent(3.5f, InitDelegate);
	UEngineEventSystem::AddEvent(3.5f, OPRoll1);
	//오프닝 롤 화면 종료
	UEngineEventSystem::AddEvent(4.5f, FadeOutDelegate);

	//오프닝 카벙클
	UEngineEventSystem::AddEvent(5.0f, InitDelegate);
	UEngineEventSystem::AddEvent(5.0f, OPCarDelegate);
	//오프닝 카벙클 화면 종료
	UEngineEventSystem::AddEvent(5.5f, FadeOutDelegate);

	//오프닝 롤 다시 나옴
	UEngineEventSystem::AddEvent(6.0f, InitDelegate);
	UEngineEventSystem::AddEvent(6.0f, OPRoll2);
	//오프닝 롤 화면 종료
	UEngineEventSystem::AddEvent(7.0f, FadeOutDelegate);

	//오프닝 아르르
	UEngineEventSystem::AddEvent(7.5f, InitDelegate);
	UEngineEventSystem::AddEvent(7.5f, OPArleDelegate);
	//오프닝 아르르 화면 종료
	UEngineEventSystem::AddEvent(9.5f, FadeOutDelegate);

	//오프닝 롤 마지막
	UEngineEventSystem::AddEvent(10.0f, InitDelegate);
	UEngineEventSystem::AddEvent(10.0f, OPRoll3);

	UEngineEventSystem::AddEvent(11.0f, [this]() {Fader->SetOrder(ERenderLayer::BottomBackground); });
	UEngineEventSystem::AddEvent(11.0f, FadeOutDelegate);
	UEngineEventSystem::AddEvent(11.0f, OPCoinDelegate);
}


void AIntroGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//EventTimer += _DeltaTime;
	//if (!EventQueue.empty() && EventQueue.front().first < EventTimer)
	//{
	//	EventQueue.front().second();
	//	EventQueue.pop();
	//}

}

void AIntroGameMode::MoveScene()
{
	UEngineAPICore::GetCore()->OpenLevel("Menu");
}
