#include "aepch.h"
#include "PuyoChainText.h"

APuyoChainText::APuyoChainText()
{
	ColorSprites.reserve(2);
	ColorSprites.push_back("PUYO_RY.CNS.BMP");
	ColorSprites.push_back("PUYO_BP.CNS.BMP");

	NumberText.resize(2, nullptr);
	for (int i = 0; i < 2; i++)
	{
		NumberText[i] = CreateDefaultSubobject<USpriteRendererComponent>("ChainAmount" + std::to_string(i));
		NumberText[i]->SetSprite(ColorSprites[0], 0);
		NumberText[i]->SetComponentScale({ 16,32 });
		NumberText[i]->SetRemoveBackground(true);
		NumberText[i]->SetPivot(EPivotType::TopLeft);
		NumberText[i]->SetActive(false);
	}
	ChainText = CreateDefaultSubobject<USpriteRendererComponent>("ChainString");
	ChainText->SetSprite("ChainString", 0);
	ChainText->SetComponentScale({ 48,16 });
	ChainText->SetRemoveBackground(true);
	ChainText->SetPivot(EPivotType::TopLeft);

}

APuyoChainText::~APuyoChainText()
{
}

void APuyoChainText::BeginPlay()
{
	Super::BeginPlay();
}

void APuyoChainText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::UP * 0.1f);
	FloatingTimer -= _DeltaTime;
	if (FloatingTimer < 0.0f)
		this->Destroy();
}

void APuyoChainText::SetupChainText(int _Amount, EPuyoBoardColor _Color)
{
	std::string NumText = std::to_string(_Amount);
	int Size = static_cast<int>(NumText.size());
	int ColorIndex = static_cast<int>(_Color);
	for (int i = 0; i < NumText.size(); i++)
	{
		NumberText[i]->SetSprite(ColorSprites[ColorIndex], NumText[i]-'0');
		NumberText[i]->SetComponentScale({ 16,32 });
		NumberText[i]->SetComponentLocation({ i * 16, 0 });
		NumberText[i]->SetRemoveBackground(true);
		NumberText[i]->SetPivot(EPivotType::TopLeft);
		NumberText[i]->SetActive(true);
	}
	ChainText->SetSprite("ChainString", ColorIndex);
	ChainText->SetRemoveBackground(true);
	ChainText->SetComponentLocation({ Size * 16, 16});
}
