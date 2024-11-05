#pragma once
#include "KeyCode.h"
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>


enum class KeyEvent
{
	Down,
	Press,
	Free,
	Up,
};


// 설명 :
class UEngineInput
{
public:

	// constrcuter destructer
	~UEngineInput();

	// delete Function
	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;

	static UEngineInput& GetInstance()
	{
		static UEngineInput Inst = UEngineInput();
		return Inst;
	}

	void KeyCheck(float _DeltaTime);
	void EventCheck();

	bool GetIsKeyUp(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[_KeyIndex].IsUp;
	}

	bool GetIsKeyPress(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[_KeyIndex].IsPress;
	}

	float GetKeyPressTime(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[_KeyIndex].PressTime;
	}


	bool GetIsKeyFree(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[_KeyIndex].IsFree;
	}

	void BindAction(int _KeyIndex, KeyEvent _EventType, std::function<void()> _Function);
protected:

private:
	class UEngineKey
	{
	public:
		int Key = -1;
		bool IsDown = false;
		bool IsPress = false;
		bool IsUp = false;
		bool IsFree = true;

		float PressTime = 0.0f;

		std::vector<std::function<void()>> PressEvents;
		std::vector<std::function<void()>> DownEvents;
		std::vector<std::function<void()>> UpEvents;
		std::vector<std::function<void()>> FreeEvents;


		UEngineKey() {}
		UEngineKey(int _Key)
			:Key(_Key) {}

		void EventCheck();
		void KeyCheck(float _DeltaTime);
	};

	std::map<int, UEngineKey> Keys;

	UEngineInput();
};

