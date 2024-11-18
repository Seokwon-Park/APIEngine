#include "aepch.h"
#include "DummyPawn.h"

#include "EngineCore/EngineAPICore.h"
#include "EnginePlatform/EngineInput.h"

ADummyPawn::ADummyPawn()
{
}

ADummyPawn::~ADummyPawn()
{

}

void ADummyPawn::BeginPlay()
{
	Super::BeginPlay();
	// 이벤트 방식으로 처리
	GetWorld()->SetCameraToMainPawn(false);
}


void ADummyPawn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
