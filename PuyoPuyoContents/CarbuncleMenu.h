#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
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
	void SetMenuInactive();
	void SetMenuActive();
	void PlayCloseAnimation();
	void SetupCarbuncleMenu(int _MenuIndex);
	void MoveTo(float _Amount,int _Dir); 
	inline bool GetIsMoving() { return IsMoving; }
	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay() override;
private:
	const int MaxMenuSize = 5;
	bool IsMoving = false;
	bool IsPlaying = false;
	float MoveAmount = 0;
	int Dir = 0;
	int MenuIndex = 0;
	float Timer = 0.0f;

	FVector2D TargetLocation = FVector2D::ZERO;
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

