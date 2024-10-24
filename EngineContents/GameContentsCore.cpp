#include "aepch.h"
#include "GameContentsCore.h"

UGameContentsCore::UGameContentsCore()
{
}

UGameContentsCore::~UGameContentsCore()
{
}

void UGameContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel("Intro");
	UEngineAPICore::GetCore()->CreateLevel("Play");
	UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void UGameContentsCore::Tick()
{
}
