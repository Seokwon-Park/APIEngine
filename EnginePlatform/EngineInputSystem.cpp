#include "aepch.h"
#include "EngineInputSystem.h"



void UEngineInputSystem::UEngineKey::KeyCheck(float _DeltaTime)
{
	if (0 != GetAsyncKeyState(Key))
	{
		// ���ӿ������� �ð����
		// Ư�� float�� ����� ���� �� float ��� ��ŸŸ���� �����ָ�
		PressTime += _DeltaTime;
		// ������ �ȴ����ִ� ���¶��
		if (true == IsFree)
		{
			IsDown = true;
			IsPress = true;
			IsFree = false;
			IsUp = false;
		}
		// �� ���� �����ӿ� ������ ������ �����ִ� ���¸�
		else if (true == IsDown)
		{
			IsDown = false;
			IsPress = true;
			IsFree = false;
			IsUp = false;
		}
	}
	else
	{
		PressTime = 0.0f;
		if (true == IsPress)
		{
			IsDown = false;
			IsPress = false;
			IsFree = true;
			IsUp = true;
		}
		else if (true == IsUp)
		{
			IsDown = false;
			IsPress = false;
			IsFree = true;
			IsUp = false;
		}
	}
}




UEngineInputSystem::UEngineInputSystem()
{
	for (int i = 0; i < 255; i++)
	{
		Keys.insert(std::make_pair(i, UEngineKey(i)));
	}
}


UEngineInputSystem::~UEngineInputSystem()
{
}


void UEngineInputSystem::KeyCheck(float _DeltaTime)
{
	for (auto& Itr : Keys)
	{
		UEngineKey& CurKey = Itr.second;
		CurKey.KeyCheck(_DeltaTime);
	}
}



