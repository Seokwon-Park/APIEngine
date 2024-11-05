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
		MSGASSERT("������ �ε��� �� �����ϴ�." + std::string(_Path));
		return;
	}

	if (false == Path.IsExists())
	{
		MSGASSERT("������ �������� �ʽ��ϴ�." + std::string(_Path));
		return;
	}

	UEngineWinImage* WindowImage = UEngineAPICore::GetWindowBuffer();

	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (Images.contains(UpperName))
	{
		DBGPRINT("�̹� ���� �̸��� �̹����� �����մϴ�. " + std::string(_Path));
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
		MSGASSERT("��ȿ���� ���� ���� ��� �Դϴ�." + std::string(_Path));
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (true == Sprites.contains(UpperName))
	{
		MSGASSERT("������ �̸��� ��������Ʈ�� �̹� �����մϴ�." + UpperName);
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
		MSGASSERT("Sprite�� ã�� �� �����ϴ�.");
		return;
	}

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("Sprite�� ã�� �� �����ϴ�.");
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
		MSGASSERT("Sprite�� ã�� �� �����ϴ�.");
		return;
	}

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("Sprite�� ã�� �� �����ϴ�.");
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
		MSGASSERT("�ε����� ���� ��������Ʈ�� ����Ϸ��� �߽��ϴ�" + std::string(_KeyName));
		return nullptr;
	}

	// �̰ɷ� 
	return Images[UpperName];
}


