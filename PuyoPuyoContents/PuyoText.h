#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

enum class ETextAlign
{
	Left,
	//Center? 어케만들지 몰?루, 필요한지도 몰?루
	Right,
};
// 설명 :
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

	void SetupText(size_t _TextLength, EPuyoTextColor _Color, ETextAlign _TextAlign = ETextAlign::Left);
	void SetText(std::string _SpriteName);
	void SetText(long long _Value);
	inline void Add(long long _Value) { Score += _Value; SetText(Score); }
	void ClearText();
protected:
	virtual void BeginPlay() override;
private:
	const size_t MAXLEN = 18;
	std::vector<int> ChMap;
	size_t TextLength;
	std::vector<USpriteRendererComponent*> TextSpriteRenderers;
	std::vector<std::string> ColorSprites;
	ETextAlign TextAlign = ETextAlign::Left;
	int Color = 0;
	bool RemoveZero;
	long long Score = 0;
	
};

