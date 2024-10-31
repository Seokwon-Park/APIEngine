#include "aepch.h"
#include "PuyoPuyoContentsCore.h"
#include "PlayGameMode.h"
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
	UEngineAPICore::GetCore()->LoadResources();

	//UImageManager::GetInstance().CuttingSprite("Test.png", {50, 50});
	//UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.bmp", { 32, 32 });

	// TODO: 인트로(로딩?) 화면, 메인메뉴, 게임플레이(모드별 분리?), 
	// 게임오버? , 게임엔딩?
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Puyo Puyo Tsu");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({0, 0}, {1280, 720});
	//UEngineAPICore::GetCore()->CreateLevel("Intro");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void PuyoPuyoContentsCore::Tick()
{
}
