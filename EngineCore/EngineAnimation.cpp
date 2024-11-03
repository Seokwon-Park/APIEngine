#include "aepch.h"
#include "EngineAnimation.h"

UEngineAnimation::UEngineAnimation()
	:Sprite(nullptr), CurIndex(0), ResultIndex(0), CurTime(0.0f), IsLoop(true)
{
}

UEngineAnimation::~UEngineAnimation()
{
}

UEngineAnimation::UEngineAnimation(const UEngineAnimation& _Other)
{
	Sprite = _Other.Sprite;

	CurIndex = _Other.CurIndex;
	ResultIndex = _Other.ResultIndex;
	CurTime = _Other.CurTime;
	IsLoop = _Other.IsLoop;
	FrameIndices = _Other.FrameIndices;
	FrameIntervals = _Other.FrameIntervals;
}

