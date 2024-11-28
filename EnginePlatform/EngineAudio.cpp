#include "aepch.h"
#include "EngineAudio.h"

UEngineAudio* UEngineAudio::Instance = nullptr;

UEngineAudio::UEngineAudio()
{
	FMOD_RESULT Result = FMOD::System_Create(&FMODSystem);
	if (Result != FMOD_RESULT::FMOD_OK)
	{
		MSGASSERT("FMOD 시스템 생성에 실패했습니다.");
		return;
	}
	// 32채널, 기본적인 초기화(Default), 추가로 지정할 사항(?)
	Result = FMODSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	if (Result != FMOD_RESULT::FMOD_OK)
	{
		MSGASSERT("FMOD 시스템 초기화에 실패했습니다.");
		return;
	}

	Result = FMODSystem->getMasterChannelGroup(&FMODChannelGroup);
	if (Result != FMOD_OK) {
		std::cerr << "FMOD: Failed to get master channel group. Error: " << Result << std::endl;
		return;
	}
}

UEngineAudio::~UEngineAudio()
{
	
}

void UEngineAudio::Update()
{
	if (nullptr == FMODSystem)
	{
		return;
	}

	if (FMOD_RESULT::FMOD_OK != FMODSystem->update())
	{
		MSGASSERT("FMOD 시스템 업데이트에 이상이 감지되었습니다.");
	}
}
