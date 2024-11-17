#include "aepch.h"
#include "TogetherPlayGameMode.h"
#include "PlayBackground.h"
#include "PuyoBoardShake.h"
#include "PuyoBoard.h"
#include "PuyoText.h"
#include <EnginePlatform/KeyCode.h>

ATogetherPlayGameMode::ATogetherPlayGameMode()
{
}

ATogetherPlayGameMode::~ATogetherPlayGameMode()
{

}

void ATogetherPlayGameMode::BeginPlay()
{
	// Actor
	// ��� ������.
	// ��ϻѿ�
	// �����ؽ�Ʈ(TextMesh?) �?
	// �ַθ�� << ���� �̹����� �׸��� �̹���?
	// 
	
	APlayBackground* Background = GetWorld()->SpawnActor<APlayBackground>();
	APuyoText* Next = GetWorld()->SpawnActor<APuyoText>();
	Next->SetupText(4, EPuyoTextColor::Green);
	Next->SetActorLocation({ 9*32,32 });
	Next->SetText("NEXT");



	APuyoText* P1Score = GetWorld()->SpawnActor<APuyoText>();
	P1Score->SetupText(8, EPuyoTextColor::Red, ETextAlign::Right);
	P1Score->SetActorLocation({ 7 * 32+16, 11*32 });
	P1Score->SetText(0);
	APuyoText* P2Score = GetWorld()->SpawnActor<APuyoText>();
	P2Score->SetupText(8, EPuyoTextColor::Blue, ETextAlign::Right);
	P2Score->SetActorLocation({ 8 * 32 + 16, 12*32 });
	P2Score->SetText(0);


	APuyoBoard* PuyoBoardP1 = GetWorld()->SpawnActor<APuyoBoard>();
	//PuyoBoardP1->SetActive(false);
	APuyoBoard* PuyoBoardP2 = GetWorld()->SpawnActor<APuyoBoard>();

	UPuyoBoardShake* ShakerP1 = GetWorld()->AddPostProcess<UPuyoBoardShake>();
	ShakerP1->SetupProcess({ 32,0 });
	UPuyoBoardShake* ShakerP2 = GetWorld()->AddPostProcess<UPuyoBoardShake>();
	ShakerP2->SetupProcess({ 416,0 });

	//Player1 Setting
	PuyoBoardP1->SetActorLocation(FVector2D(32, 0));
	APuyoBoard::PuyoBoardSettings Settings;
	{
		//Settings.Offset = FVector2D(48, 16);
		Settings.PuyoSize = FVector2D(32, 32);
		Settings.BoardSize = FIntPoint(6, 13);
		Settings.Difficulty = 3;
		Settings.NextBlockCoord = FIntPoint(8, 4);
		Settings.NextNextBlockCoord = FIntPoint(9, 5);
		Settings.CounterBoard = PuyoBoardP2;
		Settings.Score = P1Score;
		Settings.Shaker = ShakerP1;
	}
	PuyoBoardP1->SetupPuyoBoard(Settings);
	PuyoBoardP1->SetKey(EKey::Z, EKey::X, EKey::B, EKey::F, EKey::H);
	//PuyoBoardP1->SetKey(EKey::Up, EKey::Down, EKey::Left, EKey::Right);

	//test1->SetEnable();

	//Player2 Setting
	PuyoBoardP2->SetActorLocation(FVector2D(416, 0));
	{
		Settings.BoardSize = FIntPoint(6, 13);
		Settings.Difficulty = 3;
		Settings.NextBlockCoord = FIntPoint(11, 4);
		Settings.NextNextBlockCoord = FIntPoint(10, 5);
		Settings.CounterBoard = PuyoBoardP1;
		Settings.Score = P2Score;
		Settings.Shaker = ShakerP2;
	}
	PuyoBoardP2->SetupPuyoBoard(Settings);
	PuyoBoardP2->SetKey(EKey::Slash, EKey::Period, EKey::Down, EKey::Left, EKey::Right);


	//test2->SetEnable();
}
