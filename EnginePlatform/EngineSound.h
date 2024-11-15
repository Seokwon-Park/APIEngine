#pragma once

#include "ThirdParty/FMOD/include/fmod.hpp"

class UEngineSound : public UEngineResource
{
public:
	// constrcuter destructer
	UEngineSound();
	~UEngineSound();

	// delete Function
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	// 동시재생 사운드기능을 제대로 이용하려면
	// FMOD도 system업데이트 해줘야 합니다.
	// 우리가 실제 돌려주는것과 같이.

	//static void Load(std::string_view _Path);
	//static void Load(std::string_view _Name, std::string_view _Path);
	//static USoundPlayer Play(std::string_view _Name);
	//static UEngineSound* Find(std::string_view _Name);
	//static void Release();

	//static void Update();
	void Load(std::string_view _Path, bool _IsLoop = true);
	void Play();
	void Stop();
	void SetVolume(float _Volume);
	inline void SetLoop(bool _Value) { FMODSound->setMode(_Value ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF); }
protected:

private:

	FMOD::Sound* FMODSound = nullptr;
	FMOD::Channel* FMODChannel = nullptr;
};
