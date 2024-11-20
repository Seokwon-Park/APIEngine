#include "aepch.h"
#include "EngineKeyEvent.h"
#include <EnginePlatform/EngineInputSystem.h>

UEngineKeyEvent::UEngineKeyEvent()
{
}

UEngineKeyEvent::~UEngineKeyEvent()
{
}

void UEngineKeyEvent::EventCheck(KeyCode _Key)
{
	if (true == UEngineInputSystem::GetInstance().GetIsKeyDown(_Key))
	{
		for (size_t i = 0; i < DownEvents.size(); i++)
		{
			DownEvents[i]();
		}
	}
	else if (true == UEngineInputSystem::GetInstance().GetIsKeyPress(_Key))
	{
		for (size_t i = 0; i < PressEvents.size(); i++)
		{
			PressEvents[i]();
		}
	}

	if (true == UEngineInputSystem::GetInstance().GetIsKeyFree(_Key))
	{
		for (size_t i = 0; i < FreeEvents.size(); i++)
		{
			FreeEvents[i]();
		}
	}

	if (true == UEngineInputSystem::GetInstance().GetIsKeyUp(_Key))
	{
		for (size_t i = 0; i < UpEvents.size(); i++)
		{
			UpEvents[i]();
		}
	}
}
