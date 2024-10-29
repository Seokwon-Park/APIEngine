#include "aepch.h"
#include "PuyoPuyoContentsCore.h"
#include "PlayGameMode.h"
#include "Player.h"

PuyoPuyoContentsCore::PuyoPuyoContentsCore()
{
}

PuyoPuyoContentsCore::~PuyoPuyoContentsCore()
{
}

void PuyoPuyoContentsCore::BeginPlay()
{
	// TODO: ��Ʈ��(�ε�?) ȭ��, ���θ޴�, �����÷���(��庰 �и�?), 
	// ���ӿ���? , ���ӿ���?
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
