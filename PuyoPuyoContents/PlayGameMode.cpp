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
	// ��� ������.
	// ��ϻѿ�
	// �����ؽ�Ʈ(TextMesh?) �?
	// �ַθ�� << ���� �̹����� �׸��� �̹���?
	// 

	APlayMap* BackGround = GetWorld()->SpawnActor<APlayMap>();
	APuyoBoard* PuyoBoard = GetWorld()->SpawnActor<APuyoBoard>();
	//APuyoBoard* PuyoBoard2 = GetWorld()->SpawnActor<APuyoBoard>();
	PuyoBoard->SetupPuyoBoard({ 48,16 }, { 32,32 });
	//PuyoBoard2->SetupPuyoBoard({ 432,16 }, { 32,32 });
}
