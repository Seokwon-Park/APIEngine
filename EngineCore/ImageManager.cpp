#include "aepch.h"
#include "ImageManager.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineString.h>
#include <EngineBase/EngineDirectory.h>
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

void UImageManager::ClearSpriteData(std::string_view _SpriteName, UEngineSprite* _Sprite)
{
	std::string UpperSpriteName = UEngineString::ToUpper(_SpriteName);
	if (false != Sprites.contains(_SpriteName.data()))
	{
		MSGASSERT(std::string(_SpriteName) + "라는 이름의 스프라이트가 존재하지 않습니다.");
	}
	Sprites[UpperSpriteName]->ClearSpriteData();

}

void UImageManager::Load(std::string_view _Path)
{
	UEnginePath Path = UEnginePath(_Path);

	std::string FileName = Path.GetPathName();

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

	if (Images.contains(UpperName))
	{
		DBGPRINT("이미 같은 이름의 이미지가 존재합니다. " + std::string(_Path));
		return;
	}

	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->SetName(UpperName);
	NewImage->Load(WindowImage, _Path);

	Images.insert({ UpperName, NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();
	NewImage->SetName(UpperName);

	FTransform Transform;
	Transform.Location = { 0,0 };
	Transform.Scale = NewImage->GetImageSize();

	NewSprite->PushData(NewImage, Transform);

	Sprites.insert({ UpperName, NewSprite });
}

void UImageManager::LoadFolderToSprite(std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);

	std::string DirName = EnginePath.GetPathName();

	LoadFolderToSprite(DirName, _Path);
}

void UImageManager::LoadFolderToSprite(std::string_view _KeyName, std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);

	if (false == EnginePath.IsExists())
	{
		MSGASSERT("유효하지 않은 파일 경로 입니다." + std::string(_Path));
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (true == Sprites.contains(UpperName))
	{
		MSGASSERT("동일한 이름의 스프라이트가 이미 존재합니다." + UpperName);
		return;
	}

	UEngineSprite* NewSprite = new UEngineSprite();
	NewSprite->SetName(UpperName);
	Sprites.insert({ UpperName , NewSprite });

	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	UEngineDirectory Dir = _Path;
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].ToString();
		std::string UpperFileName = UEngineString::ToUpper(ImageFiles[i].GetPathName());

		UEngineWinImage* NewImage = FindImage(UpperFileName);
		if (nullptr == NewImage)
		{
			NewImage = new UEngineWinImage();
			NewImage->SetName(UpperFileName);
			NewImage->Load(WindowImage, FilePath);
		}
		Images.insert({ UpperFileName,  NewImage });

		FTransform Transform;
		Transform.Location = { 0, 0 };
		Transform.Scale = NewImage->GetImageSize();

		NewSprite->PushData(NewImage, Transform);
	}
}

void UImageManager::CuttingSprite(std::string_view _KeyName, FVector2D _CuttingSize)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("Sprite를 찾을 수 없습니다.");
		return;
	}

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("Sprite를 찾을 수 없습니다.");
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
			CuttingTransform.Location.X += _CuttingSize.X;
		}

		CuttingTransform.Location.X = 0.0f;
		CuttingTransform.Location.Y += _CuttingSize.Y;
	}
}

void UImageManager::CuttingSprite(std::string_view _KeyName, int _Rows, int _Cols)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("Sprite를 찾을 수 없습니다.");
		return;
	}

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("Sprite를 찾을 수 없습니다.");
		return;
	}

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWinImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();

	float Height = Image->GetImageSize().X / _Cols;
	float Width = Image->GetImageSize().Y / _Rows;

	FTransform CuttingTransform;

	CuttingTransform.Location = FVector2D::ZERO;
	CuttingTransform.Scale = FVector2D(Width, Height);

	for (size_t y = 0; y < _Rows; y++)
	{
		for (size_t x = 0; x < _Cols; x++)
		{
			Sprite->PushData(Image, CuttingTransform);
			CuttingTransform.Location.X += Width;
		}

		CuttingTransform.Location.X = 0.0f;
		CuttingTransform.Location.Y += Height;
	}
}

