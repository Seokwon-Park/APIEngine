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
		Sr->SetOrder(ERenderLayer::Text);
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
	ChMap['.'] = 39;

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

	Timer += _DeltaTime;
	if (IsWave == true)
	{
		for (int i = 0; i < TextLength; ++i) {
			TextSpriteRenderers[i]->SetSprite(ColorSprites[(i+TextTick) % 2], TextSpriteRenderers[i]->GetCurIndex());
			TextSpriteRenderers[i]->SetRemoveBackground(true);
			float BaseY = TextSpriteRenderers[i]->GetComponentLocation().Y;
			float y = 15.0f * std::sin(10.0f * Timer + i * 1.5f);
			TextSpriteRenderers[i]->SetComponentLocation({ TextSpriteRenderers[i]->GetComponentLocation().X, y });
		}
		TextTick += 1;
	}
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
	else if (TextAlign == ETextAlign::Right)
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

void APuyoText::SwitchColor(EPuyoBoardColor _Color1, EPuyoBoardColor _Color2, std::string _Text)
{
	int Color1 = static_cast<int>(_Color1);
	int Color2 = static_cast<int>(_Color2);
	if (Color == Color1)
	{
		SetupText(TextLength, _Color2, TextAlign);
	}
	else
	{
		SetupText(TextLength, _Color1, TextAlign);

	}
	SetText(_Text);
}







