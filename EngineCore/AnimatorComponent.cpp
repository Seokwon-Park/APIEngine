#include "aepch.h"
#include "AnimatorComponent.h"
#include "ImageManager.h"
#include <EngineBase/EngineStringHelper.h>

UAnimatorComponent::UAnimatorComponent()
	:CurAnimation(nullptr)
{
}

UAnimatorComponent::~UAnimatorComponent()
{
}

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	int _FrameStart, int _FrameEnd, float _FrameInterval, bool _IsLoop)
{
	if (_FrameStart > _FrameEnd)
	{
		MSGASSERT(std::string(_AnimationName) + "잘못된 범위 설정. FrameStart가 FrameEnd보다 큽니다.");
		return;
	}

	int Size = (_FrameEnd - _FrameStart) + 1;

	std::vector<int> Indices;
	std::vector<float> Intervals(Size, _FrameInterval);

	for (int i = 0; i < Size; i++)
	{
		Indices.push_back(_FrameStart + i);
	}

	CreateAnimation(_AnimationName, _SpriteName, Indices, Intervals, _IsLoop);
}

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, 
	std::vector<int> _Indices, float _FrameIntervals, bool _IsLoop)
{
	std::vector<float> Intervals(_Indices.size(), _FrameIntervals);


	CreateAnimation(_AnimationName, _SpriteName, _Indices, Intervals, _IsLoop);
}

void UAnimatorComponent::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName,
	std::vector<int> _FrameIndex, std::vector<float> _FrameInterval, bool _IsLoop)
{
	std::string UpperName = UEngineStringHelper::ToUpper(_AnimationName);

	if (_FrameIndex.size() != _FrameInterval.size())
	{
		MSGASSERT("두 배열 인자의 크기가 다릅니다. _Index와 _Interval은 크기가 동일해야 합니다.");
		return;
	}

	if (Animations.contains(UpperName))
	{
		return;
	}

	UEngineSprite* FindSprite = UImageManager::GetInstance().FindSprite(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("로드하지 않은 스프라이트를 애니메이션 생서에 사용하려고 했습니다" + std::string(UpperName));
		return;
	}

	UEngineAnimation NewAnimation;
	NewAnimation.Sprite = FindSprite;
	NewAnimation.FrameIndices = _FrameIndex;
	NewAnimation.FrameIntervals = _FrameInterval;
	NewAnimation.IsLoop = _IsLoop;
	NewAnimation.Reset();

	Animations.insert(std::make_pair(UpperName, NewAnimation));
}

void UAnimatorComponent::ChangeAnimation(std::string_view _AnimationName, bool _IsForce /*= false*/)
{
	std::string UpperName = UEngineStringHelper::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 애니메이션으로 변경하려고 했습니다. = " + UpperName);
		return;
	}

	UEngineAnimation* TargetAnimation = &Animations[UpperName];

	// 같은 애니메이션으로 교체하는 것 or 강제 교체가 false일 때??
	// 잘모르겠다 이부분 질문.
	if (CurAnimation == TargetAnimation && false == _IsForce)
	{
		return;
	}

	CurAnimation = &Animations[UpperName];
	CurAnimation->Reset();
}

void UAnimatorComponent::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineStringHelper::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MSGASSERT("존재하지 않는 애니메이션 이름입니다.");
		return;
	}

	UEngineAnimation* TargetAnimation = &Animations[UpperName];

	if (_Frame >= TargetAnimation->FrameIndices.size())
	{
		MSGASSERT("_Frame이 애니메이션의 최대 프레임 수를 초과합니다.");
		return;
	}

	TargetAnimation->Events[_Frame] += _Function;
}
