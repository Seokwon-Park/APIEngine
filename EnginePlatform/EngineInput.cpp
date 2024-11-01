#include "aepch.h"
#include "EngineInput.h"

void UEngineInput::UEngineKey::EventCheck()
{
	if (true == IsDown)
	{
		for (size_t i = 0; i < DownEvents.size(); i++)
		{
			DownEvents[i]();
		}
	}
	else if (true == IsPress)
	{
		for (size_t i = 0; i < PressEvents.size(); i++)
		{
			PressEvents[i]();
		}
	}

	if (true == IsFree)
	{
		for (size_t i = 0; i < FreeEvents.size(); i++)
		{
			FreeEvents[i]();
		}
	}

	if (true == IsUp)
	{
		for (size_t i = 0; i < UpEvents.size(); i++)
		{
			UpEvents[i]();
		}
	}
}

void UEngineInput::UEngineKey::KeyCheck(float _DeltaTime)
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


void UEngineInput::BindAction(int _KeyIndex, KeyEvent _EventType, std::function<void()> _Function)
{
	if (false == Keys.contains(_KeyIndex))
	{
		MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
		return;
	}

	switch (_EventType)
	{
	case KeyEvent::Down:
		Keys[_KeyIndex].DownEvents.push_back(_Function);
		break;
	case KeyEvent::Press:
		Keys[_KeyIndex].PressEvents.push_back(_Function);
		break;
	case KeyEvent::Free:
		Keys[_KeyIndex].FreeEvents.push_back(_Function);
		break;
	case KeyEvent::Up:
		Keys[_KeyIndex].UpEvents.push_back(_Function);
		break;
	default:
		break;
	}
}

UEngineInput::UEngineInput()
{
	for (int i = 0; i < 255; i++)
	{
		Keys.insert(std::make_pair(i, UEngineKey(i)));
	}
}


UEngineInput::~UEngineInput()
{
}

void UEngineInput::KeyCheck(float _DeltaTime)
{
	for (auto& Itr : Keys)
	{
		UEngineKey& CurKey = Itr.second;
		CurKey.KeyCheck(_DeltaTime);
	}
}

void UEngineInput::EventCheck()
{
	for (auto& Itr : Keys)
	{
		UEngineKey& CurKey = Itr.second;
		CurKey.EventCheck();
	}
}

