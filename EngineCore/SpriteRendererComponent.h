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


// 설명 :
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
	inline void SetRemoveBackground(bool _Value) { SetRemoveColor(FIntPoint::ZERO); RemoveBackground = _Value; }
	//주의: 해당 스프라이트 범위에서 아니라 스프라이트 이미지의 좌표에서 추출하는 것
	void SetRemoveColor(FIntPoint _Coord);
	inline void SetRemoveColor(UColor _Color) { RemoveColor = _Color; };
	inline void SetAnimator(UAnimatorComponent* _Component) { AnimatorComponent = _Component; }
	void SetPivot(EPivotType _Type);
	inline void SetPivot(FVector2D _Pivot) { Pivot = _Pivot; }
	void UpdatePivot();

	inline void SetAlpha(int _Value)
	{
		Alpha = _Value;
		_Value = std::clamp(_Value, 0, 255);
	}
	inline void SetAlphaRate(float _Value)
	{
		_Value = std::clamp(_Value, 0.0f, 1.0f);
		Alpha = static_cast<unsigned char>(_Value * 255);
	}
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
	FIntPoint RemoveCoord = FIntPoint::ZERO;
	EPivotType PivotType = EPivotType::MiddleCenter;
	FVector2D Pivot;

	int Alpha = 255;
};



