#pragma once
#include <EngineCore/InputComponent.h>
#include <EngineCore/SpriteRendererComponent.h>

#include "VSMenuMap.h"

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

	float MoveAmount = 0;
	int Dir = 0;

	const std::vector<FVector2D> Locations =
	{
	{ 152.0f, 96.0f },
	{ 536.0f, 96.0f },
	{ 152.0f + 768.0f, 96.0f },
	{ 152.0f - 768.0f, 96.0f },
	{ 152.0f - 384.0f, 96.0f }
	};
	USpriteRendererComponent* TextRenderer;

	USpriteRendererComponent* LArrowRenderer;
	USpriteRendererComponent* RArrowRenderer;
	UAnimatorComponent* LArrowAnim;
	UAnimatorComponent* RArrowAnim;

	std::vector<AVSMenuMap*> MenuItems;
	UInputComponent* MenuInput;
};

