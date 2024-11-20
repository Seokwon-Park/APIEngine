#include "aepch.h"
#include "PlayerController.h"

APlayerController::APlayerController()
{
	InputComponent = CreateDefaultSubobject<UInputComponent>("");
}

APlayerController::~APlayerController()
{
}


void APlayerController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void APlayerController::BeginPlay()
{
	Super::BeginPlay();
}
