#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 클래스 설명 :
class ANameText : public AActor
{
public:
	// Constrcuter Destructer
	ANameText();
	~ANameText();

	// Delete Function
	ANameText(const ANameText& _Other) = delete;
	ANameText(ANameText&& _Other) noexcept = delete;
	ANameText& operator=(const ANameText& _Other) = delete;
	ANameText& operator=(ANameText&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;

	//void SetupText(size_t _TextLength);
	void SetText(std::string _TextValue);
	void SetText(long long _Value);
	inline void Add(long long _Value) { Score += _Value; SetText(Score); }
	void ClearText();
protected:
	virtual void BeginPlay() override;
private:
	const int MAXLEN = 18;
	std::vector<int> ChMap;
	size_t TextLength;
	std::vector<USpriteRendererComponent*> TextSpriteRenderers;
	int Color = 0;
	bool RemoveZero;
	long long Score = 0;
};
