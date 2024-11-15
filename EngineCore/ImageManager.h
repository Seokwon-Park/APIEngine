#pragma once
#include "EngineSprite.h"
#include <EnginePlatform/EngineWinImage.h>

// 설명 :
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

	// 특정 폴더의 모든 이미지를 하나의 스프라이트로 만듭니다.
	void LoadFolderToSprite(std::string_view _Path);
	void LoadFolderToSprite(std::string_view _KeyName, std::string_view _Path);
	
	//특정 이미지를 _CuttingSize로 자른다.
	void CuttingSprite(std::string_view _KeyName, FVector2D _CuttingSize);

	//특정 이미지를 _Rows와 _Cols갯수만큼 자른다.
	void CuttingSprite(std::string_view _KeyName, int _Rows, int _Cols);

	//특정 이미지를 기반으로 하는 새로운 이름의 스프라이트를 생성한다.
	void CuttingSprite(std::string_view _NewSpriteName, std::string_view _ImageName, FVector2D _CuttingSize);

	//이미지내에서 범위를 설정하고 설정한 범위 내에서 _CuttingSize만큼 스프라이트를 자동으로 자른다.
	void CuttingSpriteCustom(std::string_view _NewSpriteName, std::string_view _ImageName, FIntPoint _StartPos,
		FIntPoint _EndPos,FVector2D _CuttingSize);

	//특정 스프라이트에 새로운 사용자 지정으로 자른 스프라이트를 1장 추가한다.
	void InsertCustomSpriteData(std::string_view _SpriteName, std::string_view _ImageName, FTransform _CutData);

	bool IsLoadSprite(std::string_view _KeyName);

	UEngineSprite* FindSprite(std::string_view _KeyName);
	UEngineWinImage* FindImage(std::string_view _KeyName);

	//32비트맵의 단색 이미지를 만듭니다.(알파블렌딩 가능)
	void CreateColorImage(std::string_view _KeyName, UColor _Color = UColor(0,0,0,255));
protected:

private:
	UImageManager();

	std::map<std::string, UEngineWinImage*>Images;
	std::map<std::string, UEngineSprite*>Sprites;
};

