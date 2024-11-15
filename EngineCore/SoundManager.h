#pragma once
#include "ThirdParty/FMOD/include/fmod.hpp"
#include <EnginePlatform/EngineSound.h>

// 설명 :
class USoundManager : public UObject
{
public:
	// constrcuter destructer
	~USoundManager();

	// delete Function
	USoundManager(const USoundManager& _Other) = delete;
	USoundManager(USoundManager&& _Other) noexcept = delete;
	USoundManager& operator=(const USoundManager& _Other) = delete;
	USoundManager& operator=(USoundManager&& _Other) noexcept = delete;

	static USoundManager& GetInstance()
	{
		static USoundManager Instance;
		return Instance;
	}

	void Load(std::string_view _Path);
	void Load(std::string_view _KeyName, std::string_view _Path);
	void ReleaseSounds();

	UEngineSound* FindSound(std::string_view _KeyName);
protected:

private:
	USoundManager();
	// API에 대한 정보는 몰라야 하는거 같음
	// FMOD::System* FMODSystem = nullptr;
	std::map<std::string, UEngineSound*> Sounds;

}; 

