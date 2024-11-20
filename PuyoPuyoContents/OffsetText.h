#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 설명 : 상쇄가 발생했을 때 스폰되는 상쇄 텍스트
class AOffsetText : public AActor
{
public:
	// constrcuter destructer
	AOffsetText();
	~AOffsetText();

	// delete Function
	AOffsetText(const AOffsetText& _Other) = delete;
	AOffsetText(AOffsetText&& _Other) noexcept = delete;
	AOffsetText& operator=(const AOffsetText& _Other) = delete;
	AOffsetText& operator=(AOffsetText&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
};

