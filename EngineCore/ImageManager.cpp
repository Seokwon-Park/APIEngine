#include "aepch.h"
#include "ImageManager.h"
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>
#include "EngineAPICore.h"

UImageManager::UImageManager()
{
}

UImageManager::~UImageManager()
{
	for (auto& Image : Images)
	{
		UEngineWinImage* CurImage = Image.second;
		if (nullptr != CurImage)
		{
			delete CurImage;
			CurImage = nullptr;
		}
	}

	for (auto& Sprite : Sprites)
	{
		UEngineSprite* CurSprite = Sprite.second;
		if (nullptr != CurSprite)
		{
			delete CurSprite;
			CurSprite = nullptr;
		}
	}
}

void UImageManager::Load(std::string_view _Path)
{
	UEnginePath Path = UEnginePath(_Path);

	std::string FileName = Path.GetFileName();

	Load(FileName, _Path);
}

void UImageManager::Load(std::string_view _KeyName, std::string_view _Path)
{
	UEnginePath Path = UEnginePath(_Path);

	if (true == Path.IsDirectory())
	{
		MSGASSERT("폴더를 로드할 수 없습니다." + std::string(_Path));
		return;
	}

	if (false == Path.IsExists())
	{
		MSGASSERT("파일이 존재하지 않습니다." + std::string(_Path));
		return;
	}

	UEngineWinImage* WindowImage = UEngineAPICore::GetWindowBuffer();

	std::string UpperName = UEngineString::ToUpper(_KeyName);

	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->Load(WindowImage, _Path);

	Images.insert({ UpperName, NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();

	FTransform Transform;
	Transform.Location = { 0,0 };
	Transform.Scale = NewImage->GetImageSize();

	NewSprite->PushData(NewImage, Transform);
	
	Sprites.insert({ UpperName, NewSprite });
}

void UImageManager::CuttingSprite(std::string_view _KeyName, FVector2D _CuttingSize)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("");
		return;
	}

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("");
		return;
	}

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWinImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();

	int SpriteX = Image->GetImageSize().iX() / _CuttingSize.iX();
	int SpriteY = Image->GetImageSize().iY() / _CuttingSize.iY();

	FTransform CuttingTransform;

	CuttingTransform.Location = FVector2D::ZERO;
	CuttingTransform.Scale = _CuttingSize;

	for (size_t y = 0; y < SpriteY; y++)
	{
		for (size_t x = 0; x < SpriteX; x++)
		{
			Sprite->PushData(Image, CuttingTransform);
			CuttingTransform.Location.X = _CuttingSize.X * x;
		}

		CuttingTransform.Location.X = 0.0f;
		CuttingTransform.Location.Y = _CuttingSize.Y * y;
	}


}

bool UImageManager::IsLoadSprite(std::string_view _KeyName)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	return Sprites.contains(UpperName);
}

UEngineSprite* UImageManager::FindSprite(std::string_view _KeyName)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (false == Sprites.contains(UpperName))
	{
		return nullptr;
	}

	return Sprites[UpperName];
}


