#include "aepch.h"
#include "PuyoPuyoContentsCore.h"
#include "TogetherPlayGameMode.h"
#include "MenuGameMode.h"
#include "IntroGameMode.h"
#include "DummyPawn.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/ImageManager.h>


PuyoPuyoContentsCore::PuyoPuyoContentsCore()
{
}

PuyoPuyoContentsCore::~PuyoPuyoContentsCore()
{
}

void PuyoPuyoContentsCore::BeginPlay()
{
	UEngineDebugHelper::SetShowFPS(false);

	UEngineAPICore::GetCore()->LoadResources();

	SetupPuyoSprite();

	//Cut Text
	UImageManager::GetInstance().CuttingSprite("PUYO_BP.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_G_.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_RY.CNS.BMP", { 16,32 });

	UImageManager::GetInstance().CuttingSprite("L1_F.CNS.BMP", { 640,480 });
	UImageManager::GetInstance().CuttingSprite("MENU_KA.CNS.BMP", { 640,480 });
	UImageManager::GetInstance().CuttingSprite("MENU_KB.CNS.BMP", { 640,480 });

	//UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.bmp", { 32, 32 });
	// TODO: ��Ʈ��(�ε�?) ȭ��, ���θ޴�, �����÷���(��庰 �и�?), 
	// ���ӿ���? , ���ӿ���?
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Puyo Puyo Tsu");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 640, 480 });
	UEngineAPICore::GetCore()->CreateLevel<AIntroGameMode, ADummyPawn>("Intro");
	UEngineAPICore::GetCore()->CreateLevel<AMenuGameMode, ADummyPawn>("Menu");
	UEngineAPICore::GetCore()->CreateLevel<ATogetherPlayGameMode, ADummyPawn>("TogetherPlay");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Intro");
	//UEngineAPICore::GetCore()->OpenLevel("TogetherPlay");
}

void PuyoPuyoContentsCore::SetupPuyoSprite()
{
	//Cut Puyo
	UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_G.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_B.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_P.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_Y.CNS.BMP", { 32,32 });
}

void PuyoPuyoContentsCore::Tick()
{
}
