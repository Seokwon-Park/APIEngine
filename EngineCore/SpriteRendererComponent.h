#pragma once
#include "SceneComponent.h"
#include "AnimatorComponent.h"

// Ό³Έν :
class USpriteRendererComponent : public USceneComponent
{
public:


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
	void SetOrder(int _Order);
	FVector2D SetSpriteScale(float _Ratio, int _Index);

	inline int GetOrder()const { return Order; }
	inline std::string GetCurSpriteName()const { return Sprite->GetName(); }
	template <typename EnumType>
	inline void SetOrder(EnumType _Order) { SetOrder(static_cast<int>(_Order)); }
protected:

private:
	int Order;
	class UEngineSprite* Sprite;
	int CurIndex;
	UAnimatorComponent* AnimatorComponent;
};



