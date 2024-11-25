#include "aepch.h"
#include "NameText.h"

ANameText::ANameText()
{
	TextSpriteRenderers.reserve(MAXLEN);
	for (int i = 0; i < MAXLEN; i++)
	{
		USpriteRendererComponent* Sr = CreateDefaultSubobject<USpriteRendererComponent>("TextRenderer" + std::to_string(i));
		Sr->SetSprite("NameText", 36);
		Sr->SetComponentScale({ 16,16 });
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
}

ANameText::~ANameText()
{
}

void ANameText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ANameText::SetText(std::string _TextValue)
{
	ClearText();
	for (int i = 0; i < _TextValue.size(); i++)
	{
		TextSpriteRenderers[i]->SetSprite("NameText", ChMap[_TextValue[i]]);
	}
}

void ANameText::SetText(long long _Value)
{
	SetText(std::to_string(_Value));
}

void ANameText::ClearText()
{
	for (size_t i = 0; i < MAXLEN; i++)
	{
		TextSpriteRenderers[i]->SetSprite("NameText", ChMap[' ']);
	}
}

void ANameText::BeginPlay()
{
	Super::BeginPlay();
}

