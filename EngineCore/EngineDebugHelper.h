#pragma once
#include "EngineAPICore.h"

// Ό³Έν :
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

	static void PushString(std::string_view _Text);
	static void PushString(std::string_view _Text, FVector2D _Pos);
	static void PrintEngineDebugText();
	static void SetShowFPS(bool _ShowFPS);
protected:
	
private:
	UEngineDebugHelper() : ShowFPS(false), EngineTextPos(FVector2D::ZERO){};
	class DebugTextInfo
	{
	public:
		std::string Text;
		FVector2D Pos;
	};
	
	inline static UEngineDebugHelper& GetInstance()
	{
		static UEngineDebugHelper Instance;
		return Instance;
	}

	std::vector<DebugTextInfo> DebugTexts;
	FVector2D EngineTextPos;
	bool ShowFPS;

};

