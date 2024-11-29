#pragma once
#include "ThirdParty/FMOD/include/fmod.hpp"
#include <EnginePlatform/EngineSound.h>

// 설명 :
class UAudioManager : public UObject
{
public:
	// constrcuter destructer
	~UAudioManager();

	// delete Function
	UAudioManager(const UAudioManager& _Other) = delete;
	UAudioManager(UAudioManager&& _Other) noexcept = delete;
	UAudioManager& operator=(const UAudioManager& _Other) = delete;
	UAudioManager& operator=(UAudioManager&& _Other) noexcept = delete;

	static UAudioManager& GetInstance()
	{
		static UAudioManager Instance;
		return Instance;
	}

	inline static void ChangeBGM(std::string_view _KeyName)
	{
		StopBGM();
		SetBGM(_KeyName);
		PlayBGM();
	}

	inline static void SetBGM(std::string_view _KeyName)
	{
		GetInstance().BGM = GetInstance().FindSound(_KeyName);
	}

	inline static void SetNoBGM()
	{
		GetInstance().BGM = nullptr;
	}

	inline static void PlayBGM()
	{
		if (GetInstance().BGM != nullptr)
		{
			GetInstance().BGM->Play();
		}
	}

	inline static void StopBGM()
	{
		if (GetInstance().BGM != nullptr)
		{
			GetInstance().BGM->Stop();
		}
	}

	static void SetBGMVolume(float _Value)
	{
		GetInstance().BGM->SetVolume(_Value);
	}

	static void SoundPlay(std::string_view _KeyName)
	{
		GetInstance().FindSound(_KeyName)->Play();
	}

	static void StopAllSounds()
	{
		UEngineAudio::GetInstance()->StopAllSounds();
	}

	void Load(std::string_view _Path);
	void Load(std::string_view _KeyName, std::string_view _Path);
	void ReleaseSounds();

	UEngineSound* FindSound(std::string_view _KeyName);
protected:

private:
	UAudioManager();
	// API에 대한 정보는 몰라야 하는거 같음
	// FMOD::System* FMODSystem = nullptr;
	std::map<std::string, UEngineSound*> Sounds;
	UEngineSound* BGM;
}; 

