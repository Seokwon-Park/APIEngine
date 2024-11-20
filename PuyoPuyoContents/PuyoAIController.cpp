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

	State= static_cast<EPuyoAIState>(RandomDevice.GetRandomInt(0, 3));
	//Do Sth
	switch (State)
	{
	case EPuyoAIState::Down:
		Board->PuyoForceDown();
		break;
	case EPuyoAIState::Left:
		Board->PuyoMoveLR({-1,0});
		break;
	case EPuyoAIState::Right:
		Board->PuyoMoveLR({ 1,0});
		break;
	case EPuyoAIState::Rotate:
		Board->Rotate(true);
		break;
	default:
		break;
	}

}
void APuyoAIController::BeginPlay()
{
	Super::BeginPlay();

	Board = GetActor<APuyoBoard>();
}
