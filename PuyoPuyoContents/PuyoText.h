#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

enum class EPuyoTextColor
{
	Blue,
	Green,
	Red,
};

// Ό³Έν :
class APuyoText : public AActor
{
public:
	// constrcuter destructer
	APuyoText();
	~APuyoText();

	// delete Function
	APuyoText(const APuyoText& _Other) = delete;
	APuyoText(APuyoText&& _Other) noexcept = delete;
	APuyoText& operator=(const APuyoText& _Other) = delete;
	APuyoText& operator=(APuyoText&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

	void SetupText(size_t _TextLength, EPuyoTextColor _Color);
	void SetText(std::string _SpriteName);
	void SetText(long long _Value);
protected:
	virtual void BeginPlay() override;
private:
	const size_t MAXLEN = 18;
	std::vector<int> ChMap;
	size_t TextLength;
	std::vector<USpriteRendererComponent*> TextSpriteRenderers;
	std::vector<std::string> ColorSprites;
	int TextAlign;
	int Color = 0;
	bool RemoveZero;
	
};

