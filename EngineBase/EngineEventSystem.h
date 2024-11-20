#pragma once
#include "EngineDelegate.h"
#include "EngineEvent.h"

// Ό³Έν :
class UEngineEventSystem : public UObject
{
public:
	// constrcuter destructer
	
	~UEngineEventSystem();

	// delete Function
	UEngineEventSystem(const UEngineEventSystem& _Other) = delete;
	UEngineEventSystem(UEngineEventSystem&& _Other) noexcept = delete;
	UEngineEventSystem& operator=(const UEngineEventSystem& _Other) = delete;
	UEngineEventSystem& operator=(UEngineEventSystem&& _Other) noexcept = delete;

	inline static void AddEvent(float _Time, std::function<void()> _Callback)
	{
		UEngineEvent Event(_Time, _Callback);
		Events.push_back(Event);
	}

	inline static void AddEvent(float _Time, UEngineDelegate _Callback)
	{
		UEngineEvent Event(_Time, _Callback);
		Events.push_back(Event);
	}

	inline static void ClearEvents()
	{
		Events.clear();
	}

	inline static void UpdateEvents(float _DeltaTime)
	{
		std::list<UEngineEvent>::iterator CurItr = Events.begin();
		for (; CurItr != Events.end(); )
		{
			UEngineEvent& Event = *CurItr;
			Event.Elapsed += _DeltaTime;
			if (Event.IsTimePass())
			{
				Event.Delegate();
				CurItr = Events.erase(CurItr);
			}
			else
			{
				CurItr++;
			}
		}
	}
protected:

private:
	UEngineEventSystem();
	static std::list<UEngineEvent> Events;
};

