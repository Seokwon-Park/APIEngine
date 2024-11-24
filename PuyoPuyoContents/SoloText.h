#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 설명 : 적을 선택하세요를 표시하는 텍스트 액터
class ASoloText : public AActor
{
public:
	// constrcuter destructer
	ASoloText();
	~ASoloText();

	// delete Function
	ASoloText(const ASoloText& _Other) = delete;
	ASoloText(ASoloText&& _Other) noexcept = delete;
	ASoloText& operator=(const ASoloText& _Other) = delete;
	ASoloText& operator=(ASoloText&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::vector< USpriteRendererComponent*> Sr;
};

