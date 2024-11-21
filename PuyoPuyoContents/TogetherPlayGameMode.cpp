#include "aepch.h"
#include "TogetherPlayGameMode.h"

#include "PuyoPlayerController.h"



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

	Background->SetBackground(EPuyoGameMode::Versus, 0);

	GetWorld()->SpawnActor<ATogetherFrame>();
	ControllerP1 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP1->Possess(PuyoBoardP1);
	ControllerP1->SetKey(EKey::G, EKey::H, EKey::S, EKey::A, EKey::D);

	ControllerP2 = GetWorld()->SpawnActor<APuyoPlayerController>();
	ControllerP2->Possess(PuyoBoardP2);
	ControllerP2->SetKey(EKey::Slash, EKey::Period, EKey::Down, EKey::Left, EKey::Right);

}

void ATogetherPlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
