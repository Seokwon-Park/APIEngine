#pragma once

class UEngineKeyEvent
{
public:
	
	UEngineKeyEvent();
	~UEngineKeyEvent();

	void EventCheck(KeyCode _Key);

	std::vector<std::function<void()>> PressEvents;
	std::vector<std::function<void()>> DownEvents;
	std::vector<std::function<void()>> UpEvents;
	std::vector<std::function<void()>> FreeEvents;
private:

};


