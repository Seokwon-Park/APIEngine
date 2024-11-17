#pragma once



// 클래스 설명 :
class UEnginePostProcess 
{
public:
	// Constrcuter Destructer
	UEnginePostProcess();
	virtual ~UEnginePostProcess();

	// Delete Function
	UEnginePostProcess(const UEnginePostProcess& _Other) = delete;
	UEnginePostProcess(UEnginePostProcess&& _Other) noexcept = delete;
	UEnginePostProcess& operator=(const UEnginePostProcess& _Other) = delete;
	UEnginePostProcess& operator=(UEnginePostProcess&& _Other) noexcept = delete;

	virtual void EffectTick() = 0;

	bool IsEnabled = false;
protected:

private:

};
