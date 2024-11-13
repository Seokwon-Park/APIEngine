#pragma once
#include "SceneComponent.h"
#include "AnimatorComponent.h"

enum class EPivotType
{
	TopLeft,
	TopCenter,
	TopRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	BottomLeft,
	BottomCenter,
	BottomRight
};


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

	void SetSprite(std::string_view _Name, int _CurIndex = 0);
	void BeginPlay() override;
	void TickComponent(float _DeltaTime) override;
	void Render();
	void SetOrder(int _Order);
	FVector2D SetSpriteScale(float _Ratio, int _Index);

	inline int GetOrder()const { return Order; }
	inline std::string GetCurSpriteName()const { return Sprite->GetName(); }
	template <typename EnumType>
	inline void SetOrder(EnumType _Order) { SetOrder(static_cast<int>(_Order)); }
	inline void SetRemoveBackground(bool _Value) { RemoveBackground = _Value; }
	inline void SetRemoveColor(FIntPoint _Coord) { RemoveColor = Sprite->GetSpriteData(CurIndex).Image->GetPixelColor(_Coord, { 0,0,0,0 }); }
	inline void SetAnimator(UAnimatorComponent* _Component) { AnimatorComponent = _Component; }
	void SetPivot(EPivotType _Type);
	inline void SetPivot(FVector2D _Pivot) { Pivot = _Pivot; }

	inline void SetAlphaChar(unsigned char _Value){Alpha = _Value;}
	//void SetAlphafloat(float _Value){
	//	_Value = UEngineMath::Clamp(_Value, 0.0f, 1.0f);
	//Alpha = static_cast<unsigned char>(_Value * 255.0f);
	//}
protected:

private:
	int Order;
	class UEngineSprite* Sprite;
	int CurIndex;
	UAnimatorComponent* AnimatorComponent;
	bool IsCameraEffected;
	bool RemoveBackground;
	UColor RemoveColor;
	FVector2D Pivot;

	unsigned char Alpha = 255;
};



