#include "aepch.h"
#include "PuyoText.h"



APuyoText::APuyoText()
{
	ColorSprites.reserve(3);
	ColorSprites.push_back("PUYO_BP.CNS.BMP");
	ColorSprites.push_back("PUYO_G_.CNS.BMP");
	ColorSprites.push_back("PUYO_RY.CNS.BMP");
	TextSpriteRenderers.reserve(MAXLEN);
	for (size_t i = 0; i < MAXLEN; i++)
	{
		USpriteRendererComponent* Sr = CreateDefaultSubobject<USpriteRendererComponent>("TextRenderer" + std::to_string(i));
		Sr->SetSprite(ColorSprites[0], 0);
		Sr->SetComponentScale({ 16,32 });
		Sr->SetComponentLocation(FVector2D(16, 0) * static_cast<float>(i));
		Sr->SetRemoveBackground(true);
		Sr->SetPivot(PivotType::TopLeft);
		Sr->SetActive(false);
		TextSpriteRenderers.push_back(Sr);
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

void APuyoText::SetupText(size_t _TextLength, EPuyoTextColor _Color)
{
	if (_TextLength > MAXLEN)
	{
		MSGASSERT("설정한 길이가 너무 큽니다. 최대 길이: " + std::to_string(MAXLEN));
		return;
	}
	TextLength = _TextLength;
	Color = static_cast<int>(_Color);

	for (size_t i = 0; i < MAXLEN; i++)
	{
		TextSpriteRenderers[i]->SetSprite(ColorSprites[Color], 0);
	}
}

void APuyoText::SetText(std::string _TextValue)
{
	for (int i = 0; i < _TextValue.size(); i++)
	{
		TextSpriteRenderers[i]->SetSprite(ColorSprites[Color], ChMap[_TextValue[i]]);
		TextSpriteRenderers[i]->SetActive(true);
	}
}

void APuyoText::SetText(long long _Value)
{
	SetText(std::to_string(_Value));
}






