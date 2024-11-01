#pragma once
#include "EngineSprite.h"
#include <EnginePlatform/EngineWinImage.h>

// Ό³Έν :
class UImageManager
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

	void Load(std::string_view _Path);
	void Load(std::string_view _KeyName, std::string_view _Path);
	void LoadFolder(std::string_view _Path);
	void LoadFolder(std::string_view _KeyName, std::string_view _Path);
	void CuttingSprite(std::string_view _KeyName, FVector2D _CuttingSize);
	void CuttingSprite(std::string_view _KeyName, int _Rows, int _Cols);
	bool IsLoadSprite(std::string_view _KeyName);
	UEngineSprite* FindSprite(std::string_view _KeyName);

protected:

private:
	UImageManager();

	std::map<std::string, UEngineWinImage*>Images;
	std::map<std::string, UEngineSprite*>Sprites;
};

