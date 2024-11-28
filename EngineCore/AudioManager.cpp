#include "aepch.h"
#include "AudioManager.h"
#include <EngineBase/EngineStringHelper.h>

UAudioManager::UAudioManager()
{
}

UAudioManager::~UAudioManager()
{

}


void UAudioManager::Load(std::string_view _Path)
{
	UEnginePath Path = UEnginePath(_Path);
	std::string FileName = Path.GetPathName();
	Load(FileName, _Path);
}

void UAudioManager::Load(std::string_view _KeyName, std::string_view _Path)
{
	UEnginePath Path = UEnginePath(_Path);

	if (true == Path.IsDirectory())
	{
		MSGASSERT("폴더를 로드할 수 없습니다." + std::string(_Path));
		return;
	}

	if (false == Path.IsExists())
	{
		MSGASSERT("파일이 존재하지 않습니다." + std::string(_Path));
		return;
	}

	std::string UpperName = UEngineStringHelper::ToUpper(_KeyName);

	if (Sounds.contains(UpperName))
	{
		DBGPRINT("이미 같은 이름의 사운드가 존재합니다. " + std::string(_Path));
		return;
	}

	UEngineSound* NewSound = new UEngineSound();
	NewSound->SetName(UpperName);
	NewSound->Load(_Path);

	Sounds.insert({ UpperName, NewSound });
}

void UAudioManager::ReleaseSounds()
{
	UEngineAudio::GetInstance()->StopAllSounds();
	for (auto& Sound : Sounds)
	{
		UEngineSound* CurSound = Sound.second;
		if (nullptr != CurSound)
		{
			delete CurSound;
			CurSound = nullptr;
		}
	}
	Sounds.clear();
}

UEngineSound* UAudioManager::FindSound(std::string_view _KeyName)
{
	std::string UpperName = UEngineStringHelper::ToUpper(_KeyName);

	if (false == Sounds.contains(UpperName))
	{
		MSGASSERT("로드하지 않은 사운드를 사용하려고 했습니다" + std::string(_KeyName));
		return nullptr;
	}

	// 이걸로 
	return Sounds[UpperName];
}
