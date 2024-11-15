#pragma once

// 설명 :
class UEngineTimer : public UObject
{
public:
	// constrcuter destructer
	UEngineTimer();
	~UEngineTimer();

	// delete Function
	UEngineTimer(const UEngineTimer& _Other) = delete;
	UEngineTimer(UEngineTimer&& _Other) noexcept = delete;
	UEngineTimer& operator=(const UEngineTimer& _Other) = delete;
	UEngineTimer& operator=(UEngineTimer&& _Other) noexcept = delete;


	// nano sec 
	void TimeCheck();

	float GetDeltaTime()
	{
		return fDeltaTime;
	}

	double GetDoubleDeltaTime()
	{
		return DeltaTime;
	}

	void TimeStart();

	float End();

	double DEnd();

protected:

private:
	// 1초에 x번 센다.
	LARGE_INTEGER Count; 
	// 기준 시간으로부터 x초 지난시간
	LARGE_INTEGER PrevTime;
	// 기준 시간으로부터 현재 시간
	LARGE_INTEGER CurTime;

	double TimeCounter;
	double DeltaTime;
	float fDeltaTime;
};

