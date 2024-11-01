#include "aepch.h"
#include "PuyoPuyoContentsCore.h"
#include "PlayGameMode.h"
#include "TitleGameMode.h"
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

	UImageManager::GetInstance().CuttingSprite("Test.png", 5, 5);
	//UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.bmp", { 32, 32 });
	UEngineDebugHelper::SetShowFPS(true);
	// TODO: ��Ʈ��(�ε�?) ȭ��, ���θ޴�, �����÷���(��庰 �и�?), 
	// ���ӿ���? , ���ӿ���?
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Puyo Puyo Tsu");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({0, 0}, {1280, 720});
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, APlayer>("Title");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void PuyoPuyoContentsCore::Tick()
{
}