void UImageManager::CuttingSprite(std::string_view _NewSpriteName, std::string_view _ImageName, FVector2D _CuttingSize)
{
	std::string SpriteUpperName = UEngineString::ToUpper(_NewSpriteName);
	std::string ImageUpperName = UEngineString::ToUpper(_ImageName);

	if (false == Images.contains(ImageUpperName))
	{
		MSGASSERT("존재하지 않는 이미지를 기반으로 스프라이트를 자르려고 했습니다" + std::string(_ImageName));
		return;
	}

	UEngineSprite* Sprite = nullptr;

	if (false == Sprites.contains(SpriteUpperName))
	{
		Sprite = new UEngineSprite();
		Sprite->SetName(SpriteUpperName);
		Sprites.insert({ SpriteUpperName, Sprite });
	}
	else 
	{
		Sprite = Sprites[SpriteUpperName];
	}

	UEngineWinImage* Image = Images[ImageUpperName];

	Sprite->ClearSpriteData();

	int SpriteX = Image->GetImageSize().iX() / _CuttingSize.iX();
	int SpriteY = Image->GetImageSize().iY() / _CuttingSize.iY();

	FTransform CuttingTrans;

	CuttingTrans.Location = FVector2D::ZERO;
	CuttingTrans.Scale = _CuttingSize;

	for (size_t y = 0; y < SpriteY; ++y)
	{
		for (size_t x = 0; x < SpriteX; ++x)
		{
			Sprite->PushData(Image, CuttingTrans);
			CuttingTrans.Location.X += _CuttingSize.X;
		}

		CuttingTrans.Location.X = 0.0f;
		CuttingTrans.Location.Y += _CuttingSize.Y;
	}
}

void UImageManager::CuttingSpriteCustom(std::string_view _NewSpriteName, std::string_view _ImageName, FIntPoint _StartPos, FIntPoint _EndPos, FVector2D _CuttingSize)
{
	std::string SpriteUpperName = UEngineString::ToUpper(_NewSpriteName);
	std::string ImageUpperName = UEngineString::ToUpper(_ImageName);

	if (false == Images.contains(ImageUpperName))
	{
		MSGASSERT("존재하지 않는 이미지를 기반으로 스프라이트를 자르려고 했습니다" + std::string(_ImageName));
		return;
	}

	UEngineSprite* Sprite = nullptr; 

	if (false == Sprites.contains(SpriteUpperName))
	{
		Sprite = new UEngineSprite();
		Sprite->SetName(SpriteUpperName);
		Sprites.insert({ SpriteUpperName, Sprite });
	}
	else
	{
		Sprite = Sprites[SpriteUpperName];
	}

	UEngineWinImage* Image = Images[ImageUpperName];

	Sprite->ClearSpriteData();

	int Width = _EndPos.X - _StartPos.X;
	int Height = _EndPos.Y - _StartPos.Y;

	int SpriteX = Width / _CuttingSize.iX();
	int SpriteY = Height / _CuttingSize.iY();

	FTransform CuttingTrans;

	CuttingTrans.Location = FVector2D(_StartPos.X, _StartPos.Y);
	CuttingTrans.Scale = _CuttingSize;

	for (size_t y = 0; y < SpriteY; ++y)
	{
		for (size_t x = 0; x < SpriteX; ++x)
		{
			Sprite->PushData(Image, CuttingTrans);
			CuttingTrans.Location.X += _CuttingSize.X;
		}

		CuttingTrans.Location.X = 0.0f;
		CuttingTrans.Location.Y += _CuttingSize.Y;
	}
}

void UImageManager::InsertCustomSpriteData(std::string_view _SpriteName, std::string_view _ImageName, FTransform _CutData)
{
	std::string SpriteUpperName = UEngineString::ToUpper(_SpriteName);
	std::string ImageUpperName = UEngineString::ToUpper(_ImageName);

	if (false == Images.contains(ImageUpperName))
	{
		MSGASSERT("존재하지 않는 이미지를 기반으로 스프라이트를 자르려고 했습니다" + std::string(_ImageName));
		return;
	}

	UEngineWinImage* Image = Images[ImageUpperName];
	UEngineSprite* Sprite = nullptr;

	if (false == Sprites.contains(SpriteUpperName))
	{
		Sprite = new UEngineSprite();
		Sprite->SetName(SpriteUpperName);
		Sprites.insert({ SpriteUpperName, Sprite });
	}
	else {
		Sprite = Sprites[SpriteUpperName];
	}

	Sprite->SetName(SpriteUpperName);
	Image->SetName(ImageUpperName);

	Sprite->PushData(Image, _CutData);
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

UEngineWinImage* UImageManager::FindImage(std::string_view _KeyName)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (false == Images.contains(UpperName))
	{
		MSGASSERT("로드하지 않은 스프라이트를 사용하려고 했습니다" + std::string(_KeyName));
		return nullptr;
	}

	// 이걸로 
	return Images[UpperName];
}

void UImageManager::CreateColorImage(std::string_view _KeyName, UColor _Color)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	UEngineWinImage* WindowImage = UEngineAPICore::GetWindowBuffer();

	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->SetName(UpperName);
	NewImage->CreateBitmap32(WindowImage, {640,480}, _Color);

	Images.insert({ UpperName, NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();
	NewImage->SetName(UpperName);

	FTransform Transform;
	Transform.Location = { 0,0 };
	Transform.Scale = NewImage->GetImageSize();

	NewSprite->PushData(NewImage, Transform);

	Sprites.insert({ UpperName, NewSprite });
}


