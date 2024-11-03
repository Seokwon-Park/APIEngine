#pragma once
#include "EngineAPICore.h"

// ���� :
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

	//����� �ؽ�Ʈ ǥ�ÿ���
	inline void SetIsDebug(bool _Use) { Instance.UseDebugHelper = _Use; }
	static void PushString(std::string_view _Text);
	static void PushString(std::string_view _Text, FVector2D _Pos);
	static void PrintEngineDebugText();
	static void CheckFPSOption();
	//FPS ǥ�ÿ���
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
	//�ɼ��� ������ �� �ְ� �ϰ� �긦 ���� �������.
	bool ShowFPS;
	bool UseDebugHelper;
	FVector2D DebugOptionPos;
	FVector2D DebugTextPos;
	std::queue<DebugTextInfo> DebugOptions;
	std::vector<DebugTextInfo> DebugTexts;

};

