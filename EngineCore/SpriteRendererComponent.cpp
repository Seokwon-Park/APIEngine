#include "aepch.h"
#include "SpriteRendererComponent.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/EngineAPICore.h>

USpriteRendererComponent::USpriteRendererComponent()
	:Order(0), Sprite(nullptr), CurIndex(0)
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

	Level->PushRenderer(this);
}

void USpriteRendererComponent::TickComponent(float _DeltaTime)
{
	Super::TickComponent(_DeltaTime);
}

void USpriteRendererComponent::Render()
{
	if (nullptr == Sprite)
	{
		MSGASSERT("스프라이트가 세팅되지 않은 액터를 랜더링을 할수 없습니다.");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = UEngineAPICore::GetBackBuffer();


	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image->CopyToTransparent(BackBufferImage, GetWorldTransform(), CurData.Transform);
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

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, 
	std::vector<int> _FrameIndex, std::vector<int> _FrameInterval, bool _IsLoop)
{
	UEngineString::ToUpper(_AnimationName);

	if (_FrameIndex.size() != _FrameInterval.size())
	{
		MSGASSERT("");
		return;
	}
	USpriteRendererComponent::UFrameAnimation NewAnimation;
}
