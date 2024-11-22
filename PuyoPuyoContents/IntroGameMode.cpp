#include "aepch.h"
#include "PublisherLogo.h"
#include "OpeningPuyo.h"
#include "OpeningRoll.h"
#include "OpeningCar.h"
#include "OpeningArle.h"
#include "ThunderBackground.h"
#include "IntroGameMode.h"
#include "IntroBackground.h"
#include "Fader.h"
#include <EnginePlatform/EngineInputSystem.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/AudioManager.h>
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
	GetWorld()->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&AIntroGameMode::MoveScene, this));
	GetWorld()->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&UEngineSound::Stop, UAudioManager::GetInstance().FindSound("OPTheme.MP3")));

	APublisherLogo* Logo = GetWorld()->SpawnActor<APublisherLogo>();
	AIntroBackground* Background = GetWorld()->SpawnActor<AIntroBackground>();
	AThunderBackground* ThunderBackground = GetWorld()->SpawnActor<AThunderBackground>();
	AOpeningPuyo* OPPuyo = GetWorld()->SpawnActor<AOpeningPuyo>();
	AOpeningRoll* OPRoll = GetWorld()->SpawnActor<AOpeningRoll>();
	AOpeningCar* OPCar = GetWorld()->SpawnActor<AOpeningCar>();
	AOpeningArle* OPArle = GetWorld()->SpawnActor<AOpeningArle>();
	Fader = GetWorld()->SpawnActor<AFader>();

	// ��Ʈ�� �ִϸ��̼� ����
	// �̷��� �ص� �Ǵ����� ��.
	// 
	// ���̵� �ƿ� ��������Ʈ
	UEngineDelegate FadeOutDelegate;
	FadeOutDelegate += std::bind(&AFader::SetActive, Fader, true);
	FadeOutDelegate += std::bind(&AFader::FadeOut, Fader, 0.5f);

	// ���̵� �� ��������Ʈ
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
	InitDelegate += std::bind(&AOpeningRoll::SetActive, OPCar, false);
	InitDelegate += std::bind(&AOpeningRoll::SetActive, OPArle, false);
	InitDelegate += std::bind(&APublisherLogo::SetActive, Logo, false);

	UEngineDelegate OPPuyoDelegate;
	OPPuyoDelegate += std::bind(&AFader::SetActive, Fader, false);
	OPPuyoDelegate += std::bind(&AThunderBackground::SetActive, ThunderBackground, true);
	OPPuyoDelegate += std::bind(&AOpeningPuyo::SetActive, OPPuyo, true);
	OPPuyoDelegate += std::bind(&UEngineSound::Play, UAudioManager::GetInstance().FindSound("OPTheme.MP3"));

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
	OPRollDelegate += std::bind(&AOpeningRoll::SetActorLocation, OPRoll, FVector2D(0, 0));
	OPRollDelegate += std::bind(&AOpeningRoll::SetActive, OPRoll, true);
	OPRollDelegate += std::bind(&AOpeningRoll::Init, OPRoll);

	//���� ������ ���̵����ϰ� ȭ�� �ʱ�ȭ
	UEngineEventSystem::AddEvent(0.0f, std::bind(&AFader::FadeIn, Fader, 1.0f));
	UEngineEventSystem::AddEvent(0.0f, InitDelegate);
	UEngineEventSystem::AddEvent(0.0f, std::bind(&APublisherLogo::SetActive, Logo, true));
	//�ΰ� ȭ�� ����
	UEngineEventSystem::AddEvent(1.5f, FadeOutDelegate);

	//������ �ѿ� ����	
	UEngineEventSystem::AddEvent(2.0f, InitDelegate);
	UEngineEventSystem::AddEvent(2.0f, OPPuyoDelegate);
	//������ �ѿ� ȭ�� ����
	UEngineEventSystem::AddEvent(3.0f, FadeOutDelegate);

	//������ �� ����
	UEngineEventSystem::AddEvent(3.5f, InitDelegate);
	UEngineEventSystem::AddEvent(3.5f, OPRollDelegate);
	//������ �� ȭ�� ����
	UEngineEventSystem::AddEvent(4.5f, FadeOutDelegate);

	//������ ī��Ŭ
	UEngineEventSystem::AddEvent(5.0f, InitDelegate);
	UEngineEventSystem::AddEvent(5.0f, OPCarDelegate);
	//������ ī��Ŭ ȭ�� ����
	UEngineEventSystem::AddEvent(5.5f, FadeOutDelegate);


	//������ �� �ٽ� ����
	UEngineEventSystem::AddEvent(6.0f, InitDelegate);
	UEngineEventSystem::AddEvent(6.0f, OPRollDelegate);
	//������ �� ȭ�� ����
	UEngineEventSystem::AddEvent(7.0f, FadeOutDelegate);

	//������ �Ƹ���
	UEngineEventSystem::AddEvent(7.5f, InitDelegate);
	UEngineEventSystem::AddEvent(7.5f, OPArleDelegate);
	//������ �Ƹ��� ȭ�� ����
	UEngineEventSystem::AddEvent(9.5f, FadeOutDelegate);

	//������ �� ������
	UEngineEventSystem::AddEvent(10.0f, InitDelegate);
	UEngineEventSystem::AddEvent(10.0f, OPRollDelegate);
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
