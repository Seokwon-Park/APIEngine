#pragma once
#include <EngineCore/SpriteRendererComponent.h>
#include <EngineCore/AnimatorComponent.h>

enum EColor
{
	Red,
	Green,
	Blue,
	Yellow,
	Purple
};
// Ό³Έν :
class APuyo : public AActor
{
public:
	// constrcuter destructer
	APuyo();
	~APuyo();

	// delete Function
	APuyo(const APuyo& _Other) = delete;
	APuyo(APuyo&& _Other) noexcept = delete;
	APuyo& operator=(const APuyo& _Other) = delete;
	APuyo& operator=(APuyo&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SetupPuyo(FVector2D _Location, int _Color);
	void PlayAnimation(std::string _Name);
	void SetSprite(int _Index);
	inline int GetColor() const { return Color; }
	inline void AnimationEndTrigger() 
	{
		IsAnimationEnd = true; 
	}

	bool IsDropComplete;
	bool IsAnimationEnd;
	int SpriteIndex;
protected:

private:
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Animator;
	int Color;
	std::vector<std::string> ColorSprites;
};

