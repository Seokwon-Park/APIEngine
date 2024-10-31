#include "aepch.h"
#include "Player.h"

#include "EngineCore/EngineAPICore.h"
#include "EnginePlatform/EngineInput.h"

APlayer::APlayer()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 32, 32 });

	Sr = CreateDefaultSubObject<USpriteRendererComponent>();
	Sr->SetSprite("test.png", 0);
	Sr->SetComponentScale({ 100, 100 });
	//SetSprite("test.png");
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
	// 이벤트 방식으로 처리
	UEngineInput::GetInst().BindAction(Key::Left, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::LEFT));
	UEngineInput::GetInst().BindAction(Key::Right, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::RIGHT));
	UEngineInput::GetInst().BindAction(Key::Down, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::DOWN));
	UEngineInput::GetInst().BindAction(Key::Up, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::UP));
}

void APlayer::MoveFunction(FVector2D _Dir)
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
