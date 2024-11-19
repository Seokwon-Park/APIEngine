#include "aepch.h"
#include "PuyoAIController.h"

APuyoAIController::APuyoAIController()
{
}

APuyoAIController::~APuyoAIController()
{
}


void APuyoAIController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ThinkDelay -= _DeltaTime;
	if (ThinkDelay <= 0.0f)
	{
		ThinkDelay = 0.5f;
		//Do Sth

	}
}
void APuyoAIController::BeginPlay()
{
	Super::BeginPlay();
}
