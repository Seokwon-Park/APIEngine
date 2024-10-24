#include "aepch.h"
#include "Player.h"

APlayer::APlayer()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{

}

void APlayer::Tick()
{
	AddActorLocation(FVector2D::RIGHT * 0.0001f);
}
