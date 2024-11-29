#include "aepch.h"
#include "InputComponent.h"


UInputComponent::UInputComponent()
{
}

UInputComponent::~UInputComponent()
{
}

void UInputComponent::TickComponent(float _DeltaTime)
{
	Super::TickComponent(_DeltaTime);

	for (auto Event : KeyEvents)
	{
		Event.second.EventCheck(Event.first);
	}
}

void UInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInputComponent::BindAction(KeyCode _KeyCode, KeyEvent _EventType, std::function<void()> _Function)
{
	if (_KeyCode == EKey::AnyKey)
	{
		for (int i = 8; i < 255; i++)
		{
			KeyEvents[i].DownEvents.push_back(_Function);
		}
		return;
	}
	switch (_EventType)
	{
	case KeyEvent::Down:
		KeyEvents[_KeyCode].DownEvents.push_back(_Function);
		break;
	case KeyEvent::Press:
		KeyEvents[_KeyCode].PressEvents.push_back(_Function);
		break;
	case KeyEvent::Free:
		KeyEvents[_KeyCode].FreeEvents.push_back(_Function);
		break;
	case KeyEvent::Up:
		KeyEvents[_KeyCode].UpEvents.push_back(_Function);
		break;
	default:
		break;
	}
}
