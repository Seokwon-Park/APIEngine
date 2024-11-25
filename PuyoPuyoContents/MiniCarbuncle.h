#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AMiniCarbuncle : public AActor
{
public:
	// constrcuter destructer
	AMiniCarbuncle();
	~AMiniCarbuncle();

	// delete Function
	AMiniCarbuncle(const AMiniCarbuncle& _Other) = delete;
	AMiniCarbuncle(AMiniCarbuncle&& _Other) noexcept = delete;
	AMiniCarbuncle& operator=(const AMiniCarbuncle& _Other) = delete;
	AMiniCarbuncle& operator=(AMiniCarbuncle&& _Other) noexcept = delete;

	void AddEvent(std::function<void()> _Func)
	{
		Event += _Func;
	}
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Anim;

	UEngineDelegate Event;
};

