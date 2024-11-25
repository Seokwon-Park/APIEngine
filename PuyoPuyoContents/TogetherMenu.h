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

	const std::vector<FVector2D> Locations= {
	{ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X, 224.0f },
	{ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X + 400.0f, 224.0f },
	{ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X + 800.0f, 224.0 },
	{ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X - 800, 224.0f },
	{ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X - 400, 224.0f }
	};
	USpriteRendererComponent* TextRenderer;

	USpriteRendererComponent* LArrowRenderer;
	USpriteRendererComponent* RArrowRenderer;
	UAnimatorComponent* LArrowAnim;
	UAnimatorComponent* RArrowAnim;

	std::vector<USpriteRendererComponent*> MapRenderer;
	UInputComponent* MenuInput;
};

