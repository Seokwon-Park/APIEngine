#pragma once
#include <EngineCore/EnginePostProcess.h>

// 클래스 설명 :
class UPuyoBoardShakePostProcess : public UEnginePostProcess
{
public:
	// Constrcuter Destructer
	UPuyoBoardShakePostProcess();
	~UPuyoBoardShakePostProcess();

	// Delete Function
	UPuyoBoardShakePostProcess(const UPuyoBoardShakePostProcess& _Other) = delete;
	UPuyoBoardShakePostProcess(UPuyoBoardShakePostProcess&& _Other) noexcept = delete;
	UPuyoBoardShakePostProcess& operator=(const UPuyoBoardShakePostProcess& _Other) = delete;
	UPuyoBoardShakePostProcess& operator=(UPuyoBoardShakePostProcess&& _Other) noexcept = delete;

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
