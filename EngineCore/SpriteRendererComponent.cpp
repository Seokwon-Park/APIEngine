#include "aepch.h"
#include "SpriteRendererComponent.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineAPICore.h>

USpriteRendererComponent::USpriteRendererComponent()
	:Order(0), Sprite(nullptr), CurIndex(0), AnimatorComponent(nullptr), IsCameraEffected(false),
	RemoveBackground(false), RemoveColor(UColor(255, 0, 255, 0)), Pivot(FVector2D::ZERO)
{
}

USpriteRendererComponent::~USpriteRendererComponent()
{
}

void USpriteRendererComponent::SetSprite(std::string_view _Name, int _CurIndex)
{
	Sprite = UImageManager::GetInstance().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("스프라이트가 설정되지 않았습니다.");
		return;
	}

	CurIndex = _CurIndex;
}

void USpriteRendererComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = GetOwner();
	ULevel* Level = Actor->GetWorld();
	/*for (UActorComponent* Component : Actor->GetComponents())
	{
		UAnimatorComponent* Animator = dynamic_cast<UAnimatorComponent*>(Component);
		if (nullptr != Animator)
		{
			AnimatorComponent = Animator;
			break;
		}
	}*/


	Level->PushRenderer(this);
}

void USpriteRendererComponent::TickComponent(float _DeltaTime)
{
	Super::TickComponent(_DeltaTime);
}

void USpriteRendererComponent::Render()
{
	// 만약 스프라이트 렌더러에 연결된 애니메이터 컴포넌트가 있으면 
	if (AnimatorComponent != nullptr)
	{
		UEngineAnimation* CurAnimation = AnimatorComponent->CurAnimation;
		// 현재 재생해야 하는 애니메이션이 있는지 체크한다.
		if (nullptr != CurAnimation)
		{
			std::vector<int>& Indices = CurAnimation->FrameIndices;
			std::vector<float>& Intervals = CurAnimation->FrameIntervals;

			Sprite = CurAnimation->Sprite;

			CurAnimation->CurTime += UEngineAPICore::GetEngineDeltaTime();

			float CurFrameTime = Intervals[CurAnimation->CurIndex];

			if (CurAnimation->CurTime > CurFrameTime)
			{
				CurAnimation->CurTime -= CurFrameTime;
				++CurAnimation->CurIndex;

				if (CurAnimation->Events.contains(CurAnimation->CurIndex))
				{
					CurAnimation->Events[CurAnimation->CurIndex]();
				}

				if (CurAnimation->CurIndex >= Indices.size())
				{
					if (true == CurAnimation->IsLoop)
					{
						CurAnimation->CurIndex = 0;

						if (CurAnimation->Events.contains(CurAnimation->CurIndex))
						{
							CurAnimation->Events[CurAnimation->CurIndex]();
						}

					}
					else
					{
						--CurAnimation->CurIndex;
					}
				}

			}
			CurIndex = Indices[CurAnimation->CurIndex];
			// ++CurAnimation->CurIndex;
		}
	}

	if (nullptr == Sprite)
	{
		MSGASSERT("스프라이트가 세팅되지 않은 액터를 랜더링을 할수 없습니다.");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = UEngineAPICore::GetBackBuffer();

	FTransform Transform = GetWorldTransform();

	ULevel* Level = GetOwner()->GetWorld();

	if (true == IsCameraEffected)
	{
		Transform.Location = Transform.Location - (Level->CameraPos);
	}

	Transform.Location += Pivot;

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	if (true == RemoveBackground)
	{
		RemoveColor = CurData.Image->GetPixelColor({ 0,0 }, { 0,0,0,0 });
	}
	else
	{
		RemoveColor = UColor(255, 0, 255, 0);
	}

	if (Alpha == 255)
	{
		CurData.Image->CopyToTransparent(BackBufferImage, Transform, CurData.Transform, RemoveColor);
	}
	else
	{
		CurData.Image->CopyToAlphaBlend(BackBufferImage, Transform, CurData.Transform, Alpha);
	}
}

void USpriteRendererComponent::SetOrder(int _Order)
{
	int PrevOrder = Order;

	Order = _Order;

	ULevel* Level = GetOwner()->GetWorld();

	if (nullptr != Level)
	{
		Level->ChangeRenderOrder(this, PrevOrder);
	}
}

FVector2D USpriteRendererComponent::SetSpriteScale(float _Ratio, int _Index)
{
	if (nullptr == Sprite)
	{
		MSGASSERT("스프라이트가 세팅되지 않았습니다!");
		return FVector2D::ZERO;
	}

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(_Index);

	FVector2D Scale = CurData.Transform.Scale * _Ratio;

	SetComponentScale(CurData.Transform.Scale * _Ratio);

	return Scale;
}

void USpriteRendererComponent::SetPivot(EPivotType _Type)
{
	if (EPivotType::MiddleCenter == _Type)
	{
		SetPivot(FVector2D::ZERO);
		return;
	}

	if (nullptr == Sprite)
	{
		MSGASSERT("이미지를 기반으로한 피봇설정은 스프라이트가 세팅되지 않은 상태에서는 호출할수 없습니다");
		return;
	}

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	switch (_Type)
	{
	case EPivotType::TopLeft:
		Pivot = CurData.Transform.Scale.Half();
		break;
	case EPivotType::TopCenter:
		Pivot.X = 0.0f;
		Pivot.Y = CurData.Transform.Scale.Half().Y;
		break;
	case EPivotType::TopRight:
		Pivot.X = -CurData.Transform.Scale.Half().X;
		Pivot.Y = CurData.Transform.Scale.Half().Y;
		break;
	case EPivotType::MiddleLeft:
		Pivot.X = CurData.Transform.Scale.Half().X;
		Pivot.Y = 0.0f;
		break;
	case EPivotType::MiddleCenter:
		SetPivot(FVector2D::ZERO);
		break;
	case EPivotType::MiddleRight:
		Pivot.X = -CurData.Transform.Scale.Half().X;
		Pivot.Y = 0.0f;
		break;
	case EPivotType::BottomLeft:
		Pivot.X = CurData.Transform.Scale.Half().X;
		Pivot.Y = -CurData.Transform.Scale.Half().Y;
		break;
	case EPivotType::BottomCenter:
		Pivot.X = 0.0f;
		Pivot.Y = -CurData.Transform.Scale.Half().Y;
		break;
	case EPivotType::BottomRight:
		Pivot.X = -CurData.Transform.Scale.Half().X;
		Pivot.Y = -CurData.Transform.Scale.Half().Y;
		break;
	default:
		break;
	}

}


