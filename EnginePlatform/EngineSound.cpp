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
		MSGASSERT("파일로드에 실패함");
	}

	if (nullptr == FMODSound)
	{
		MSGASSERT("사운드 로딩에 실패했습니다" + std::string(_Path));
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
//	// 이녀석은 UTF-8로 경로를 바꿔줘야 할수 있다.
//	std::string UpperString = UEngineStringHelper::ToUpper(_Name);
//
//	UEngineSound* NewSound = new UEngineSound();
//
//
//	if (false == NewSound->ResLoad(_Path))
//	{
//		delete NewSound;
//		MSGASSERT("사운드 로드에 실패했습니다" + UpperString);
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
//		MSGASSERT("로드하지 않은 사운드를 재생하려고 했습니다" + UpperString);
//	}
//
//
//	// 그냥 단순히 재생하는게 아니라면 채널을 얻어와야 속략이나 피치 볼륨 믹싱 등등을 조절할수 있다.
//	FMOD::Channel* Ch = nullptr;
//
//	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Ch);
//
//	// 1번 재생
//	Ch->setLoopCount(0);
//
//	// 볼륨 1로
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
//	// 유니코드로 넣어도
//	// 멀티바이트로 넣어도 제대로 안될때가 있다.
//	// 그러면 UTF시리즈로 인코딩해서 넣어줘야할때가 있다.
//	// FMOD를 사용하는 부분
//	// 해봤더니 된다 UTF시리즈로 안해줘도 됐다.

//
//	return true;
//}