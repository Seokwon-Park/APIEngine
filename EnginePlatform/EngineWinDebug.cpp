#include "aepch.h"
#include "EngineWinDebug.h"

namespace UEngineDebug
{
	void WinAPIOutputString(UEngineWinImage* _Image,
		std::string_view _Text, FVector2D _Pos)
	{
		TextOutA(_Image->GetDC(), _Pos.iX(), _Pos.iY(), _Text.data(), _Text.size());
	}
}