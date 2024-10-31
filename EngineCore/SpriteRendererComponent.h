#pragma once
#include "SceneComponent.h"

// Ό³Έν :
class USpriteRendererComponent : public USceneComponent
{
public:
	class UFrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameInterval;
		
		int CurIndex = 0;
		int ResultIndex = 0;
		float CurTime = 0;

	};

	// constrcuter destructer
	USpriteRendererComponent();
	~USpriteRendererComponent();

	// delete Function
	USpriteRendererComponent(const USpriteRendererComponent& _Other) = delete;
	USpriteRendererComponent(USpriteRendererComponent&& _Other) noexcept = delete;
	USpriteRendererComponent& operator=(const USpriteRendererComponent& _Other) = delete;
	USpriteRendererComponent& operator=(USpriteRendererComponent&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, int _CurIndex);
	void BeginPlay() override;
	void TickComponent(float _DeltaTime) override;
	void Render();
	inline int GetOrder(){return Order;}
	void SetOrder(int _Order);
	FVector2D SetSpriteScale(float _Ratio, int _Index);

	template <typename EnumType>
	inline void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}
protected:

private:
	int Order;
	class UEngineSprite* Sprite;
	int CurIndex;
};

class UAnimatorComponent
{
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _FrameIndex,
		std::vector<int> _FrameInterval, bool _IsLoop = true);
};
