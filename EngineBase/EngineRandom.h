#pragma once
#include <random>

// 클래스 설명 :
class UEngineRandom 
{
public:
	// Constrcuter Destructer
	~UEngineRandom();

	// Delete Function
	UEngineRandom(const UEngineRandom& _Other) = delete;
	UEngineRandom(UEngineRandom&& _Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& _Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& _Other) noexcept = delete;

	static void Init();           
	static int GetRandomInt(int min, int max);
	static float GetRandomFloat(float min, float max);
protected:

private:
	
private:
	UEngineRandom();
	static std::mt19937 Generator;

};
