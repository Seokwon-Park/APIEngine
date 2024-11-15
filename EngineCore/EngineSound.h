#pragma once

#include "ThirdParty/FMOD/include/fmod.hpp"


// Ό³Έν :
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

	static void Load(std::string_view _Path);
	static void Load(std::string_view _Name, std::string_view _Path);
	static void Release();

protected:

private:
	static std::map<std::string, UEngineSound*> Sounds;

	bool ResLoad(std::string_view _Path);
};

