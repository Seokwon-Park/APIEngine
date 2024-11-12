#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class APuyoChainText : public AActor
{
public:
	// constrcuter destructer
	APuyoChainText();
	~APuyoChainText();

	// delete Function
	APuyoChainText(const APuyoChainText& _Other) = delete;
	APuyoChainText(APuyoChainText&& _Other) noexcept = delete;
	APuyoChainText& operator=(const APuyoChainText& _Other) = delete;
	APuyoChainText& operator=(APuyoChainText&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

	void SetupChainText(int _Amount, EPuyoTextColor _Color);
protected:

	void BeginPlay()override;

private:
	float Timer = 0.5f;
	std::vector<std::string>ColorSprites;
	std::vector<std::string>ChainStringColor;
	std::vector<USpriteRendererComponent*> NumberText;
	USpriteRendererComponent* ChainText;

};

