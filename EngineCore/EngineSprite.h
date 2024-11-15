#pragma once

#include <EngineBase/EngineResource.h>

// ���� :
class UEngineSprite : public UEngineResource
{
public:
	class USpriteData
	{
	public:
		// �� �̹����� ������
		UEngineWinImage* Image;
		// ���⼭���� Transform ũ�⸸ŭ
		FTransform Transform;
		// �߶� ���ڴ�.
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
			MSGASSERT("��������Ʈ�� �ε����� �ʰ��߽��ϴ�.");
		}
		return Data[_Index];
	}

protected:

private:
	std::vector<USpriteData> Data;
};

