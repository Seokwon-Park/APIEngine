#include "aepch.h"
#include "EngineRandom.h"


UEngineRandom::UEngineRandom()
	:Generator(static_cast<unsigned long long>(time(nullptr)))
{
}

UEngineRandom::~UEngineRandom()
{
}

int UEngineRandom::GetRandomInt(int _InclusiveMin, int _InclusiveMax)
{
	std::uniform_int_distribution<int> Dist(_InclusiveMin, _InclusiveMax);
	return Dist(Generator);
}

float UEngineRandom::GetRandomFloat(float _InclusiveMin, float _ExclusiveMax)
{
	std::uniform_real_distribution<float> Dist(_InclusiveMin, _ExclusiveMax);
	return Dist(Generator);
}
