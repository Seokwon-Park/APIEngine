#pragma once
#include "EngineDelegate.h"

// Ό³Έν :
class UEngineEvent :public UObject
{
public:
	UEngineEvent() {};
	UEngineEvent(float _Delay, UEngineDelegate _Delegate) 
	{
		Duration = _Delay;
		Delegate = _Delegate;
	};
	bool IsTimePass() { return Elapsed >= Duration; }
	
	float Elapsed = 0.0f;
	UEngineDelegate Delegate;
private:
	float Duration = 0.0f;
};

