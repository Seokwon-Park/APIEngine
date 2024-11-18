#include "aepch.h"
#include "TogetherPlayGameMode.h"


ATogetherPlayGameMode::ATogetherPlayGameMode()
{
}

ATogetherPlayGameMode::~ATogetherPlayGameMode()
{

}

void ATogetherPlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayGameMode::BeginPlay();

	GetWorld()->SpawnActor<ATogetherFrame>();
	GetWorld()->SpawnActor<ATogetherBackground>();
}

void ATogetherPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
