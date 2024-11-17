#include "aepch.h"
#include "PuyoBoardShake.h"

UPuyoBoardShake::UPuyoBoardShake()
{
	for (int i = 0; i < 6; i++)
	{
		ShakeImage[i] = new UEngineWinImage();
		ShakeImage[i]->Create(UEngineAPICore::GetBackBuffer(), { 32,480 });
	}
}

UPuyoBoardShake::~UPuyoBoardShake()
{
	for (int i = 0; i < 6; i++)
	{
		delete ShakeImage[i];
	}
}

void UPuyoBoardShake::EffectTick()
{
	if (false == IsEnabled) return;

	Timer += UEngineAPICore::GetEngineDeltaTime();
	auto BackBuffer = UEngineAPICore::GetBackBuffer();

	for (int i = 0; i < 6; i++)
	{
		FTransform TargetTrans1({ 16,240 }, { 32,480 });
		FTransform CopyTrans1(StartPos + FVector2D(32 * i,0), { 32,480 });
		BackBuffer->CopyToTransparent(ShakeImage[i], TargetTrans1, CopyTrans1);
	}

	FTransform CopyTrans({ 0,0 }, { 32,480 });
	for (int i = 0; i < 6; i++)
	{
		float offset = std::sin(Timer * 30.0f + i) * 10.0f; // 사인파로 오프셋 계산
		//float Y = baseY + offset); // y 위치에 흔들림 적용
		FTransform TargetTrans(StartPos + FVector2D(32 * i + 16.0f, 240.0f + offset), { 32,480 });
		ShakeImage[i]->CopyToTransparent(BackBuffer, TargetTrans, CopyTrans);
	}
	if (Timer < 0.5f)
	{
		for (int i = 0; i < 6; i++)
		{
			FTransform TargetTrans(StartPos + FVector2D(32 * i + 16, 240), { 32,480 });
			FTransform CopyTrans({ 0,0 }, { 32,480 });
			ShakeImage[i]->CopyToTransparent(BackBuffer, TargetTrans, CopyTrans);
		}
	}

	if (Timer >= 1.0f)
		IsEnabled = false;

	//TargetTrans = { { 50,50 }, { 100,100 } };
	//CopyTrans = { { 100,100 }, { 100,100 } };
}

void UPuyoBoardShake::CaptureBoardState()
{
	auto BackBuffer = UEngineAPICore::GetBackBuffer();


}

void UPuyoBoardShake::SetEnable()
{
	IsEnabled = true;
	Timer = 0.0f;
}

