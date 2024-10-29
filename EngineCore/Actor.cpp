#include "aepch.h"
#include "Actor.h"
#include <EngineCore/EngineAPICore.h>

AActor::AActor()
	:World(nullptr), Transform(FTransform())
{
}

AActor::~AActor()
{
}

void AActor::Render()
{
	//                  100 100  - 50 50 => 50 50
	FVector2D LeftTop = Transform.CenterLeftTop();
	//                  100 100  + 50 50 => 150 150
	FVector2D RightBot = Transform.CenterRightBottom();

	UEngineWindow& MainWindow = UEngineAPICore::GetEngineWindow();
	UEngineWinImage* BackBufferImage = UEngineAPICore::GetBackBuffer();
	HDC BackBufferDC = BackBufferImage->GetDC();

	Rectangle(BackBufferDC, LeftTop.iX(), LeftTop.iY(), RightBot.iX(), RightBot.iY());
}
