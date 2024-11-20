#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// ���� : ��Ⱑ �߻����� �� �����Ǵ� ��� �ؽ�Ʈ
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

