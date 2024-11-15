#include "aepch.h"
#include "EngineSound.h"
#include <EngineBase/EngineStringHelper.h>

std::map<std::string, UEngineSound*> UEngineSound::Sounds;

// ���带 �����ϱ����� �ڵ�
FMOD::System* SoundSystem = nullptr;

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

class SoundInit
{
public:
	SoundInit()
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MSGASSERT("FMOD �ý��� �̴ֿ� �����߽��ϴ�.");
			return;
		}

		// ���� ä�μ���
		// int maxchannels, ���ÿ� ����� ���� ����� �Ǵ°�?
		// FMOD_INITFLAGS flags, ���������� �ֳ��ε�
		// void* extradriverdata �������׿� ���� �����ͳ־��ٰ� �ֳ�.
		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MSGASSERT("FMOD �ý��� �̴ֿ� �����߽��ϴ�.");
			return;
		}
	}
};

SoundInit SoundInitObject;


// ������ ������ ���� ȣ��
void UEngineSound::Release()
{
	std::map<std::string, UEngineSound*>::iterator StartIter = Sounds.begin();
	std::map<std::string, UEngineSound*>::iterator EndIter = Sounds.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Sounds.clear();
}

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
}

void  UEngineSound::Load(std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);
	std::string FileName = EnginePath.GetPathName();

	UEngineSound::Load(FileName.data(), _Path);
}

void UEngineSound::Load(std::string_view _Name, std::string_view _Path)
{
	// �̳༮�� UTF-8�� ��θ� �ٲ��־� �Ѵ�.
	std::string UpperString = UEngineStringHelper::ToUpper(_Path);

	UEngineSound* NewSound = new UEngineSound();


	if (false == NewSound->ResLoad(_Path))
	{
		delete NewSound;
		MSGASSERT("���� �ε忡 �����߽��ϴ�" + UpperString);
		return;
	}
	;

	UEngineSound::Sounds.insert({ UpperString, NewSound });
	// Load(FileName, Path);
}


bool UEngineSound::ResLoad(std::string_view _Path)
{
	// FMOD�� ����ϴ� �κ�
	int a = 0;

	return true;
}