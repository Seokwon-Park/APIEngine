#include "aepch.h"
#include "Actor.h"
#include "ImageManager.h"
 
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
	if (nullptr == Sprite)
	{
		MSGASSERT("NO Sprites");
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetEngineWindow();
	UEngineWinImage* BackBufferImage = UEngineAPICore::GetBackBuffer();

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image;
	CurData.Transform;
	CurData.Image->CopyToTransparent(BackBufferImage, Transform, CurData.Transform);
}

void AActor::SetSprite(std::string_view _Name, int _CurIndex)
{
	Sprite = UImageManager::GetInstance().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		return;
	}
}
