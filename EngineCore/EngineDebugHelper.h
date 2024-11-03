#pragma once
#include "EngineAPICore.h"

// 설명 :
class UEngineDebugHelper
{
public:


	// constrcuter destructer
	~UEngineDebugHelper() {};

	// delete Function
	UEngineDebugHelper(const UEngineDebugHelper& _Other) = delete;
	UEngineDebugHelper(UEngineDebugHelper&& _Other) noexcept = delete;
	UEngineDebugHelper& operator=(const UEngineDebugHelper& _Other) = delete;
	UEngineDebugHelper& operator=(UEngineDebugHelper&& _Other) noexcept = delete;

	//디버그 텍스트 표시여부
	inline void SetIsDebug(bool _Use) { Instance.UseDebugHelper = _Use; }
	static void PushString(std::string_view _Text);
	static void PushString(std::string_view _Text, FVector2D _Pos);
	static void PrintEngineDebugText();
	static void CheckFPSOption();
	//FPS 표시여부
	inline static void SetShowFPS(bool _ShowFPS){Instance.ShowFPS = true;}
protected:

private:
	UEngineDebugHelper() : ShowFPS(false), UseDebugHelper(true),
		DebugOptionPos(FVector2D::ZERO), DebugTextPos(FVector2D::ZERO) {};
	class DebugTextInfo
	{
	public:
		std::string Text;
		FVector2D Pos;
	};

	inline static UEngineDebugHelper& GetInstance()
	{
		return Instance;
	}

	static UEngineDebugHelper Instance;
	//옵션을 설정할 수 있게 하고 얘를 먼저 출력하자.
	bool ShowFPS;
	bool UseDebugHelper;
	FVector2D DebugOptionPos;
	FVector2D DebugTextPos;
	std::queue<DebugTextInfo> DebugOptions;
	std::vector<DebugTextInfo> DebugTexts;

};

