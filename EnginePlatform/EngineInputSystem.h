#pragma once
#include "KeyCode.h"
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>





// 설명 :
class UEngineInputSystem : public UObject
{
public:

	UEngineInputSystem();
	// constrcuter destructer
	~UEngineInputSystem();

	// delete Function
	UEngineInputSystem(const UEngineInputSystem& _Other) = delete;
	UEngineInputSystem(UEngineInputSystem&& _Other) noexcept = delete;
	UEngineInputSystem& operator=(const UEngineInputSystem& _Other) = delete;
	UEngineInputSystem& operator=(UEngineInputSystem&& _Other) noexcept = delete;

	static UEngineInputSystem& GetInstance()
	{
		static UEngineInputSystem Inst = UEngineInputSystem();
		return Inst;
	}

	void KeyCheck(float _DeltaTime);
	bool GetIsKeyDown(int _KeyIndex)
	{
		if (false == Keys.contains(_KeyIndex))
		{
			MSGASSERT("아직도 등록되지 않은 키가 존재합니다.");
			return false;
		}

		return Keys[_KeyIndex].IsDown;
	}

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

	UEngineKey() {}
		UEngineKey(int _Key)
			:Key(_Key) {}

		void KeyCheck(float _DeltaTime);
	};

	std::map<int, UEngineKey> Keys;
};

