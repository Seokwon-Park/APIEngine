#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

// ���� :
class ACarbuncleMenu : public AActor
{
public:
	// constrcuter destructer
	ACarbuncleMenu();
	~ACarbuncleMenu();

	// delete Function
	ACarbuncleMenu(const ACarbuncleMenu& _Other) = delete;
	ACarbuncleMenu(ACarbuncleMenu&& _Other) noexcept = delete;
	ACarbuncleMenu& operator=(const ACarbuncleMenu& _Other) = delete;
	ACarbuncleMenu& operator=(ACarbuncleMenu&& _Other) noexcept = delete;

	void Test();
	void SetInacitve();
	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay() override;
private:
	int MenuIndex = 0;

	USpriteRendererComponent* HeadRenderer;
	USpriteRendererComponent* UBodyRenderer;
	USpriteRendererComponent* DBodyRenderer;
	USpriteRendererComponent* LHandRenderer;
	USpriteRendererComponent* RHandRenderer;
	USpriteRendererComponent* LegRenderer;
	USpriteRendererComponent* LArrowRenderer;
	USpriteRendererComponent* RArrowRenderer;
	USpriteRendererComponent* JewelRenderer;
	UAnimatorComponent* LArrowAnimator;
	UAnimatorComponent* RArrowAnimator;
	UAnimatorComponent* JewelAnimator;

};

