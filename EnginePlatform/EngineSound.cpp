#include "aepch.h"
#include "EngineSound.h"
#include <EngineBase/EngineStringHelper.h>

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
	if (nullptr != FMODSound)
	{
		FMODSound->release();
		FMODSound = nullptr;
	}
}
void UEngineSound::Load(std::string_view _Path, bool _IsLoop)
{
	FMOD_MODE LoopMode = _IsLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

	FMOD_RESULT Result = UEngineAudio::GetSystem()->createSound(_Path.data(), LoopMode, nullptr, &FMODSound);

	if (FMOD_RESULT::FMOD_OK != Result)
	{
		MSGASSERT("���Ϸε忡 ������");
	}

	if (nullptr == FMODSound)
	{
		MSGASSERT("���� �ε��� �����߽��ϴ�" + std::string(_Path));
	}
}
void UEngineSound::Play()
{
	UEngineAudio::GetSystem()->playSound(FMODSound, nullptr, false, &FMODChannel);
}
void UEngineSound::Stop()
{
	FMODChannel->stop();
}
void UEngineSound::SetVolume(float _Volume)
{
	FMODChannel->setVolume(_Volume);
}
//
//void UEngineSound::Load(std::string_view _Path)
//{
//	UEnginePath EnginePath = UEnginePath(_Path);
//	std::string FileName = EnginePath.GetPathName();
//
//	UEngineSound::Load(FileName.data(), _Path);
//}
//
//void UEngineSound::Load(std::string_view _Name, std::string_view _Path)
//{
//	// �̳༮�� UTF-8�� ��θ� �ٲ���� �Ҽ� �ִ�.
//	std::string UpperString = UEngineStringHelper::ToUpper(_Name);
//
//	UEngineSound* NewSound = new UEngineSound();
//
//
//	if (false == NewSound->ResLoad(_Path))
//	{
//		delete NewSound;
//		MSGASSERT("���� �ε忡 �����߽��ϴ�" + UpperString);
//		return;
//	}
//	;
//
//	UEngineSound::Sounds.insert({ UpperString, NewSound });
//	// Load(FileName, Path);
//}
//
//UEngineSound* UEngineSound::Find(std::string_view _Name)
//{
//	std::string UpperString = UEngineStringHelper::ToUpper(_Name);
//
//	if (false == Sounds.contains(UpperString))
//	{
//		return nullptr;
//	}
//
//	return Sounds[UpperString];
//}
//
//USoundPlayer UEngineSound::Play(std::string_view _Name)
//{
//	std::string UpperString = UEngineStringHelper::ToUpper(_Name);
//
//	UEngineSound* FindSound = Find(_Name);
//
//	if (nullptr == FindSound)
//	{
//		MSGASSERT("�ε����� ���� ���带 ����Ϸ��� �߽��ϴ�" + UpperString);
//	}
//
//
//	// �׳� �ܼ��� ����ϴ°� �ƴ϶�� ä���� ���;� �ӷ��̳� ��ġ ���� �ͽ� ����� �����Ҽ� �ִ�.
//	FMOD::Channel* Ch = nullptr;
//
//	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Ch);
//
//	// 1�� ���
//	Ch->setLoopCount(0);
//
//	// ���� 1��
//	Ch->setVolume(1.0f);
//
//
//	USoundPlayer NewPlayer;
//	NewPlayer.Control = Ch;
//	return NewPlayer;
//}
//
//
//bool UEngineSound::ResLoad(std::string_view _Path)
//{
//	// �����ڵ�� �־
//	// ��Ƽ����Ʈ�� �־ ����� �ȵɶ��� �ִ�.
//	// �׷��� UTF�ø���� ���ڵ��ؼ� �־�����Ҷ��� �ִ�.
//	// FMOD�� ����ϴ� �κ�
//	// �غô��� �ȴ� UTF�ø���� �����൵ �ƴ�.

//
//	return true;
//}