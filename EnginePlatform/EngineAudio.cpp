#include "aepch.h"
#include "EngineAudio.h"

UEngineAudio* UEngineAudio::Instance = nullptr;

UEngineAudio::UEngineAudio()
{
	FMOD_RESULT Result = FMOD::System_Create(&FMODSystem);
	if (Result != FMOD_RESULT::FMOD_OK)
	{
		MSGASSERT("FMOD �ý��� ������ �����߽��ϴ�.");
		return;
	}
	// 32ä��, �⺻���� �ʱ�ȭ(Default), �߰��� ������ ����(?)
	Result = FMODSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	if (Result != FMOD_RESULT::FMOD_OK)
	{
		MSGASSERT("FMOD �ý��� �ʱ�ȭ�� �����߽��ϴ�.");
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
		MSGASSERT("FMOD �ý��� ������Ʈ�� �̻��� �����Ǿ����ϴ�.");
	}
}
