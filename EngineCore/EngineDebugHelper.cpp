#include "aepch.h"
#include "EngineDebugHelper.h"

#include <EnginePlatform/EngineWinDebug.h>

UEngineDebugHelper UEngineDebugHelper::Instance;

void UEngineDebugHelper::PushString(std::string_view _Text)
{
	Instance.DebugTexts.push_back({ _Text.data(), Instance.DebugTextPos });
	Instance.DebugTextPos.Y += 20;
}

void UEngineDebugHelper::PushString(std::string_view _Text, FVector2D _Pos)
{
	Instance.DebugTexts.push_back({_Text.data(), _Pos});
}

void UEngineDebugHelper::PrintEngineDebugRender()
{
	if (false == Instance.UseDebugHelper)
	{
		return;
	}

	UEngineWinImage* BackBuffer = UEngineAPICore::GetBackBuffer();
	CheckFPSOption();

	while(false == Instance.DebugOptions.empty())
	{
		DebugTextInfo Debug = Instance.DebugOptions.front();
		Instance.DebugOptions.pop();
		UEngineDebug::WinAPIOutputString(BackBuffer, Debug.Text, Debug.Pos);
	}

	for (size_t i = 0; i < Instance.DebugTexts.size(); i++)
	{
		DebugTextInfo& Debug = Instance.DebugTexts[i];
		UEngineDebug::WinAPIOutputString(BackBuffer, Debug.Text, Debug.Pos+Instance.DebugOptionPos);
	}

	Instance.DebugTextPos = FVector2D::ZERO;
	Instance.DebugOptionPos = FVector2D::ZERO;
	Instance.DebugTexts.clear();

	//DebugPivot
	FTransform Transform;
	Transform.Scale = FVector2D(6, 6);

	for (size_t i = 0; i < Instance.DebugPoses.size(); i++)
	{

		EDebugPosType Type = Instance.DebugPoses[i].Type;

		Transform.Location = Instance.DebugPoses[i].Pos;
		FVector2D TopLeft = Transform.CenterLeftTop();
		FVector2D BottomRight = Transform.CenterRightBottom();
		switch (Type)
		{
		case EDebugPosType::Rect:
			Rectangle(BackBuffer->GetDC(), TopLeft.iX(), TopLeft.iY(), BottomRight.iX(), BottomRight.iY());
			break;
		case EDebugPosType::Circle:
			Ellipse(BackBuffer->GetDC(), TopLeft.iX(), TopLeft.iY(), BottomRight.iX(), BottomRight.iY());
			break;
		default:
			break;
		}
	}

	Instance.DebugPoses.clear();

}

void UEngineDebugHelper::CheckFPSOption()
{
	if (true == Instance.ShowFPS)
	{
		std::string FPSText = "FPS : " + std::to_string(1.0 / UEngineAPICore::GetCore()->GetDeltaTime());
		Instance.DebugOptions.push({ FPSText ,Instance.DebugOptionPos });
		Instance.DebugOptionPos.Y += 20;
	}
}

void UEngineDebugHelper::SetDebugPos(FVector2D _Pos, EDebugPosType _Type)
{
	Instance.DebugPoses.push_back({ _Pos, _Type });
}

void UEngineDebugHelper::PivotDebugSwitch()
{
	Instance.ShowAllActorPivot = !Instance.ShowAllActorPivot;
	if (Instance.ShowAllActorPivot)
	{
		UEngineAPICore::GetCurrentLevel()->PivotDebugOn();
	}
	else
	{
		UEngineAPICore::GetCurrentLevel()->PivotDebugOff();
	}
}


