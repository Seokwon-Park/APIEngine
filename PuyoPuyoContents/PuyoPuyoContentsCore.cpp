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
	// TODO: 인트로(로딩?) 화면, 메인메뉴, 게임플레이(모드별 분리?), 
	// 게임오버? , 게임엔딩?
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
