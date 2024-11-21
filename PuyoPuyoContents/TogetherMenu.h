#pragma once
#include <EngineCore/InputComponent.h>
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class ATogetherMenu : public AActor
{
public:
	// constrcuter destructer
	ATogetherMenu();
	~ATogetherMenu();

	// delete Function
	ATogetherMenu(const ATogetherMenu& _Other) = delete;
	ATogetherMenu(ATogetherMenu&& _Other) noexcept = delete;
	ATogetherMenu& operator=(const ATogetherMenu& _Other) = delete;
	ATogetherMenu& operator=(ATogetherMenu&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	void StartPlay();
	void MoveMenu(int _Dir);
	int CurIndex = 0;

	USpriteRendererComponent* TextRenderer;
	USpriteRendererComponent* MapRenderer;
	UInputComponent* MenuInput;
};

