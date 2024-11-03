#include "aepch.h"
#include "EngineRandom.h"

std::mt19937 UEngineRandom::Generator;

UEngineRandom::UEngineRandom()
{
}

UEngineRandom::~UEngineRandom()
{
}

void UEngineRandom::Init()
{
	Generator.seed(static_cast<unsigned int>(std::time(nullptr)));
}

int UEngineRandom::GetRandomInt(int _InclusiveMin, int _InclusiveMax)
{
	std::uniform_int_distribution<int> Dist(_InclusiveMin, _InclusiveMax);
	return Dist(Generator);
}

float UEngineRandom::GetRandomFloat(float _InclusiveMin, float _InclusiveMax)
{
	std::uniform_real_distribution<float> Dist(_InclusiveMin, _InclusiveMax);
	return Dist(Generator);
}
