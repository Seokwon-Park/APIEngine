#include "aepch.h"
#include "PlayGameMode.h"

#include "PuyoText.h"
#include "PuyoWarn.h"
#include "PuyoBoardShakePostProcess.h"
#include <EnginePlatform/KeyCode.h>
#include "Star.h"


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Actor
	// 배경 게임판.
	// 블록뿌요
	// 점수텍스트(TextMesh?) 몇개?
	// 솔로모드 << 상대방 이미지를 그리는 이미지?

	Frame = GetWorld()->SpawnActor<APlayFrame>();
	Background = GetWorld()->SpawnActor<APlayBackground>();
	BotBackgroundL = GetWorld()->SpawnActor<ABottomBackground>();
	BotBackgroundL->SetActorLocation({ 32,416 });
	BotBackgroundR = GetWorld()->SpawnActor<ABottomBackground>();
	BotBackgroundR->SetActorLocation({ 416,416 });

	BotFrameL.resize(6, nullptr);
	BotFrameR.resize(6, nullptr);
	for (int i = 0; i < 6; i++)
	{
		BotFrameL[i] = GetWorld()->SpawnActor<ABottomFrame>();
		BotFrameL[i]->SetActorLocation(FVector2D(32, 416) + FVector2D(i*32, 0));

		BotFrameR[i] = GetWorld()->SpawnActor<ABottomFrame>();
		BotFrameR[i]->SetActorLocation(FVector2D(416, 416) + FVector2D(i * 32, 0));
	}

	PuyoBoardP1 = GetWorld()->SpawnActor<APuyoBoard>();
	//PuyoBoardP1->SetActive(false);
	PuyoBoardP2 = GetWorld()->SpawnActor<APuyoBoard>();

	//어차피 PuyoBoard에 종속적인 애들임
	APuyoText* Next = GetWorld()->SpawnActor<APuyoText>();
	Next->SetupText(4, EPuyoBoardColor::Green);
	Next->SetActorLocation({ 9 * 32,32 });
	Next->SetText("NEXT");

	APuyoWarn* P1Warn = GetWorld()->SpawnActor<APuyoWarn>();
	APuyoWarn* P2Warn = GetWorld()->SpawnActor<APuyoWarn>();

	P1Score = GetWorld()->SpawnActor<APuyoText>();
	P1Score->SetupText(8, EPuyoBoardColor::Red, ETextAlign::Right);
	P1Score->SetActorLocation({ 7 * 32 + 16, 11 * 32 });
	P1Score->SetText(0);

	P2Score = GetWorld()->SpawnActor<APuyoText>();
	P2Score->SetupText(8, EPuyoBoardColor::Blue, ETextAlign::Right);
	P2Score->SetActorLocation({ 8 * 32 + 16, 12 * 32 });
	P2Score->SetText(0);

	NameTextL = GetWorld()->SpawnActor<ANameText>();
	NameTextL->SetText("ARLE");
	NameTextL->SetActorLocation({ 240, 80 });

	NameTextR = GetWorld()->SpawnActor<ANameText>();
	NameTextR->SetText("NAJA");
	NameTextR->SetActorLocation({ 336, 80 });

	UPuyoBoardShakePostProcess* ShakerP1 = GetWorld()->AddPostProcess<UPuyoBoardShakePostProcess>();
	ShakerP1->SetupProcess({ 32,0 });
	UPuyoBoardShakePostProcess* ShakerP2 = GetWorld()->AddPostProcess<UPuyoBoardShakePostProcess>();
	ShakerP2->SetupProcess({ 416,0 });

	//Player1 Setting
	PuyoBoardP1->SetActorLocation(FVector2D(32, 0));
	APuyoBoard::PuyoBoardSettings Settings;
	{
		//Settings.Offset = FVector2D(48, 16);
		Settings.Difficulty = 3;
		Settings.PuyoSize = FVector2D(32, 32);
		Settings.BoardSize = FIntPoint(6, 13);
		Settings.NextBlockCoord = FIntPoint(8, 4);
		Settings.NextNextBlockCoord = FIntPoint(9, 5);
		Settings.BoardColor = EPuyoBoardColor::Red;
		Settings.WarnActor = P1Warn;
		Settings.ScoreActor = P1Score;
		Settings.CounterBoardActor = PuyoBoardP2;
		Settings.ShakePostProcess = ShakerP1;
		Settings.BottomFrames = BotFrameL;
	}
	PuyoBoardP1->SetupPuyoBoard(Settings);
	//PuyoBoardP1->SetKey(EKey::G, EKey::H, EKey::S, EKey::A, EKey::D);
	//PuyoBoardP1->SetKey(EKey::Up, EKey::Down, EKey::Left, EKey::Right);

	//test1->SetEnable();

	//Player2 Setting
	PuyoBoardP2->SetActorLocation(FVector2D(416, 0));
	{
		Settings.Difficulty = 3;
		Settings.BoardSize = FIntPoint(6, 13);
		Settings.NextBlockCoord = FIntPoint(11, 4);
		Settings.NextNextBlockCoord = FIntPoint(10, 5);
		Settings.BoardColor = EPuyoBoardColor::Blue;
		Settings.WarnActor = P2Warn;
		Settings.ScoreActor = P2Score;
		Settings.CounterBoardActor = PuyoBoardP1;
		Settings.ShakePostProcess = ShakerP2;
		Settings.BottomFrames = BotFrameR;
	}
	PuyoBoardP2->SetupPuyoBoard(Settings);
	//PuyoBoardP2->SetKey(EKey::Slash, EKey::Period, EKey::Down, EKey::Left, EKey::Right);

	//예고뿌요 세팅
	P1Warn->SetActorLocation(PuyoBoardP1->GetActorLocation());
	P2Warn->SetActorLocation(PuyoBoardP2->GetActorLocation());

	//test2->SetEnable();
}


void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
