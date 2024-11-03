#include "aepch.h"
#include "Player.h"

#include "EngineCore/EngineAPICore.h"
#include "EnginePlatform/EngineInput.h"

APlayer::APlayer()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 32, 32 });

	//Sr = CreateDefaultSubObject<USpriteRendererComponent>();
	//Sr->SetSprite("Puyo_r.cns.bmp", 0);
	//Sr->SetComponentScale({ 100, 100 });
	
	//SetSprite("test.png");
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
	// 이벤트 방식으로 처리
	GetWorld()->SetCameraToMainPawn(false);
	UEngineInput::GetInstance().BindAction(Key::Left, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::LEFT));
	UEngineInput::GetInstance().BindAction(Key::Right, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::RIGHT));
	UEngineInput::GetInstance().BindAction(Key::Down, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::DOWN));
	UEngineInput::GetInstance().BindAction(Key::Up, KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::UP));
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
