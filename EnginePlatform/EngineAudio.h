#pragma once
#include "ThirdParty/FMOD/include/fmod.hpp"

// Ό³Έν :
class UEngineAudio : public UObject
{
public:
	// constrcuter destructer
	~UEngineAudio();

	// delete Function
	UEngineAudio(const UEngineAudio& _Other) = delete;
	UEngineAudio(UEngineAudio&& _Other) noexcept = delete;
	UEngineAudio& operator=(const UEngineAudio& _Other) = delete;
	UEngineAudio& operator=(UEngineAudio&& _Other) noexcept = delete;

	inline static void Init()
	{
		if (Instance == nullptr)
		{
			Instance = new UEngineAudio();
		}
	}

	inline static UEngineAudio* GetInstance()
	{
		return Instance;
	}


	inline static FMOD::System* GetSystem()
	{
		return Instance->FMODSystem;
	}

	inline static void Release()
	{
		Instance->FMODSystem->close();
		Instance->FMODSystem->release();
		Instance->FMODSystem = nullptr;
		delete Instance;
	}
	static void AudioUpdate() { Instance->Update(); }

	static void StopAllSounds() { Instance->FMODChannelGroup->stop();}

protected:

private:
	UEngineAudio();
	void Update();

	static UEngineAudio* Instance;
	FMOD::System* FMODSystem = nullptr;
	FMOD::ChannelGroup* FMODChannelGroup = nullptr;
};

