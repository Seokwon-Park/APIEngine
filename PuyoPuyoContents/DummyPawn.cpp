#include "aepch.h"
#include "DummyPawn.h"

#include "EngineCore/EngineAPICore.h"
#include "EnginePlatform/EngineInput.h"

ADummyPawn::ADummyPawn()
{
	/*SetActorLocation({ 100, 100 });
	SetActorScale({ 32, 32 });*/

	//Sr = CreateDefaultSubObject<USpriteRendererComponent>();
	//Sr->SetSprite("Puyo_r.cns.bmp", 0);
	//Sr->SetComponentScale({ 100, 100 });
	
	//SetSprite("test.png");
}

ADummyPawn::~ADummyPawn()
{

}

void ADummyPawn::BeginPlay()
{
	Super::BeginPlay();
	// 이벤트 방식으로 처리
	GetWorld()->SetCameraToMainPawn(false);
	/*GetWorld()->GetInputSystem().BindAction(Key::Left, KeyEvent::Press, std::bind(&ADummyPawn::MoveFunction, this, FVector2D::LEFT));
	GetWorld()->GetInputSystem().BindAction(Key::Right, KeyEvent::Press, std::bind(&ADummyPawn::MoveFunction, this, FVector2D::RIGHT));
	GetWorld()->GetInputSystem().BindAction(Key::Down, KeyEvent::Press, std::bind(&ADummyPawn::MoveFunction, this, FVector2D::DOWN));
	GetWorld()->GetInputSystem().BindAction(Key::Up, KeyEvent::Press, std::bind(&ADummyPawn::MoveFunction, this, FVector2D::UP));*/
}

//void ADummyPawn::MoveFunction(FVector2D _Dir)
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//	AddActorLocation(_Dir * DeltaTime * Speed);
//}

void ADummyPawn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
