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

	void SetupChainText(int _Amount, EPuyoBoardColor _Color);
protected:

	void BeginPlay()override;

private:
	float FloatingTimer = 0.5f;
	std::vector<std::string>ColorSprites;
	std::vector<USpriteRendererComponent*> NumberText;
	USpriteRendererComponent* ChainText;

};

