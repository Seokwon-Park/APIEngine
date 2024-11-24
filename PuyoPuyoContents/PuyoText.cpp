#include "aepch.h"
#include "PuyoText.h"



APuyoText::APuyoText()
{
	ColorSprites.reserve(3);
	ColorSprites.push_back("PUYO_RY.CNS.BMP");
	ColorSprites.push_back("PUYO_BP.CNS.BMP");
	ColorSprites.push_back("PUYO_G_.CNS.BMP");
	ColorSprites.push_back("GrayText");
	TextSpriteRenderers.reserve(MAXLEN);
	for (int i = 0; i < MAXLEN; i++)
	{
		USpriteRendererComponent* Sr = CreateDefaultSubobject<USpriteRendererComponent>("TextRenderer" + std::to_string(i));
		Sr->SetSprite(ColorSprites[0], 36);
		Sr->SetComponentScale({ 16,32 });
		Sr->SetRemoveBackground(true);
		Sr->SetPivot(EPivotType::TopLeft);
		TextSpriteRenderers.push_back(Sr);
		TextSpriteRenderers[i]->SetComponentLocation({ i * 16,0 });

	}
	ChMap.resize(127, 0);
	for (int i = 0; i < 10; i++)
	{
		ChMap['0' + i] = i;
	}

	for (int i = 0; i < 26; i++)
	{
		ChMap['a' + i] = 10 + i;
		ChMap['A' + i] = 10 + i;
	}
	ChMap[' '] = 10 + 26;
	ChMap['*'] = 40;
	ChMap['-'] = 38;

}

APuyoText::~APuyoText()
{
}

void APuyoText::BeginPlay()
{
	Super::BeginPlay();


}

void APuyoText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APuyoText::SetupText(size_t _TextLength, EPuyoBoardColor _Color, ETextAlign _TextAlign)
{
	if (_TextLength > MAXLEN)
	{
		MSGASSERT("설정한 길이가 너무 큽니다. 최대 길이: " + std::to_string(MAXLEN));
		return;
	}
	TextLength = _TextLength;
	Color = static_cast<int>(_Color);
	TextAlign = _TextAlign;

	for (int i = 0; i < TextLength; i++)
	{
	}

	for (size_t i = 0; i < MAXLEN; i++)
	{
		TextSpriteRenderers[i]->SetSprite(ColorSprites[Color], ChMap[' ']);
		TextSpriteRenderers[i]->SetRemoveBackground(true);
	}

}

void APuyoText::SetText(std::string _TextValue)
{
	ClearText();
	if (TextAlign == ETextAlign::Left)
	{
		for (int i = 0; i < _TextValue.size(); i++)
		{
			TextSpriteRenderers[i]->SetSprite(ColorSprites[Color], ChMap[_TextValue[i]]);
		}
	}
	else
	{
		for (int i = 0; i < _TextValue.size(); i++)
		{
			TextSpriteRenderers[TextLength - 1 - i]->SetSprite(ColorSprites[Color], ChMap[_TextValue[_TextValue.size() - 1 - i]]);
		}
	}
}

void APuyoText::SetText(long long _Value)
{
	SetText(std::to_string(_Value));
}

void APuyoText::ClearText()
{
	for (size_t i = 0; i < MAXLEN; i++)
	{
		TextSpriteRenderers[i]->SetSprite(ColorSprites[Color], ChMap[' ']);
	}
}






