#pragma once

// Ό³Έν :
class APuyoAIController : public AActor
{
public:
	// constrcuter destructer
	APuyoAIController();
	~APuyoAIController();

	// delete Function
	APuyoAIController(const APuyoAIController& _Other) = delete;
	APuyoAIController(APuyoAIController&& _Other) noexcept = delete;
	APuyoAIController& operator=(const APuyoAIController& _Other) = delete;
	APuyoAIController& operator=(APuyoAIController&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	float ThinkDelay = 0.5f;
};

