#include "aepch.h"
#include "SoundManager.h"
#include <EngineBase/EngineStringHelper.h>

USoundManager::USoundManager()
{
}

USoundManager::~USoundManager()
{

}


void USoundManager::Load(std::string_view _Path)
{
	UEnginePath Path = UEnginePath(_Path);
	std::string FileName = Path.GetPathName();
	Load(FileName, _Path);
}

void USoundManager::Load(std::string_view _KeyName, std::string_view _Path)
{
	UEnginePath Path = UEnginePath(_Path);

	if (true == Path.IsDirectory())
	{
		MSGASSERT("������ �ε��� �� �����ϴ�." + std::string(_Path));
		return;
	}

	if (false == Path.IsExists())
	{
		MSGASSERT("������ �������� �ʽ��ϴ�." + std::string(_Path));
		return;
	}

	std::string UpperName = UEngineStringHelper::ToUpper(_KeyName);

	if (Sounds.contains(UpperName))
	{
		DBGPRINT("�̹� ���� �̸��� ���尡 �����մϴ�. " + std::string(_Path));
		return;
	}

	UEngineSound* NewSound = new UEngineSound();
	NewSound->SetName(UpperName);
	NewSound->Load(_Path);

	Sounds.insert({ UpperName, NewSound });
}

void USoundManager::ReleaseSounds()
{
	for (auto& Sound : Sounds)
	{
		UEngineSound* CurSound = Sound.second;
		if (nullptr != CurSound)
		{
			delete CurSound;
			CurSound = nullptr;
		}
	}
}

UEngineSound* USoundManager::FindSound(std::string_view _KeyName)
{
	std::string UpperName = UEngineStringHelper::ToUpper(_KeyName);

	if (false == Sounds.contains(UpperName))
	{
		MSGASSERT("�ε����� ���� ���带 ����Ϸ��� �߽��ϴ�" + std::string(_KeyName));
		return nullptr;
	}

	// �̰ɷ� 
	return Sounds[UpperName];
}
