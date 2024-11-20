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

	static void SoundPlay(std::string_view _KeyName)
	{
		GetInstance().FindSound(_KeyName)->Play();
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

}; 

