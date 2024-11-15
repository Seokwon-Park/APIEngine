#pragma once
#include <random>

// 클래스 설명 :
class UEngineRandom :public UObject
{
public:
	// Constrcuter Destructer
	UEngineRandom();
	~UEngineRandom();

	// Delete Function
	UEngineRandom(const UEngineRandom& _Other) = delete;
	UEngineRandom(UEngineRandom&& _Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& _Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& _Other) noexcept = delete;

	inline void SetSeed(unsigned long long _Seed) { Generator.seed(_Seed); }
	int GetRandomInt(int _InclusiveMin, int _InclusiveMax);
	float GetRandomFloat(float _InclusiveMin, float _ExclusiveMax);
protected:

private:
	std::mt19937_64 Generator;

};
