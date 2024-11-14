#pragma once
#include "EngineAPICore.h"

// 설명 :
class UEngineDebugHelper
{
public:
	enum class EDebugPosType
	{
		Rect,
		Circle,
	};

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
	static void PrintEngineDebugRender();
	static void CheckFPSOption();
	static void SetDebugPos(FVector2D _Pos, EDebugPosType _Type);
	static void PivotDebugSwitch();

	//FPS 표시여부
	inline static void SetShowFPS(bool _Value){Instance.ShowFPS = _Value;}

	inline static UEngineDebugHelper& GetInstance()
	{
		return Instance;
	}
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

	class DebugPosInfo
	{
	public:
		FVector2D Pos;
		EDebugPosType Type;
	};



	static UEngineDebugHelper Instance;

	//옵션을 설정할 수 있게 하고 얘를 먼저 출력하자.
	bool ShowFPS;
	bool ShowAllActorPivot = false;
	bool UseDebugHelper;
	FVector2D DebugOptionPos;
	FVector2D DebugTextPos;
	std::queue<DebugTextInfo> DebugOptions;
	std::vector<DebugTextInfo> DebugTexts;
	std::vector<DebugPosInfo> DebugPoses;
};

