#include "aepch.h"
#include "EngineSprite.h"

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}

void UEngineSprite::PushData(UEngineWinImage* _Image, const FTransform& _Trans)
{
	if (true == _Trans.Scale.isZero())
	{
		MSGASSERT("ũ�Ⱑ 0�� �̹����� ���� �� �����ϴ�.");
	}

	Data.push_back({ _Image, _Trans });
}
