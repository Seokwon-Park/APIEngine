#include "aepch.h"
#include "PuyoPuyoContentsCore.h"
#include "PlayGameMode.h"
#include "IntroGameMode.h"
#include "Player.h"
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
	
	UEngineDebugHelper::SetShowFPS(true);

	UEngineAPICore::GetCore()->LoadResources();

	//Cut Puyo
	UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_G.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_B.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_Y.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_P.CNS.BMP", { 32,32 });

	UImageManager::GetInstance().CuttingSprite("L1_F.CNS.BMP", {640,480});
	
	//UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.bmp", { 32, 32 });
	// TODO: ��Ʈ��(�ε�?) ȭ��, ���θ޴�, �����÷���(��庰 �и�?), 
	// ���ӿ���? , ���ӿ���?
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Puyo Puyo Tsu");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({0, 0}, {640, 480});
	UEngineAPICore::GetCore()->CreateLevel<AIntroGameMode, APlayer>("Intro");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");
	
	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void PuyoPuyoContentsCore::Tick()
{
}
