#include "aepch.h"
#include "EngineInputSystem.h"



void UEngineInputSystem::UEngineKey::KeyCheck(float _DeltaTime)
{
	if (0 != GetAsyncKeyState(Key))
	{
		// 게임엔진에서 시간재기
		// 특정 float을 만들어 놓고 그 float 계속 델타타임을 더해주면
		PressTime += _DeltaTime;
		// 이전에 안눌려있는 상태라면
		if (true == IsFree)
		{
			IsDown = true;
			IsPress = true;
			IsFree = false;
			IsUp = false;
		}
		// 그 다음 프레임에 왔을때 여전히 눌려있는 상태면
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



