#pragma once
#include <EngineCore/SpriteRendererComponent.h>
#include <EngineCore/AnimatorComponent.h>


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

	void Tick(float _DeltaTime) override;
	void SetupPuyo(FVector2D _Location, EPuyoColor _Color);
	void PlayAnimation(std::string _Name);
	void SetSprite(int _Index);
	int GetSpriteIndex() const { return SpriteIndex; }
	inline EPuyoColor GetColor() const { return Color; }
	inline void AnimationEndTrigger() { IsAnimationEnd = true; }

	inline FIntPoint GetCurXY() const { return CurXY; };
	inline FIntPoint GetTargetXY() const { return TargetXY; };
	inline bool GetIsDropComplete() const { return IsDropComplete; };
	inline bool GetIsAnimationEnd() const { return IsAnimationEnd; };

	inline void SetCurXY(FIntPoint _XY) { CurXY = _XY; };
	inline void SetTargetXY(FIntPoint _XY) { TargetXY = _XY; };
	inline void SetIsDropComplete(bool _IsDropComplete) { IsDropComplete = _IsDropComplete; };
	inline void SetIsAnimationEnd(bool _IsAnimationEnd) { IsAnimationEnd = _IsAnimationEnd; };
	// int X, Y;
	// int TargetX, TargetY;
protected:
	void BeginPlay() override;
private:
	FIntPoint CurXY;
	FIntPoint TargetXY;
	USpriteRendererComponent* Sr;
	UAnimatorComponent* Animator;
	EPuyoColor Color;
	int ColorIndex;
	int SpriteIndex;
	bool IsDropComplete;
	bool IsAnimationEnd;
	std::vector<std::string> ColorSprites;
};

