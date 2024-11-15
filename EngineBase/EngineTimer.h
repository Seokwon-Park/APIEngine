#pragma once

// ���� :
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
	// 1�ʿ� x�� ����.
	LARGE_INTEGER Count; 
	// ���� �ð����κ��� x�� �����ð�
	LARGE_INTEGER PrevTime;
	// ���� �ð����κ��� ���� �ð�
	LARGE_INTEGER CurTime;

	double TimeCounter;
	double DeltaTime;
	float fDeltaTime;
};

