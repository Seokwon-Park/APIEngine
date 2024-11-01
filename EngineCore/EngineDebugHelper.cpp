#include "aepch.h"
#include "EngineDebugHelper.h"

#include <EnginePlatform/EngineWinDebug.h>

void UEngineDebugHelper::PushString(std::string_view _Text)
{
	GetInstance().DebugTexts.push_back({ _Text.data(), GetInstance().EngineTextPos });
	GetInstance().EngineTextPos.Y += 20;
}

void UEngineDebugHelper::PushString(std::string_view _Text, FVector2D _Pos)
{
	GetInstance().DebugTexts.push_back({_Text.data(), _Pos});
}

void UEngineDebugHelper::PrintEngineDebugText()
{
	UEngineWinImage* BackBuffer = UEngineAPICore::GetBackBuffer();
	int PosOffset = 0;
	if (true == GetInstance().ShowFPS)
	{
		GetInstance().PushString("FPS : "+std::to_string(1.0 / UEngineAPICore::GetCore()->GetDeltaTime()));
	}

	for (size_t i = 0; i < GetInstance().DebugTexts.size(); i++)
	{
		DebugTextInfo& Debug = GetInstance().DebugTexts[i];
		UEngineDebug::WinAPIOutputString(BackBuffer, Debug.Text, Debug.Pos);
	}

	GetInstance().EngineTextPos = FVector2D::ZERO;
	GetInstance().DebugTexts.clear();
}

void UEngineDebugHelper::SetShowFPS(bool _ShowFPS)
{
	GetInstance().ShowFPS = true;
}
