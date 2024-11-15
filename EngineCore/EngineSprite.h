#pragma once

#include <EngineBase/EngineResource.h>

// 설명 :
class UEngineSprite : public UEngineResource
{
public:
	class USpriteData
	{
	public:
		// 이 이미지의 포인터
		UEngineWinImage* Image;
		// 여기서부터 Transform 크기만큼
		FTransform Transform;
		// 잘라서 쓰겠다.
	};

	// constrcuter destructer
	UEngineSprite();
	~UEngineSprite();

	// delete Function
	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	void PushData(UEngineWinImage* _Image, const FTransform& _Trans);

	inline void ClearSpriteData()
	{
		Data.clear();
	}
	inline USpriteData GetSpriteData(int _Index = 0)
	{
		if (_Index >= Data.size())
		{
			MSGASSERT("스프라이트의 인덱스를 초과했습니다.");
		}
		return Data[_Index];
	}

protected:

private:
	std::vector<USpriteData> Data;
};

