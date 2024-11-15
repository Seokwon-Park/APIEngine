#pragma once
#include "EngineAPICore.h"

// ���� :
class EngineDebugHelper
{
public:
	enum class EDebugPosType
	{
		Rect,
		Circle,
	};

	// constrcuter destructer
	~EngineDebugHelper() {};

	// delete Function
	EngineDebugHelper(const EngineDebugHelper& _Other) = delete;
	EngineDebugHelper(EngineDebugHelper&& _Other) noexcept = delete;
	EngineDebugHelper& operator=(const EngineDebugHelper& _Other) = delete;
	EngineDebugHelper& operator=(EngineDebugHelper&& _Other) noexcept = delete;

	//����� �ؽ�Ʈ ǥ�ÿ���
	inline void SetIsDebug(bool _Use) { Instance.UseDebugHelper = _Use; }
	static void PushString(std::string_view _Text);
	static void PushString(std::string_view _Text, FVector2D _Pos);
	static void PrintEngineDebugRender();
	static void CheckFPSOption();
	static void SetDebugPos(FVector2D _Pos, EDebugPosType _Type);
	static void PivotDebugSwitch();

	//FPS ǥ�ÿ���
	inline static void SetShowFPS(bool _Value){Instance.ShowFPS = _Value;}

	inline static EngineDebugHelper& GetInstance()
	{
		return Instance;
	}
protected:

private:
	EngineDebugHelper() : ShowFPS(false), UseDebugHelper(true),
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



	static EngineDebugHelper Instance;

	//�ɼ��� ������ �� �ְ� �ϰ� �긦 ���� �������.
	bool ShowFPS;
	bool ShowAllActorPivot = false;
	bool UseDebugHelper;
	FVector2D DebugOptionPos;
	FVector2D DebugTextPos;
	std::queue<DebugTextInfo> DebugOptions;
	std::vector<DebugTextInfo> DebugTexts;
	std::vector<DebugPosInfo> DebugPoses;
};

