#include "aepch.h"
#include "GameContentsCore.h"
#include "PlayGameMode.h"
#include "Player.h"

UGameContentsCore::UGameContentsCore()
{
}

UGameContentsCore::~UGameContentsCore()
{
}

void UGameContentsCore::BeginPlay()
{
	//UEngineAPICore::GetCore()->CreateLevel("Intro");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void UGameContentsCore::Tick()
{
}
