#pragma once
#include <EngineCore/EnginePostProcess.h>

// 클래스 설명 :
class UPuyoBoardShake : public UEnginePostProcess
{
public:
	// Constrcuter Destructer
	UPuyoBoardShake();
	~UPuyoBoardShake();

	// Delete Function
	UPuyoBoardShake(const UPuyoBoardShake& _Other) = delete;
	UPuyoBoardShake(UPuyoBoardShake&& _Other) noexcept = delete;
	UPuyoBoardShake& operator=(const UPuyoBoardShake& _Other) = delete;
	UPuyoBoardShake& operator=(UPuyoBoardShake&& _Other) noexcept = delete;

	void EffectTick() override;
	void CaptureBoardState();
	void SetEnable();
	inline void SetupProcess(FVector2D _Offset) { StartPos = _Offset; }

	UEngineRandom RandomDevice;
	UEngineWinImage* ShakeImage[6];
protected:

private:
	FVector2D Transform[6];
	FVector2D StartPos = FVector2D::ZERO;
	bool IsEnabled = false;
	float Timer = 0.0f;

};
