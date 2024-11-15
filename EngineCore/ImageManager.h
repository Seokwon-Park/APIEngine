#pragma once
#include "EngineSprite.h"
#include <EnginePlatform/EngineWinImage.h>

// ���� :
class UImageManager : public UObject
{
public:
	// constrcuter destructer
	~UImageManager();

	// delete Function
	UImageManager(const UImageManager& _Other) = delete;
	UImageManager(UImageManager&& _Other) noexcept = delete;
	UImageManager& operator=(const UImageManager& _Other) = delete;
	UImageManager& operator=(UImageManager&& _Other) noexcept = delete;

	static UImageManager& GetInstance()
	{
		static UImageManager Instance;
		return Instance;
	}

	void ClearSpriteData(std::string_view _SpriteName, UEngineSprite* _Sprite);
	
	void Load(std::string_view _Path);
	void Load(std::string_view _KeyName, std::string_view _Path);

	// Ư�� ������ ��� �̹����� �ϳ��� ��������Ʈ�� ����ϴ�.
	void LoadFolderToSprite(std::string_view _Path);
	void LoadFolderToSprite(std::string_view _KeyName, std::string_view _Path);
	
	//Ư�� �̹����� _CuttingSize�� �ڸ���.
	void CuttingSprite(std::string_view _KeyName, FVector2D _CuttingSize);

	//Ư�� �̹����� _Rows�� _Cols������ŭ �ڸ���.
	void CuttingSprite(std::string_view _KeyName, int _Rows, int _Cols);

	//Ư�� �̹����� ������� �ϴ� ���ο� �̸��� ��������Ʈ�� �����Ѵ�.
	void CuttingSprite(std::string_view _NewSpriteName, std::string_view _ImageName, FVector2D _CuttingSize);

	//�̹��������� ������ �����ϰ� ������ ���� ������ _CuttingSize��ŭ ��������Ʈ�� �ڵ����� �ڸ���.
	void CuttingSpriteCustom(std::string_view _NewSpriteName, std::string_view _ImageName, FIntPoint _StartPos,
		FIntPoint _EndPos,FVector2D _CuttingSize);

	//Ư�� ��������Ʈ�� ���ο� ����� �������� �ڸ� ��������Ʈ�� 1�� �߰��Ѵ�.
	void InsertCustomSpriteData(std::string_view _SpriteName, std::string_view _ImageName, FTransform _CutData);

	bool IsLoadSprite(std::string_view _KeyName);

	UEngineSprite* FindSprite(std::string_view _KeyName);
	UEngineWinImage* FindImage(std::string_view _KeyName);

	//32��Ʈ���� �ܻ� �̹����� ����ϴ�.(���ĺ��� ����)
	void CreateColorImage(std::string_view _KeyName, UColor _Color = UColor(0,0,0,255));
protected:

private:
	UImageManager();

	std::map<std::string, UEngineWinImage*>Images;
	std::map<std::string, UEngineSprite*>Sprites;
};

