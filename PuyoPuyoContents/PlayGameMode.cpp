#include "aepch.h"
#include "PlayGameMode.h"
#include "PlayMap.h"
#include "PuyoBoard.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{

}

void APlayGameMode::BeginPlay()
{
	// Actor
	// 배경 게임판.
	// 블록뿌요
	// 점수텍스트(TextMesh?) 몇개?
	// 솔로모드 << 상대방 이미지를 그리는 이미지?
	// 

	APlayMap* BackGround = GetWorld()->SpawnActor<APlayMap>();
	APuyoBoard* PuyoBoard = GetWorld()->SpawnActor<APuyoBoard>();
	PuyoBoard->SetupPuyoBoard({ 48,16 }, { 32,32 });
}
