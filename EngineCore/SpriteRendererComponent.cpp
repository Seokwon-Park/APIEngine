#include "aepch.h"
#include "SpriteRendererComponent.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineAPICore.h>

USpriteRendererComponent::USpriteRendererComponent()
	:Order(0), Sprite(nullptr), CurIndex(0), AnimatorComponent(nullptr)
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
		MSGASSERT("");
		return;
	}

	CurIndex = _CurIndex;
}

void USpriteRendererComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = GetOwner();
	ULevel* Level = Actor->GetWorld();

	for (UActorComponent* Component : Actor->GetComponents())
	{
		UAnimatorComponent* Animator = dynamic_cast<UAnimatorComponent*>(Component);
		if (nullptr != Animator)
		{
			AnimatorComponent = Animator;
			break;
		}
	}


	Level->PushRenderer(this);
}

void USpriteRendererComponent::TickComponent(float _DeltaTime)
{
	Super::TickComponent(_DeltaTime);
}

void USpriteRendererComponent::Render()
{
	// 만약 스프라이트에 연결된 애니메이터 컴포넌트가 있으면 
	
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

			//                           0.1 0.1 0.1
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


			//         2 3 4           0
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

	Transform.Location = Transform.Location - Level->CameraPos;

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image->CopyToTransparent(BackBufferImage, Transform, CurData.Transform);
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


