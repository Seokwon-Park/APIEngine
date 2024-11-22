#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOptionsItem : public AActor
{
public:
	// constrcuter destructer
	AOptionsItem();
	~AOptionsItem();

	// delete Function
	AOptionsItem(const AOptionsItem& _Other) = delete;
	AOptionsItem(AOptionsItem&& _Other) noexcept = delete;
	AOptionsItem& operator=(const AOptionsItem& _Other) = delete;
	AOptionsItem& operator=(AOptionsItem&& _Other) noexcept = delete;

	void SetupItem(std::string_view _SpriteName, int _Index);

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::string SpriteName;
	USpriteRendererComponent* OptItemRenderer;
	std::list<std::function<void()>> Actions;

	
};

