#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AOptionsMenu : public AActor
{
public:
	// constrcuter destructer
	AOptionsMenu();
	~AOptionsMenu();

	// delete Function
	AOptionsMenu(const AOptionsMenu& _Other) = delete;
	AOptionsMenu(AOptionsMenu&& _Other) noexcept = delete;
	AOptionsMenu& operator=(const AOptionsMenu& _Other) = delete;
	AOptionsMenu& operator=(AOptionsMenu&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* OptMenuTitle;
	std::vector<USpriteRendererComponent*> OptMenuSr;

};

