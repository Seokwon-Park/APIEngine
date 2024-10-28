#include "aepch.h"
#include "Player.h"

#include "EngineCore/EngineAPICore.h"
#include "EnginePlatform/EngineInput.h"

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
	// �̺�Ʈ ������� ó��
	UEngineInput::GetInst().BindAction(KeyCode::Left, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::LEFT));
	UEngineInput::GetInst().BindAction(KeyCode::Left, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::RIGHT));
	UEngineInput::GetInst().BindAction(KeyCode::Left, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::DOWN));
	UEngineInput::GetInst().BindAction(KeyCode::Left, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::UP));
}

void APlayer::MoveFunction(FVector2D _Dir)
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);
}

void APlayer::Tick(float _DeltaTime)
{

}