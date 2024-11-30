#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

enum class ETextAlign
{
	Left,
	Center,
	Right,
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

	void SetupText(size_t _TextLength, EPuyoBoardColor _Color, ETextAlign _TextAlign = ETextAlign::Left);
	void SetText(std::string _TextValue);
	void SetText(long long _Value);
	inline void AddScoreAndUpdate(long long _Value) { Score += _Value; SetText(Score); }
	inline void SetScoreAndUpdate(long long _Value) { Score = _Value; SetText(Score); }
	inline void SetScore(long long _Value) { Score = _Value; }
	void ClearText();
	void SwitchColor(EPuyoBoardColor _Color1, EPuyoBoardColor _Color2, std::string _Text);
	void SetWave() { IsWave = true; };
	inline long long GetScore() const { return Score; }
protected:
	virtual void BeginPlay() override;
	std::vector<int> ChMap;
	std::vector<USpriteRendererComponent*> TextSpriteRenderers;
	size_t TextLength;
	const int MAXLEN = 18;
	std::vector<std::string> ColorSprites;
	ETextAlign TextAlign = ETextAlign::Left;
	int Color = 0;
	int TextTick = 0;
	bool RemoveZero;
	bool IsWave = false;
	long long Score = 0;
	float Timer = 0.0f;
private:
	
};

