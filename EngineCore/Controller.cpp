#include "aepch.h"
#include "Controller.h"

AController::AController()
{
}

AController::~AController()
{
}


void AController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AController::Possess(AActor* InActor)
{
	if (InActor == nullptr)
	{
		return;
	}
	SetActor(InActor);
}

void AController::BeginPlay()
{
	Super::BeginPlay();
}
