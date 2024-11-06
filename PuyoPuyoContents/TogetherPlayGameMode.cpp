#include "aepch.h"
#include "TogetherPlayGameMode.h"
#include "PlayBackground.h"
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
	// 배경 게임판.
	// 블록뿌요
	// 점수텍스트(TextMesh?) 몇개?
	// 솔로모드 << 상대방 이미지를 그리는 이미지?
	// 

	APlayBackground* Background = GetWorld()->SpawnActor<APlayBackground>();

	APuyoBoard* PuyoBoardP1 = GetWorld()->SpawnActor<APuyoBoard>();
	
	PuyoBoardP1->SetActorLocation(FVector2D(32, 0));

	APuyoBoard::PuyoBoardSettings Settings;
	{
		//Settings.Offset = FVector2D(48, 16);
		Settings.PuyoSize = FVector2D(32, 32);
		Settings.BoardSize = FIntPoint(6, 13);
		Settings.Difficulty = 3;
		Settings.NextBlockCoord = FIntPoint(8, 4);
		Settings.NextNextBlockCoord = FIntPoint(9, 5);
	}
	PuyoBoardP1->SetupPuyoBoard(Settings);
	PuyoBoardP1->SetKey(EKey::Up, EKey::Down, EKey::Left, EKey::Right);

	//PuyoBoardP1->SetKey(EKey::W, EKey::S, EKey::A, EKey::D);
	
	//APuyoBoard* PuyoBoardP2 = GetWorld()->SpawnActor<APuyoBoard>();
	//{
	//	Settings.Offset = FVector2D(432, 16);
	//	Settings.BoardSize = FIntPoint(6, 13);
	//	Settings.Difficulty = 3;
	//	Settings.NextBlockCoord = FIntPoint(11, 4);
	//	Settings.NextNextBlockCoord = FIntPoint(10, 5);
	//}
	//PuyoBoardP2->SetupPuyoBoard(Settings);
	//PuyoBoardP2->SetKey(EKey::Up, EKey::Down, EKey::Left, EKey::Right);
}
